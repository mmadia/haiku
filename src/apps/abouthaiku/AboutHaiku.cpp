/*
 * Copyright (c) 2005, Haiku, Inc.
 * Distributed under the terms of the MIT license.
 *
 * Author: DarkWyrm <bpmagic@columbus.rr.com>
 */


#include <AppFileInfo.h>
#include <Application.h>
#include <Bitmap.h>
#include <File.h>
#include <Font.h>
#include <MessageRunner.h>
#include <Messenger.h>
#include <OS.h>
#include <Screen.h>
#include <ScrollView.h>
#include <String.h>
#include <TextView.h>
#include <TranslationUtils.h>
#include <StringView.h>
#include <View.h>
#include <Window.h>

#include <cpu_type.h>

#include <stdio.h>


#define SCROLL_CREDITS_VIEW 'mviv'


static const char *UptimeToString(char string[], size_t size);


class AboutApp : public BApplication {
	public:
		AboutApp(void);
};

class AboutWindow : public BWindow {
	public:
				AboutWindow(void);
		bool	QuitRequested(void);
};

class AboutView : public BView {
	public:
				AboutView(const BRect &r);
				~AboutView(void);
				
		virtual void AttachedToWindow();
		virtual void Pulse();
		
		virtual void FrameResized(float width, float height);
		virtual void Draw(BRect update);
		virtual void MessageReceived(BMessage *msg);
		virtual void MouseDown(BPoint pt);

	private:
		BStringView		*fUptimeView;
		BView			*fInfoView;
		BTextView		*fCreditsView;
		
		BBitmap			*fLogo;
		
		BPoint			fDrawPoint;
		
		bigtime_t		fLastActionTime;
		BMessageRunner	*fScrollRunner;
};


//	#pragma mark -


AboutApp::AboutApp(void)
	: BApplication("application/x-vnd.haiku-AboutHaiku")
{
	AboutWindow *window = new AboutWindow();
	window->Show();
}


//	#pragma mark -


AboutWindow::AboutWindow()
	: BWindow(BRect(0, 0, 500, 300), "About Haiku", B_TITLED_WINDOW, 
			B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	AddChild(new AboutView(Bounds()));

	MoveTo((BScreen().Frame().Width() - Bounds().Width()) / 2,
		(BScreen().Frame().Height() - Bounds().Height()) / 2 );
}


bool
AboutWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


AboutView::AboutView(const BRect &r)
	: BView(r, "aboutview", B_FOLLOW_ALL, B_WILL_DRAW | B_PULSE_NEEDED),
	fLastActionTime(system_time()),
	fScrollRunner(NULL)
{
	fLogo = BTranslationUtils::GetBitmap('PNG ', "haikulogo.png");
	if (fLogo) {
		fDrawPoint.x = (225-fLogo->Bounds().Width()) / 2;
		fDrawPoint.y = 0;
	}

	// Begin Construction of System Information controls

	font_height height;
	float labelHeight, textHeight;
	char string[255];

	system_info systemInfo;
	get_system_info(&systemInfo);

	be_plain_font->GetHeight(&height);
	textHeight = height.ascent + height.descent + height.leading;

	be_bold_font->GetHeight(&height);
	labelHeight = height.ascent + height.descent + height.leading;

	BRect r(0, 0, 225, Bounds().bottom);
	if (fLogo)
		r.OffsetBy(0, fLogo->Bounds().Height());

	fInfoView = new BView(r, "infoview", B_FOLLOW_LEFT | B_FOLLOW_TOP_BOTTOM, B_WILL_DRAW);
	fInfoView->SetViewColor(235, 235, 235);
	AddChild(fInfoView);

	// Add all the various labels for system infomation

	BStringView *stringView;

	// OS Version
	r.Set(5, 5, 225, labelHeight + 5);
	stringView = new BStringView(r, "oslabel", "Version:");
	stringView->SetFont(be_bold_font);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;

	// the version is stored in the BEOS:APP_VERSION attribute of libbe.so
	BFile file("/boot/beos/system/lib/libbe.so", B_READ_ONLY);
	if (file.InitCheck() == B_OK) {
		BAppFileInfo appFileInfo;
		version_info versionInfo;

		if (appFileInfo.SetTo(&file) == B_OK
			&& appFileInfo.GetVersionInfo(&versionInfo, B_APP_VERSION_KIND) == B_OK)
			strcpy(string, versionInfo.short_info);
		else
			strcpy(string, "Unknown");
	}

	stringView = new BStringView(r, "ostext", string);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	// CPU count, type and clock speed
	r.OffsetBy(0, textHeight * 1.5);
	r.bottom = r.top + labelHeight;

	if (systemInfo.cpu_count > 1)
		sprintf(string, "%ld Processors:", systemInfo.cpu_count);
	else
		strcpy(string, "Processor:");

	stringView = new BStringView(r, "cpulabel", string);
	stringView->SetFont(be_bold_font);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();


	BString cpuType;
	cpuType << get_cpu_vendor_string(systemInfo.cpu_type) 
		<< " " << get_cpu_model_string(systemInfo.cpu_type);

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;
	stringView = new BStringView(r, "cputext", cpuType.String());
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;

	if (systemInfo.cpu_clock_speed < 1000000000)
		sprintf(string,"%d MHz", int(systemInfo.cpu_clock_speed / 1000000.0f));
	else
		sprintf(string,"%.2f GHz", systemInfo.cpu_clock_speed / 1000000000.0f);

	stringView = new BStringView(r, "mhztext", string);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	// RAM
	r.OffsetBy(0, textHeight * 1.5);
	r.bottom = r.top + labelHeight;
	stringView = new BStringView(r, "ramlabel", "Memory:");
	stringView->SetFont(be_bold_font);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;

	sprintf(string, "%d MB total", int(systemInfo.max_pages / 256.0f + 0.5f));

	stringView = new BStringView(r, "ramtext", string);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	// Kernel build time/date
	r.OffsetBy(0, textHeight * 1.5);
	r.bottom = r.top + labelHeight;
	stringView = new BStringView(r, "kernellabel", "Kernel:");
	stringView->SetFont(be_bold_font);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;

	sprintf(string, "%s %s", systemInfo.kernel_build_date, systemInfo.kernel_build_time);

	stringView = new BStringView(r, "kerneltext", string);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	// Uptime
	r.OffsetBy(0, textHeight * 1.5);
	r.bottom = r.top + labelHeight;
	stringView = new BStringView(r, "uptimelabel", "Time Running:");
	stringView->SetFont(be_bold_font);
	fInfoView->AddChild(stringView);
	stringView->ResizeToPreferred();

	r.OffsetBy(0, labelHeight);
	r.bottom = r.top + textHeight;
	
	fUptimeView = new BStringView(r, "uptimetext", "");
	fInfoView->AddChild(fUptimeView);
	
	char uptimeString[255];
	fUptimeView->SetText(UptimeToString(uptimeString, 255));
	
	// Begin construction of the credits view
	r = Bounds();
	r.left += fInfoView->Bounds().right;
	r.right -= B_V_SCROLL_BAR_WIDTH;

	fCreditsView = new BTextView(r, "credits",
		r.OffsetToCopy(0, 0).InsetByCopy(5, 5), B_FOLLOW_ALL);
	fCreditsView->SetFlags(fCreditsView->Flags() | B_FRAME_EVENTS );
	fCreditsView->SetStylable(true);
	fCreditsView->MakeEditable(false);
	fCreditsView->SetWordWrap(true);

	BScrollView *creditsScroller = new BScrollView("creditsScroller",
		fCreditsView, B_FOLLOW_ALL, B_WILL_DRAW | B_FRAME_EVENTS, false, true, B_PLAIN_BORDER);
	AddChild(creditsScroller);


	rgb_color darkgrey 		= { 100, 100, 100, 255 };
	rgb_color haiku_green 	= {  42, 131,  36, 255 };
	rgb_color haiku_orange 	= { 255,  69,   0, 255 };
	rgb_color haiku_yellow  = { 255, 176,   0, 255 };

	BFont font(be_bold_font);
	font.SetSize(font.Size() + 4);

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_green);
	fCreditsView->Insert("Haiku\n");

	font.SetSize(be_bold_font->Size());
	font.SetFace(B_BOLD_FACE | B_ITALIC_FACE);

	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert("Copyright " B_UTF8_COPYRIGHT "2001-2005 Haiku, Inc.\n\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_orange);
	fCreditsView->Insert("Team Leads:\n");

	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Bruno G. Albuquerque\n"
		"DarkWyrm\n"
		"Axel Dörfler\n"
		"Phil Greenway\n"
		"Philippe Houdoin\n"
		"Kurtis Kopf\n"
		"Marcus Overhagen\n"
		"Michael Pfeiffer\n"
		"Ingo Weinhold\n"
		"Michael Wilber\n"
		"\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_orange);
	fCreditsView->Insert("Developers:\n");

	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Stephan Aßmus\n"
		"Andrew Bachmann\n"
		"Stefano Ceccherini\n"
		"Rudolf Cornelissen\n"
		"Jérôme Duval\n"
		"Matthijs Hollemans\n"
		"Thomas Kurschel\n"
		"Adi Oanca\n"
		"Niels Reedijk\n"
		"\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_orange);
	fCreditsView->Insert("Contributors:\n");

	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Bruce Cameron\n"
		"Tyler Dauwalder\n"
		"Oliver Ruiz Dorantes\n"
		"Cian Duffy\n"
		"Marc Flerackers\n"
		"Daniel Furrer\n"
		"Erik Jaesler\n"
		"Marcin Konicki\n"
		"Elad Lahav\n"
		"Santiago Lema\n"
		"Oscar Lesta\n"
		"Jerome Leveque\n"
		"Michael Lotz\n"
		"Graham MacDonald\n"
		"Brian Matzon\n"
		"Christopher ML Zumwalt May\n"
		"Andrew McCall\n"
		"David McPaul\n"
		"Misza\n"
		"MrSiggler\n"
		"Alan Murta\n"
		"Frans Van Nispen\n"
		"Pahtz\n"
		"Michael Phipps\n"
		"Jeremy Rand\n"
		"David Reid\n"
		"Daniel Reinhold\n"
		"François Revol\n"
		"Thomas Roell\n"
		"Rafael Romo\n"
		"Zousar Shaker\n"
		"Daniel Switkin\n"
		"Atsushi Takamatsu\n"
		"Jason Vandermark\n"
		"Sandor Vroemisse\n"
		"Nathan Whitehorn\n"
		"Ulrich Wimboeck\n"
		"Gabe Yoder\n"
		"\n" B_UTF8_ELLIPSIS " and probably some more we forgot to mention (sorry!)"
		"\n\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_orange);
	fCreditsView->Insert("Special Thanks To:\n");

	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert("Michael Phipps (project founder)\n\n");

	font.SetSize(be_bold_font->Size() + 4);
	font.SetFace(B_BOLD_FACE);
	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_green);
	fCreditsView->Insert("\nCopyrights\n\n");

	font.SetSize(be_bold_font->Size());
	font.SetFace(B_BOLD_FACE | B_ITALIC_FACE);

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("AntiGrain Geometry\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert("Copyright (C) 2002-2005 Maxim Shemanarev (McSeem)\n\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("PDFLib\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Copyright (c) 1997-2005 PDFlib GmbH and Thomas Merz. "
		"All rights reserved.\n"
		"PDFlib and the PDFlib logo are registered trademarks of PDFlib GmbH.\n\n");

	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("FreeType2\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert("Portions of this software are copyright (C) 1996-2002 The FreeType"
		" Project (www.freetype.org).  All rights reserved.\n\n");

	// Mesa3D (http://www.mesa3d.org) copyrights
	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("Mesa\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Copyright (c) 1999-2005 Brian Paul. "
		"Mesa3D project (www.mesa3d.org).  All rights reserved.\n\n");

	// SGI's GLU implementation copyrights
	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("GLU\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Copyright (c) 1991-2000 Silicon Graphics, Inc. "
		"SGI's Software FreeB license.  All rights reserved.\n\n");

	// GLUT implementation copyrights
	fCreditsView->SetFontAndColor(&font, B_FONT_ALL, &haiku_yellow);
	fCreditsView->Insert("GLUT\n");
	fCreditsView->SetFontAndColor(be_plain_font, B_FONT_ALL, &darkgrey);
	fCreditsView->Insert(
		"Copyright (c) 1994-1997 Mark Kilgard. "
		"All rights reserved.\n"
		"Copyright (c) 1997 Be Inc.\n"
		"Copyright (c) 1999 Jake Hamby. \n\n");
}


AboutView::~AboutView(void)
{
	delete fScrollRunner;
}


void
AboutView::AttachedToWindow(void)
{
	BView::AttachedToWindow();
	Window()->SetPulseRate(500000);
	SetEventMask(B_POINTER_EVENTS);
}


void
AboutView::MouseDown(BPoint pt)
{
	BRect r(92, 26, 105, 31);
	if (r.Contains(pt))
		printf("Easter Egg\n");
	
	if (Bounds().Contains(pt)) {
		fLastActionTime = system_time();
		delete fScrollRunner;
		fScrollRunner = NULL;
	}
}


void
AboutView::FrameResized(float width, float height)
{
	BRect r = fCreditsView->Bounds();
	r.OffsetTo(B_ORIGIN);
	r.InsetBy(3, 3);
	fCreditsView->SetTextRect(r);
}


void
AboutView::Draw(BRect update)
{
	if (fLogo)
		DrawBitmap(fLogo, fDrawPoint);
}


void
AboutView::Pulse(void)
{
	char uptime[255];
	fUptimeView->SetText(UptimeToString(uptime, 255));
	
	if (fScrollRunner == NULL && (system_time() > fLastActionTime + 10000000)) {
		BMessage message(SCROLL_CREDITS_VIEW);
		//fScrollRunner = new BMessageRunner(this, &message, 300000, -1);
	}
}


void
AboutView::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
		case SCROLL_CREDITS_VIEW:
		{
			BScrollBar *scrollBar = fCreditsView->ScrollBar(B_VERTICAL);
			if (scrollBar == NULL)
				break;
			float max, min;
			scrollBar->GetRange(&min, &max);
			if (scrollBar->Value() < max)
				fCreditsView->ScrollBy(0, 5);
			
			break;
		}
		
		default:
			BView::MessageReceived(msg);
			break;
	}
}


//	#pragma mark -


static const char *
UptimeToString(char string[], size_t size)
{
	int64 days, hours, minutes, seconds, remainder;
	int64 systime = system_time();

	days = systime / 86400000000LL;
	remainder = systime % 86400000000LL;

	hours = remainder / 3600000000LL;
	remainder = remainder % 3600000000LL;

	minutes = remainder / 60000000;
	remainder = remainder % 60000000;

	seconds = remainder / 1000000;

	char *str = string;
	if (days) {
		str += snprintf(str, size, "%lld day%s",days, days > 1 ? "s" : "");
	}
	if (hours) {
		str += snprintf(str, size - strlen(string), "%s%lld hour%s",
				str != string ? ", " : "",
				hours, hours > 1 ? "s" : "");	
	}
	if (minutes) {
		str += snprintf(str, size - strlen(string), "%s%lld minute%s",
				str != string ? ", " : "",
				minutes, minutes > 1 ? "s" : "");	
	}
	// Always show second(s)...
	str += snprintf(str, size - strlen(string), "%s%lld second%s",
				str != string ? ", " : "",
				seconds, seconds > 1 ? "s" : "");	

	return string;
}


int
main()
{
	AboutApp app;
	app.Run();
	return 0;
}

