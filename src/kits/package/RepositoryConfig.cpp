/*
 * Copyright 2011, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Oliver Tappe <zooey@hirschkaefer.de>
 */


#include <package/RepositoryConfig.h>

#include <stdlib.h>

#include <new>

#include <Directory.h>
#include <driver_settings.h>
#include <File.h>
#include <FindDirectory.h>
#include <Path.h>


namespace Haiku {

namespace Package {


const uint8 RepositoryConfig::kDefaultPriority	= 50;
const char* RepositoryConfig::kNameField 		= "name";
const char* RepositoryConfig::kURLField 		= "url";
const char* RepositoryConfig::kPriorityField 	= "priority";


RepositoryConfig::RepositoryConfig()
	:
	fInitStatus(B_NO_INIT),
	fPriority(kDefaultPriority),
	fIsUserSpecific(false)
{
}


RepositoryConfig::RepositoryConfig(const BEntry& entry)
{
	SetTo(entry);
}


RepositoryConfig::RepositoryConfig(BMessage* data)
	:
	inherited(data)
{
	SetTo(data);
}


RepositoryConfig::RepositoryConfig(const BString& name, const BString& url,
	uint8 priority)
	:
	fInitStatus(B_OK),
	fName(name),
	fURL(url),
	fPriority(priority),
	fIsUserSpecific(false)
{
}


RepositoryConfig::~RepositoryConfig()
{
}


/*static*/ RepositoryConfig*
RepositoryConfig::Instantiate(BMessage* data)
{
	if (validate_instantiation(data, "Haiku::Package::RepositoryConfig"))
		return new (std::nothrow) RepositoryConfig(data);

	return NULL;
}


status_t
RepositoryConfig::Archive(BMessage* data, bool deep) const
{
	status_t result = inherited::Archive(data, deep);
	if (result != B_OK)
		return result;

	if ((result = data->AddString(kNameField, fName)) != B_OK)
		return result;
	if ((result = data->AddString(kURLField, fURL)) != B_OK)
		return result;
	if ((result = data->AddUInt8(kPriorityField, fPriority)) != B_OK)
		return result;

	return B_OK;
}


status_t
RepositoryConfig::StoreAsConfigFile(const BEntry& entry) const
{
	BFile file(&entry, B_WRITE_ONLY | B_CREATE_FILE | B_ERASE_FILE);
	status_t result = file.InitCheck();
	if (result != B_OK)
		return result;

	BString configString;
	configString
		<< "url=" << fURL << "\n"
		<< "priority=" << fPriority << "\n";

	int32 size = configString.Length();
	if ((result = file.Write(configString.String(), size)) < size)
		return (result >= 0) ? B_ERROR : result;

	return B_OK;
}


status_t
RepositoryConfig::InitCheck() const
{
	return fInitStatus;
}


status_t
RepositoryConfig::SetTo(const BEntry& entry)
{
	fEntry = entry;
	fInitStatus = B_NO_INIT;

	BFile file(&entry, B_READ_ONLY);
	status_t result = file.InitCheck();
	if (result != B_OK)
		return result;

	off_t size;
	if ((result = file.GetSize(&size)) != B_OK)
		return result;

	BString configString;
	char* buffer = configString.LockBuffer(size);
	if (buffer == NULL)
		return B_NO_MEMORY;

	if ((result = file.Read(buffer, size)) < size)
		return (result >= 0) ? B_IO_ERROR : result;

	buffer[size] = '\0';
	configString.UnlockBuffer(size);

	void* settingsHandle = parse_driver_settings_string(configString.String());
	if (settingsHandle == NULL)
		return B_BAD_DATA;

	const char* url = get_driver_parameter(settingsHandle, "url", NULL, NULL);
	const char* priorityString
		= get_driver_parameter(settingsHandle, "priority", NULL, NULL);

	unload_driver_settings(settingsHandle);

	if (url == NULL || *url == '\0')
		return B_BAD_DATA;

	char name[B_FILE_NAME_LENGTH];
	if ((result = entry.GetName(name)) != B_OK)
		return result;

	fName = name;
	fURL = url;
	fPriority = priorityString == NULL
		? kDefaultPriority : atoi(priorityString);

	BPath userSettingsPath;
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &userSettingsPath) == B_OK) {
		BDirectory userSettingsDir(userSettingsPath.Path());
		fIsUserSpecific = userSettingsDir.Contains(&entry);
	} else
		fIsUserSpecific = false;

	fInitStatus = B_OK;

	return B_OK;
}


status_t
RepositoryConfig::SetTo(const BMessage* data)
{
	fInitStatus = B_NO_INIT;

	if (data == NULL)
		return B_BAD_VALUE;

	status_t result;
	if ((result = data->FindString(kNameField, &fName)) != B_OK)
		return result;
	if ((result = data->FindString(kURLField, &fURL)) != B_OK)
		return result;
	if ((result = data->FindUInt8(kPriorityField, &fPriority)) != B_OK)
		return result;

	fIsUserSpecific = false;

	fInitStatus = B_OK;

	return B_OK;
}


const BString&
RepositoryConfig::Name() const
{
	return fName;
}


const BString&
RepositoryConfig::URL() const
{
	return fURL;
}


uint8
RepositoryConfig::Priority() const
{
	return fPriority;
}


bool
RepositoryConfig::IsUserSpecific() const
{
	return fIsUserSpecific;
}


const BEntry&
RepositoryConfig::Entry() const
{
	return fEntry;
}


void
RepositoryConfig::SetName(const BString& name)
{
	fName = name;
}


void
RepositoryConfig::SetURL(const BString& url)
{
	fURL = url;
}


void
RepositoryConfig::SetPriority(uint8 priority)
{
	fPriority = priority;
}


void
RepositoryConfig::SetIsUserSpecific(bool isUserSpecific)
{
	fIsUserSpecific = isUserSpecific;
}


}	// namespace Package

}	// namespace Haiku
