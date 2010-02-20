/*
 * Copyright (C) 2007 Ryan Leavengood <leavengood@gmail.com>
 * Copyright (C) 2010 Stephan Aßmus <superstippi@gmx.de>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LauncherApp_h
#define LauncherApp_h

#include <Application.h>
#include <Rect.h>

class BFile;
class DownloadWindow;
class LauncherWindow;

enum {
    CREATE_WEBVIEW = 'crwb'
};

class LauncherApp : public BApplication {
public:
    LauncherApp();
    virtual ~LauncherApp();

    virtual void AboutRequested();
    virtual void ArgvReceived(int32, char**);
    virtual void MessageReceived(BMessage*);
    virtual void RefsReceived(BMessage*);
    virtual void ReadyToRun();
    virtual bool QuitRequested();

private:
	bool openSettingsFile(BFile& file, uint32 mode);
	void newWindow(const BString& url);

    int m_windowCount;
    BRect m_lastWindowFrame;
    BMessage* m_launchRefsMessage;
    bool m_initialized;

    DownloadWindow* m_downloadWindow;
};

extern const char* kApplicationSignature;

#endif // LauncherApp_h

