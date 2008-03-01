/*
 * Copyright 2002-2008, Haiku. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		DarkWyrm (darkwyrm@earthlink.net)
 *		Rene Gollent (rene@gollent.com)
 */
#include <OS.h>
#include <Directory.h>
#include <Alert.h>
#include <Messenger.h>
#include <storage/Path.h>
#include <Entry.h>
#include <File.h>
#include <stdio.h>

#include <InterfaceDefs.h>

#include "APRView.h"
#include "defs.h"
#include "ColorWell.h"
#include "ColorWhichItem.h"
#include "ColorSet.h"

//#define DEBUG_APRVIEW

#ifdef DEBUG_APRVIEW
	#define STRACE(a) printf a
#else
	#define STRACE(A) /* nothing */
#endif

#define COLOR_DROPPED 'cldp'
#define DECORATOR_CHANGED 'dcch'

int32 sColorConsts[] = {
	B_PANEL_BACKGROUND_COLOR,
	B_PANEL_TEXT_COLOR,
	B_DOCUMENT_BACKGROUND_COLOR,
	B_DOCUMENT_TEXT_COLOR,
	B_CONTROL_BACKGROUND_COLOR,
	B_CONTROL_TEXT_COLOR,
	B_CONTROL_BORDER_COLOR,
	B_CONTROL_HIGHLIGHT_COLOR,
	B_NAVIGATION_BASE_COLOR,
	B_NAVIGATION_PULSE_COLOR,
	B_SHINE_COLOR,
	B_SHADOW_COLOR,
	B_MENU_BACKGROUND_COLOR,
	B_MENU_SELECTED_BACKGROUND_COLOR,
	B_MENU_ITEM_TEXT_COLOR,
	B_MENU_SELECTED_ITEM_TEXT_COLOR,
	B_MENU_SELECTED_BORDER_COLOR,
	B_TOOLTIP_BACKGROUND_COLOR,
	B_TOOLTIP_TEXT_COLOR,
	B_SUCCESS_COLOR,
	B_FAILURE_COLOR,
	B_WINDOW_TAB_COLOR,
	B_WINDOW_TEXT_COLOR,
	B_WINDOW_INACTIVE_TAB_COLOR,
	B_WINDOW_INACTIVE_TEXT_COLOR,
};

const uint32 sColorCount = sizeof(sColorConsts) / sizeof(int32);

namespace BPrivate
{
	int32 count_decorators(void);
	status_t set_decorator(const int32 &index);
	int32 get_decorator(void);
	status_t get_decorator_name(const int32 &index, BString &name);
	status_t get_decorator_preview(const int32 &index, BBitmap *bitmap);
}

APRView::APRView(const BRect &frame, const char *name, int32 resize, int32 flags)
 :	BView(frame,name,resize,flags),
 	fDecorMenu(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	BRect rect(Bounds().InsetByCopy(kBorderSpace,kBorderSpace));
	
	#ifdef HAIKU_TARGET_PLATFORM_HAIKU
	
	fDecorMenu = new BMenu("Window Style");
	int32 decorCount = BPrivate::count_decorators();
	if (decorCount > 1) {
		for (int32 i = 0; i < decorCount; i++) {
			BString name;
			BPrivate::get_decorator_name(i, name);
			if (name.CountChars() < 1)
				continue;
			fDecorMenu->AddItem(new BMenuItem(name.String(),
								new BMessage(DECORATOR_CHANGED)));
		}
		
		BMenuField *field = new BMenuField(rect, "menufield", "Window Style",
										fDecorMenu, B_FOLLOW_RIGHT | 
										B_FOLLOW_TOP);
		AddChild(field);
		field->SetDivider(be_plain_font->StringWidth("Window style: ") + 5);
		field->ResizeToPreferred();
		field->MoveTo(Bounds().right - field->Bounds().Width(), 10);
		rect = Bounds().InsetByCopy(10,10);
		rect.OffsetTo(10, field->Frame().bottom + 10);
	}
	BMenuItem *marked = fDecorMenu->ItemAt(BPrivate::get_decorator());
	if (marked)
		marked->SetMarked(true);
	else
	{
		marked = fDecorMenu->FindItem("Default");
		if (marked)
			marked->SetMarked(true);
	}
	
	#endif
	
	// Set up list of color fAttributes
	rect.right -= B_V_SCROLL_BAR_WIDTH;
	rect.bottom = rect.top + 75;
	fAttrList = new BListView(rect,"AttributeList", B_SINGLE_SELECTION_LIST,
							B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP);
	
	fScrollView = new BScrollView("ScrollView",fAttrList, B_FOLLOW_LEFT_RIGHT | 
									B_FOLLOW_TOP, 0, false, true);
	AddChild(fScrollView);
	fScrollView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	fAttrList->SetSelectionMessage(new BMessage(ATTRIBUTE_CHOSEN));

	printf("Color count: %lu\n", sColorCount);

	for (uint32 i = 0; i < sColorCount; i++) {
		printf("Adding color item for which: %ld\n", sColorConsts[i]);
		fAttrList->AddItem(new ColorWhichItem((color_which)sColorConsts[i]));
	}

	BRect wellrect(0,0,50,50);
	wellrect.OffsetTo(rect.right + 30, rect.top +
					(fScrollView->Bounds().Height() - wellrect.Height())/2 );

	fColorWell = new ColorWell(wellrect,new BMessage(COLOR_DROPPED),true);
	AddChild(fColorWell);
	
	// Center the list and color well
	
	rect = fScrollView->Frame();
	rect.right = wellrect.right;
	rect.OffsetTo((Bounds().Width()-rect.Width())/2,rect.top);
	
	fPicker = new BColorControl(BPoint(fScrollView->Frame().left,fScrollView->Frame().bottom+kBorderSpace),B_CELLS_32x8,5.0,"fPicker",
								new BMessage(UPDATE_COLOR));
	AddChild(fPicker);
	
	fDefaults = new BButton(BRect(0,0,1,1),"DefaultsButton","Defaults",
							new BMessage(DEFAULT_SETTINGS),
							B_FOLLOW_LEFT |B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	fDefaults->ResizeToPreferred();
	fDefaults->SetEnabled(false);
	fDefaults->MoveTo(fPicker->Frame().left,fPicker->Frame().bottom+kBorderSpace);
	AddChild(fDefaults);
	
	
	BRect cvrect(fDefaults->Frame());
	cvrect.OffsetBy(cvrect.Width() + kItemSpace,0);

	fRevert = new BButton(cvrect,"RevertButton","Revert", 
						new BMessage(REVERT_SETTINGS),
						B_FOLLOW_LEFT |B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	fRevert->ResizeToPreferred();
	fRevert->SetEnabled(false);
	AddChild(fRevert);
}

APRView::~APRView(void)
{
	ColorSet::SaveColorSet("/boot/home/config/settings/app_server/system_colors",fCurrentSet);
}

void
APRView::AttachedToWindow(void)
{
	fPicker->SetTarget(this);
	fAttrList->SetTarget(this);
	fDefaults->SetTarget(this);
	fRevert->SetTarget(this);
	fColorWell->SetTarget(this);

	fPicker->SetValue(fCurrentSet.StringToColor(fAttrString.String()));
	
	if (fDecorMenu)
		fDecorMenu->SetTargetForItems(BMessenger(this));
	
	Window()->ResizeTo(MAX(fPicker->Frame().right,fPicker->Frame().right) + 10,
					   fDefaults->Frame().bottom + 10);
	LoadSettings();
	fAttrList->Select(0);
	
	fDefaults->SetEnabled(fCurrentSet.IsDefaultable());
}

void
APRView::MessageReceived(BMessage *msg)
{
	if (msg->WasDropped()) {
		rgb_color *col;
		ssize_t size;
		
		if (msg->FindData("RGBColor",(type_code)'RGBC',(const void**)&col,&size)==B_OK) {
			fPicker->SetValue(*col);
			fColorWell->SetColor(*col);
			fColorWell->Invalidate();
			UpdateCurrentColor();
		}
	}

	switch(msg->what) {
		case DECORATOR_CHANGED: {
			int32 index = fDecorMenu->IndexOf(fDecorMenu->FindMarked());
			#ifdef HAIKU_TARGET_PLATFORM_HAIKU
			if (index >= 0)
				BPrivate::set_decorator(index);
			#endif
			break;
		}
		case UPDATE_COLOR: {
			// Received from the color fPicker when its color changes
			
			rgb_color col=fPicker->ValueAsColor();

			fColorWell->SetColor(col);
			fColorWell->Invalidate();
				
			// Update current fAttribute in the settings
			fCurrentSet.SetColor(fAttribute, col);
			UpdateCurrentColor();				
	
			fDefaults->SetEnabled(fCurrentSet.IsDefaultable());
			fRevert->SetEnabled(true);
			
			break;
		}
		case ATTRIBUTE_CHOSEN: {
			// Received when the user chooses a GUI fAttribute from the list
			
			ColorWhichItem *whichitem = (ColorWhichItem*)
										fAttrList->ItemAt(fAttrList->CurrentSelection());
			
			if (!whichitem)
				break;
			
			fAttrString=whichitem->Text();
			UpdateControlsFromAttr(whichitem->Text());
			
			fDefaults->SetEnabled(fCurrentSet.IsDefaultable());
			break;
		}
		case REVERT_SETTINGS: {
			fCurrentSet=fPrevSet;
			UpdateControlsFromAttr(fAttrString.String());
			UpdateAllColors();
			
			fRevert->SetEnabled(false);
			
			break;
		}
		case DEFAULT_SETTINGS: {
			fCurrentSet = ColorSet::DefaultColorSet();
			fDefaults->SetEnabled(false);
			
			UpdateControlsFromAttr(fAttrString.String());
			UpdateAllColors();

			BMenuItem *item = fDecorMenu->FindItem("Default");
			if (item)
			{
				item->SetMarked(true);
				#ifdef HAIKU_TARGET_PLATFORM_HAIKU
				BPrivate::set_decorator(fDecorMenu->IndexOf(item));
				#endif
			}
			break;
		}
		default:
			BView::MessageReceived(msg);
			break;
	}
}

void APRView::LoadSettings(void)
{
	printf("Max colors: %lu\n", sColorCount);
	for (uint32 i = 0; i < sColorCount; i++) {
		printf("getting ui_color for index %lu, constant: %ld\n", i, sColorConsts[i]);
		fCurrentSet.SetColor((color_which)sColorConsts[i], ui_color((color_which)sColorConsts[i]));
	}

	fCurrentSet.PrintToStream();

	fPrevSet = fCurrentSet;
}

void APRView::UpdateAllColors(void)
{
	for (uint32 i = 0; i < sColorCount; i++)
		set_ui_color((color_which)sColorConsts[i], 
			fCurrentSet.AttributeToColor((color_which)sColorConsts[i]));
}

void APRView::UpdateCurrentColor(void)
{
	rgb_color col=fPicker->ValueAsColor();
	ColorWhichItem *whichitem = (ColorWhichItem *)fAttrList->ItemAt(fAttrList->CurrentSelection());
	set_ui_color(whichitem->GetAttribute(), col);
}

void APRView::UpdateControlsFromAttr(const char *string)
{
	if (!string)
		return;
	STRACE(("Update color for %s\n",string));

	fPicker->SetValue(fCurrentSet.StringToColor(string));
	fColorWell->SetColor(fPicker->ValueAsColor());
	fColorWell->Invalidate();
}
