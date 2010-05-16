/*
 * Copyright 2007-2009, Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Stephan Aßmus <superstippi@gmx.de>
 */


#include "ProfileMessageSupport.h"

#include <ServerProtocol.h>


void
string_for_message_code(uint32 code, BString& string)
{
	string = "";

	switch (code) {
		// Return the exact name for each constant
		#define CODE(x) case x: string = #x; break

		CODE(AS_GET_DESKTOP);
		CODE(AS_REGISTER_INPUT_SERVER);
		CODE(AS_EVENT_STREAM_CLOSED);

		// Desktop definitions (through the ServerApp, though)
		CODE(AS_GET_WINDOW_LIST);
		CODE(AS_GET_WINDOW_INFO);
		CODE(AS_MINIMIZE_TEAM);
		CODE(AS_BRING_TEAM_TO_FRONT);
		CODE(AS_WINDOW_ACTION);

		// Application definitions
		CODE(AS_CREATE_APP);
		CODE(AS_DELETE_APP);
		CODE(AS_QUIT_APP);
		CODE(AS_ACTIVATE_APP);
		CODE(AS_APP_CRASHED);

		CODE(AS_CREATE_WINDOW);
		CODE(AS_CREATE_OFFSCREEN_WINDOW);
		CODE(AS_DELETE_WINDOW);
		CODE(AS_CREATE_BITMAP);
		CODE(AS_DELETE_BITMAP);
		CODE(AS_GET_BITMAP_OVERLAY_RESTRICTIONS);

		// Cursor commands
		CODE(AS_SET_CURSOR);
		CODE(AS_SET_VIEW_CURSOR);

		CODE(AS_SHOW_CURSOR);
		CODE(AS_HIDE_CURSOR);
		CODE(AS_OBSCURE_CURSOR);
		CODE(AS_QUERY_CURSOR_HIDDEN);

		CODE(AS_CREATE_CURSOR);
		CODE(AS_REFERENCE_CURSOR);
		CODE(AS_DELETE_CURSOR);

		CODE(AS_BEGIN_RECT_TRACKING);
		CODE(AS_END_RECT_TRACKING);
		
		CODE(AS_GET_CURSOR_POSITION);
		CODE(AS_GET_CURSOR_BITMAP);

		// Window definitions
		CODE(AS_SHOW_WINDOW);
		CODE(AS_HIDE_WINDOW);
		CODE(AS_MINIMIZE_WINDOW);
		CODE(AS_QUIT_WINDOW);
		CODE(AS_SEND_BEHIND);
		CODE(AS_SET_LOOK);
		CODE(AS_SET_FEEL);
		CODE(AS_SET_FLAGS);
		CODE(AS_DISABLE_UPDATES);
		CODE(AS_ENABLE_UPDATES);
		CODE(AS_BEGIN_UPDATE);
		CODE(AS_END_UPDATE);
		CODE(AS_NEEDS_UPDATE);
		CODE(AS_SET_WINDOW_TITLE);
		CODE(AS_ADD_TO_SUBSET);
		CODE(AS_REMOVE_FROM_SUBSET);
		CODE(AS_SET_ALIGNMENT);
		CODE(AS_GET_ALIGNMENT);
		CODE(AS_GET_WORKSPACES);
		CODE(AS_SET_WORKSPACES);
		CODE(AS_WINDOW_RESIZE);
		CODE(AS_WINDOW_MOVE);
		CODE(AS_SET_SIZE_LIMITS);
		CODE(AS_ACTIVATE_WINDOW);
		CODE(AS_IS_FRONT_WINDOW);

		// BPicture definitions
		CODE(AS_CREATE_PICTURE);
		CODE(AS_DELETE_PICTURE);
		CODE(AS_CLONE_PICTURE);
		CODE(AS_DOWNLOAD_PICTURE);

		// Font-related server communications
		CODE(AS_SET_SYSTEM_FONT);
		CODE(AS_GET_SYSTEM_FONTS);
		CODE(AS_GET_SYSTEM_DEFAULT_FONT);

		CODE(AS_GET_FONT_LIST_REVISION);
		CODE(AS_GET_FAMILY_AND_STYLES);

		CODE(AS_GET_FAMILY_AND_STYLE);
		CODE(AS_GET_FAMILY_AND_STYLE_IDS);
		CODE(AS_GET_FONT_BOUNDING_BOX);
		CODE(AS_GET_TUNED_COUNT);
		CODE(AS_GET_TUNED_INFO);
		CODE(AS_GET_FONT_HEIGHT);
		CODE(AS_GET_FONT_FILE_FORMAT);
		CODE(AS_GET_EXTRA_FONT_FLAGS);

		CODE(AS_GET_STRING_WIDTHS);
		CODE(AS_GET_EDGES);
		CODE(AS_GET_ESCAPEMENTS);
		CODE(AS_GET_ESCAPEMENTS_AS_FLOATS);
		CODE(AS_GET_BOUNDINGBOXES_CHARS);
		CODE(AS_GET_BOUNDINGBOXES_STRING);
		CODE(AS_GET_BOUNDINGBOXES_STRINGS);
		CODE(AS_GET_HAS_GLYPHS);
		CODE(AS_GET_GLYPH_SHAPES);
		CODE(AS_GET_TRUNCATED_STRINGS);

		// Screen methods
		CODE(AS_VALID_SCREEN_ID);
		CODE(AS_GET_NEXT_SCREEN_ID);
		CODE(AS_SCREEN_GET_MODE);
		CODE(AS_SCREEN_SET_MODE);
		CODE(AS_PROPOSE_MODE);
		CODE(AS_GET_MODE_LIST);

		CODE(AS_GET_PIXEL_CLOCK_LIMITS);
		CODE(AS_GET_TIMING_CONSTRAINTS);

		CODE(AS_SCREEN_GET_COLORMAP);
		CODE(AS_GET_DESKTOP_COLOR);
		CODE(AS_SET_DESKTOP_COLOR);
		CODE(AS_GET_SCREEN_ID_FROM_WINDOW);

		CODE(AS_READ_BITMAP);

		CODE(AS_GET_RETRACE_SEMAPHORE);
		CODE(AS_GET_ACCELERANT_INFO);
		CODE(AS_GET_MONITOR_INFO);
		CODE(AS_GET_FRAME_BUFFER_CONFIG);

		CODE(AS_SET_DPMS);
		CODE(AS_GET_DPMS_STATE);
		CODE(AS_GET_DPMS_CAPABILITIES);

		// Misc stuff
		CODE(AS_GET_ACCELERANT_PATH);
		CODE(AS_GET_DRIVER_PATH);

		// Global function call defs
		CODE(AS_SET_UI_COLORS);
		CODE(AS_SET_UI_COLOR);
		CODE(AS_SET_DECORATOR);
		CODE(AS_GET_DECORATOR);
		case AS_R5_SET_DECORATOR:
			string = "AS_R5_SET_DECORATOR"; break;
		CODE(AS_COUNT_DECORATORS);
		CODE(AS_GET_DECORATOR_NAME);

		CODE(AS_SET_WORKSPACE_LAYOUT);
		CODE(AS_GET_WORKSPACE_LAYOUT);
		CODE(AS_CURRENT_WORKSPACE);
		CODE(AS_ACTIVATE_WORKSPACE);
		CODE(AS_GET_SCROLLBAR_INFO);
		CODE(AS_SET_SCROLLBAR_INFO);
		CODE(AS_GET_MENU_INFO);
		CODE(AS_SET_MENU_INFO);
		CODE(AS_IDLE_TIME);
		CODE(AS_SET_MOUSE_MODE);
		CODE(AS_GET_MOUSE_MODE);
		CODE(AS_SET_FOCUS_FOLLOWS_MOUSE_MODE);
		CODE(AS_GET_FOCUS_FOLLOWS_MOUSE_MODE);
		CODE(AS_SET_ACCEPT_FIRST_CLICK);
		CODE(AS_GET_ACCEPT_FIRST_CLICK);
		CODE(AS_GET_MOUSE);
		CODE(AS_SET_DECORATOR_SETTINGS);
		CODE(AS_GET_DECORATOR_SETTINGS);
		CODE(AS_GET_SHOW_ALL_DRAGGERS);
		CODE(AS_SET_SHOW_ALL_DRAGGERS);

		// Subpixel antialiasing & hinting
		CODE(AS_SET_SUBPIXEL_ANTIALIASING);
		CODE(AS_GET_SUBPIXEL_ANTIALIASING);
		CODE(AS_SET_HINTING);
		CODE(AS_GET_HINTING);
		CODE(AS_SET_SUBPIXEL_AVERAGE_WEIGHT);
		CODE(AS_GET_SUBPIXEL_AVERAGE_WEIGHT);
		CODE(AS_SET_SUBPIXEL_ORDERING);
		CODE(AS_GET_SUBPIXEL_ORDERING);

		// Graphics calls
		CODE(AS_SET_HIGH_COLOR);
		CODE(AS_SET_LOW_COLOR);
		CODE(AS_SET_VIEW_COLOR);

		CODE(AS_STROKE_ARC);
		CODE(AS_STROKE_BEZIER);
		CODE(AS_STROKE_ELLIPSE);
		CODE(AS_STROKE_LINE);
		CODE(AS_STROKE_LINEARRAY);
		CODE(AS_STROKE_POLYGON);
		CODE(AS_STROKE_RECT);
		CODE(AS_STROKE_ROUNDRECT);
		CODE(AS_STROKE_SHAPE);
		CODE(AS_STROKE_TRIANGLE);

		CODE(AS_FILL_ARC);
		CODE(AS_FILL_ARC_GRADIENT);
		CODE(AS_FILL_BEZIER);
		CODE(AS_FILL_BEZIER_GRADIENT);
		CODE(AS_FILL_ELLIPSE);
		CODE(AS_FILL_ELLIPSE_GRADIENT);
		CODE(AS_FILL_POLYGON);
		CODE(AS_FILL_POLYGON_GRADIENT);
		CODE(AS_FILL_RECT);
		CODE(AS_FILL_RECT_GRADIENT);
		CODE(AS_FILL_REGION);
		CODE(AS_FILL_REGION_GRADIENT);
		CODE(AS_FILL_ROUNDRECT);
		CODE(AS_FILL_ROUNDRECT_GRADIENT);
		CODE(AS_FILL_SHAPE);
		CODE(AS_FILL_SHAPE_GRADIENT);
		CODE(AS_FILL_TRIANGLE);
		CODE(AS_FILL_TRIANGLE_GRADIENT);

		CODE(AS_DRAW_STRING);
		CODE(AS_DRAW_STRING_WITH_DELTA);

		CODE(AS_SYNC);

		CODE(AS_VIEW_CREATE);
		CODE(AS_VIEW_DELETE);
		CODE(AS_VIEW_CREATE_ROOT);
		CODE(AS_VIEW_SHOW);
		CODE(AS_VIEW_HIDE);
		CODE(AS_VIEW_MOVE);
		CODE(AS_VIEW_RESIZE);
		CODE(AS_VIEW_DRAW);

		// View definitions
		CODE(AS_VIEW_GET_COORD);
		CODE(AS_VIEW_SET_FLAGS);
		CODE(AS_VIEW_SET_ORIGIN);
		CODE(AS_VIEW_GET_ORIGIN);
		CODE(AS_VIEW_RESIZE_MODE);
		CODE(AS_VIEW_BEGIN_RECT_TRACK);
		CODE(AS_VIEW_END_RECT_TRACK);
		CODE(AS_VIEW_DRAG_RECT);
		CODE(AS_VIEW_DRAG_IMAGE);
		CODE(AS_VIEW_SCROLL);
		CODE(AS_VIEW_SET_LINE_MODE);
		CODE(AS_VIEW_GET_LINE_MODE);
		CODE(AS_VIEW_PUSH_STATE);
		CODE(AS_VIEW_POP_STATE);
		CODE(AS_VIEW_SET_SCALE);
		CODE(AS_VIEW_GET_SCALE);
		CODE(AS_VIEW_SET_DRAWING_MODE);
		CODE(AS_VIEW_GET_DRAWING_MODE);
		CODE(AS_VIEW_SET_BLENDING_MODE);
		CODE(AS_VIEW_GET_BLENDING_MODE);
		CODE(AS_VIEW_SET_PEN_LOC);
		CODE(AS_VIEW_GET_PEN_LOC);
		CODE(AS_VIEW_SET_PEN_SIZE);
		CODE(AS_VIEW_GET_PEN_SIZE);
		CODE(AS_VIEW_SET_HIGH_COLOR);
		CODE(AS_VIEW_SET_LOW_COLOR);
		CODE(AS_VIEW_SET_VIEW_COLOR);
		CODE(AS_VIEW_GET_HIGH_COLOR);
		CODE(AS_VIEW_GET_LOW_COLOR);
		CODE(AS_VIEW_GET_VIEW_COLOR);
		CODE(AS_VIEW_PRINT_ALIASING);
		CODE(AS_VIEW_CLIP_TO_PICTURE);
		CODE(AS_VIEW_GET_CLIP_REGION);
		CODE(AS_VIEW_DRAW_BITMAP);
		CODE(AS_VIEW_SET_EVENT_MASK);
		CODE(AS_VIEW_SET_MOUSE_EVENT_MASK);

		CODE(AS_VIEW_DRAW_STRING);
		CODE(AS_VIEW_SET_CLIP_REGION);
		CODE(AS_VIEW_LINE_ARRAY);
		CODE(AS_VIEW_BEGIN_PICTURE);
		CODE(AS_VIEW_APPEND_TO_PICTURE);
		CODE(AS_VIEW_END_PICTURE);
		CODE(AS_VIEW_COPY_BITS);
		CODE(AS_VIEW_DRAW_PICTURE);
		CODE(AS_VIEW_INVALIDATE_RECT);
		CODE(AS_VIEW_INVALIDATE_REGION);
		CODE(AS_VIEW_INVERT_RECT);
		CODE(AS_VIEW_MOVE_TO);
		CODE(AS_VIEW_RESIZE_TO);
		CODE(AS_VIEW_SET_STATE);
		CODE(AS_VIEW_SET_FONT_STATE);
		CODE(AS_VIEW_GET_STATE);
		CODE(AS_VIEW_SET_VIEW_BITMAP);
		CODE(AS_VIEW_SET_PATTERN);
		CODE(AS_SET_CURRENT_VIEW);

		// BDirectWindow codes
		CODE(AS_DIRECT_WINDOW_GET_SYNC_DATA);
		CODE(AS_DIRECT_WINDOW_SET_FULLSCREEN);

		default:
			string << "unkown code: " << code;
			break;
	}
}


