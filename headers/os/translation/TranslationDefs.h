/********************************************************************************
/
/      File:           TranslationDefs.h
/
/      Description:    Miscellaneous basic definitions for the Translation Kit
/
/      Copyright 1998, Be Incorporated, All Rights Reserved.
/      Copyright 1995-1997, Jon Watte
/
/      2002 - translation_data struct added by Michael Wilber, OBOS TransKit Team
********************************************************************************/

#if !defined(_TRANSLATION_DEFS_H)
#define _TRANSLATION_DEFS_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <TranslationErrors.h>


typedef unsigned long translator_id;


/*	when you export this struct, end with an empty	*/
/*	record that has 0 for "type"	*/


/*	These are defines, because they reflect the state at which the app was compiled	*/
#define B_TRANSLATION_CURRENT_VERSION	B_BEOS_VERSION
#define B_TRANSLATION_MIN_VERSION		161

extern const char * B_TRANSLATOR_MIME_TYPE;

struct translation_format {
	uint32		type;			/* B_ASCII_TYPE, ...*/
	uint32		group;			/* B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...*/
	float		quality;		/* ability of the format to retain the data of its group (0.0-1.0) */
	float		capability;		/* ability of the translator to decode the format (0.0-1.0) */
	char		MIME[251];		/* MIME string*/
	char		name[251];		/* only descriptive	*/
};


/*	This struct is different from the format struct for a reason:	*/
/*	to separate the notion of formats from the notion of translations	*/

struct translator_info {		/* Info about a specific translation*/
	uint32			type;		/* B_ASCII_TYPE, ...*/
	translator_id	translator;	/* Filled in by BTranslationRoster*/
	uint32			group;		/* B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...*/
	float			quality;	/* ability of the format to retain the data of its group (0.0-1.0) */
	float			capability;	/* ability of the translator to decode the format (0.0-1.0) */
	char			name[251];
	char			MIME[251];
};

// BEGIN: Added by Michael Wilber
struct translator_data {
	const char *translatorName;
	const char *translatorInfo;
	int32 translatorVersion;
	const translation_format *inputFormats;
	const translation_format *outputFormats;

	status_t (*Identify)(BPositionIO *inSource,
		const translation_format *inFormat, BMessage *ioExtension,
		translator_info *outInfo, uint32 outType);
		
	status_t (*Translate)(BPositionIO *inSource,
		const translator_info *inInfo, BMessage *ioExtension,
		uint32 outType, BPositionIO *outDestination);
		
	status_t (*MakeConfig)(BMessage *ioExtension,
		BView **outView, BRect *outExtent);
		
	status_t (*GetConfigMessage)(BMessage *ioExtension);
};

#define TK_MAKE_VERSION(mjr,mnr,rev) ((mjr << 8) & ((mnr << 4) & 0xf0) & (rev & 0x0f))
#define TK_MAJOR_VERSION(v) (v >> 8)
#define TK_MINOR_VERSION(v) ((v >> 4) & 0xf)
#define TK_REVISION_VERSION(v) (v & 0xf)

// END: Added by Michael Wilber

#endif /* _TRANSLATION_DEFS_H */
