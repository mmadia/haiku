/*
 * Copyright 2004, Waldemar Kornewald <Waldemar.Kornewald@web.de>
 * Distributed under the terms of the MIT License.
 */

#include <PTPSettings.h>

// built-in add-ons
#include <PPPDefs.h>
#include "ConnectionOptionsAddon.h"
#include "GeneralAddon.h"
#include "IPCPAddon.h"
#include "PPPoEAddon.h"

#include "MessageDriverSettingsUtils.h"
#include <TemplateList.h>

#include <Directory.h>
#include <File.h>


PTPSettings::PTPSettings()
{
}


PTPSettings::~PTPSettings()
{
	// free known add-on types (these should free their known add-on types, etc.)
	DialUpAddon *addon;
	for(int32 index = 0;
			fAddons.FindPointer(DUN_DELETE_ON_QUIT, index,
				reinterpret_cast<void**>(&addon)) == B_OK;
			index++)
		delete addon;
}


bool
PTPSettings::GetPTPDirectories(BDirectory *settingsDirectory,
	BDirectory *profileDirectory) const
{
	if(settingsDirectory) {
		BDirectory settings(PPP_INTERFACE_SETTINGS_PATH);
		if(settings.InitCheck() != B_OK) {
			create_directory(PPP_INTERFACE_SETTINGS_PATH, 0750);
			settings.SetTo(PPP_INTERFACE_SETTINGS_PATH);
			if(settings.InitCheck() != B_OK)
				return false;
		}
		
		*settingsDirectory = settings;
	}
	
	if(profileDirectory) {
		BDirectory profile(PPP_INTERFACE_SETTINGS_PATH "/profile");
		if(profile.InitCheck() != B_OK) {
			create_directory(PPP_INTERFACE_SETTINGS_PATH "/profile", 0750);
			profile.SetTo(PPP_INTERFACE_SETTINGS_PATH "/profile");
			if(profile.InitCheck() != B_OK)
				return false;
		}
		
		*profileDirectory = profile;
	}
	
	return true;
}


bool
PTPSettings::LoadSettings(const char *interfaceName, bool isNew)
{
	if(interfaceName && strlen(interfaceName) == 0)
		return false;
	
	fCurrent = interfaceName ? interfaceName : "";
	fSettings.MakeEmpty();
	fProfile.MakeEmpty();
	BMessage *settingsPointer = interfaceName ? &fSettings : NULL,
		*profilePointer = interfaceName ? &fProfile : NULL;
	
	if(interfaceName && !isNew) {
		BString name("pppidf/");
		name << fCurrent;
		if(!ReadMessageDriverSettings(name.String(), &fSettings))
			return false;
		name = "pppidf/profile/";
		name << fCurrent;
		if(!ReadMessageDriverSettings(name.String(), &fProfile))
			profilePointer = settingsPointer;
	}
	
	DialUpAddon *addon;
	for(int32 index = 0; fAddons.FindPointer(DUN_TAB_ADDON_TYPE, index,
			reinterpret_cast<void**>(&addon)) == B_OK; index++) {
		if(!addon)
			continue;
		
		if(!addon->LoadSettings(settingsPointer, profilePointer, isNew))
			return false;
	}
	
	// TODO: check if settings are valid
	
	return true;
}


void
PTPSettings::IsModified(bool *settings, bool *profile)
{
	*settings = *profile = false;
	bool addonSettingsChanged, addonProfileChanged;
		// for current addon
	
	DialUpAddon *addon;
	for(int32 index = 0; fAddons.FindPointer(DUN_TAB_ADDON_TYPE, index,
			reinterpret_cast<void**>(&addon)) == B_OK; index++) {
		if(!addon)
			continue;
		
		addon->IsModified(&addonSettingsChanged, &addonProfileChanged);
		if(addonSettingsChanged)
			*settings = true;
		if(addonProfileChanged)
			*profile = true;
	}
}


bool
PTPSettings::SaveSettings(BMessage *settings, BMessage *profile, bool saveTemporary)
{
	if(fCurrent.Length() == 0 || !settings || !profile)
		return false;
	
	DialUpAddon *addon;
	TemplateList<DialUpAddon*> addons;
	for(int32 index = 0;
			fAddons.FindPointer(DUN_TAB_ADDON_TYPE, index,
				reinterpret_cast<void**>(&addon)) == B_OK; index++) {
		if(!addon)
			continue;
		
		int32 insertIndex = 0;
		for(; insertIndex < addons.CountItems(); insertIndex++)
			if(addons.ItemAt(insertIndex)->Priority() <= addon->Priority())
				break;
		
		addons.AddItem(addon, insertIndex);
	}
	
	settings->AddString("InterfaceName", fCurrent);
	
	for(int32 index = 0; index < addons.CountItems(); index++)
		if(!addons.ItemAt(index)->SaveSettings(settings, profile, saveTemporary))
			return false;
	
	return true;
}


bool
PTPSettings::SaveSettingsToFile()
{
	bool settingsChanged, profileChanged;
	IsModified(&settingsChanged, &profileChanged);
	if(!settingsChanged && !profileChanged)
		return true;
	
	BMessage settings, profile;
	if(!SaveSettings(&settings, &profile, false))
		return false;
	
	BDirectory settingsDirectory;
	BDirectory profileDirectory;
	if(!GetPTPDirectories(&settingsDirectory, &profileDirectory))
		return false;
	
	BFile file;
	if(settingsChanged) {
		settingsDirectory.CreateFile(fCurrent.String(), &file);
		WriteMessageDriverSettings(file, settings);
	}
	
	if(profileChanged) {
		profileDirectory.CreateFile(fCurrent.String(), &file);
		WriteMessageDriverSettings(file, profile);
	}
	
	return true;
}


void
PTPSettings::LoadAddons(bool loadGeneralAddon = true)
{
	// Load built-in add-ons:
	// "Connection Options" tab
	ConnectionOptionsAddon *connectionOptionsAddon =
		new ConnectionOptionsAddon(&fAddons);
	fAddons.AddPointer(DUN_TAB_ADDON_TYPE, connectionOptionsAddon);
	fAddons.AddPointer(DUN_DELETE_ON_QUIT, connectionOptionsAddon);
	// "General" tab
	if(loadGeneralAddon) {
		GeneralAddon *fGeneralAddon = new GeneralAddon(&fAddons);
		fAddons.AddPointer(DUN_TAB_ADDON_TYPE, fGeneralAddon);
		fAddons.AddPointer(DUN_DELETE_ON_QUIT, fGeneralAddon);
	}
	// "IPCP" protocol
	IPCPAddon *ipcpAddon = new IPCPAddon(&fAddons);
	fAddons.AddPointer(DUN_TAB_ADDON_TYPE, ipcpAddon);
	fAddons.AddPointer(DUN_DELETE_ON_QUIT, ipcpAddon);
	// "PPPoE" device
	PPPoEAddon *pppoeAddon = new PPPoEAddon(&fAddons);
	fAddons.AddPointer(DUN_DEVICE_ADDON_TYPE, pppoeAddon);
	fAddons.AddPointer(DUN_DELETE_ON_QUIT, pppoeAddon);
	
	// "PAP" authenticator
	BMessage addon;
#ifdef LANG_GERMAN
	addon.AddString("FriendlyName", "Unverschlüsselt");
#else
	addon.AddString("FriendlyName", "Plain-text Authentication");
#endif
	addon.AddString("TechnicalName", "PAP");
	addon.AddString("KernelModuleName", "pap");
	fAddons.AddMessage(DUN_AUTHENTICATOR_ADDON_TYPE, &addon);
	// addon.MakeEmpty(); // for next authenticator
	
	// TODO:
	// load all add-ons from the add-ons folder
}
