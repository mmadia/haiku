/*
 * Copyright 2001-2006, Haiku.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		DarkWyrm <bpmagic@columbus.rr.com>
 */
#ifndef CURSOR_SET_H
#define CURSOR_SET_H


#include <Bitmap.h>
#include <Cursor.h>
#include <Message.h>


typedef enum {
	B_CURSOR_DEFAULT = 1,
	B_CURSOR_TEXT,
	B_CURSOR_MOVE,
	B_CURSOR_DRAG,
	B_CURSOR_RESIZE,
	B_CURSOR_RESIZE_NWSE,
	B_CURSOR_RESIZE_NESW,
	B_CURSOR_RESIZE_NS,
	B_CURSOR_RESIZE_EW,
	B_CURSOR_OTHER,
	B_CURSOR_APP,
	B_CURSOR_INVALID
} cursor_which;

class ServerCursor;


/*!
	\brief Class to manage system cursor sets
*/
class CursorSet : public BMessage {
	public:
		CursorSet(const char *name);

		status_t		Save(const char *path,int32 saveflags=0);
		status_t		Load(const char *path);
		status_t		AddCursor(cursor_which which,const BBitmap *cursor, const BPoint &hotspot);
		status_t		AddCursor(cursor_which which, uint8 *data);
		void			RemoveCursor(cursor_which which);
		status_t		FindCursor(cursor_which which, BBitmap **cursor, BPoint *hotspot);
		status_t		FindCursor(cursor_which which, ServerCursor **cursor);
		void			SetName(const char *name);
		const char		*GetName(void);

	private:
		const char *_CursorWhichToString(cursor_which which);
		BBitmap *_CursorDataToBitmap(uint8 *data);
};

#endif	// CURSOR_SET_H
