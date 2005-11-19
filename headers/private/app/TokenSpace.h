/*
 * Copyright 2001-2005, Haiku.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Erik Jaesler (erik@cgsoftware.com)
 *		Axel Dörfler, axeld@pinc-software.de
 */
#ifndef _TOKEN_SPACE_H
#define _TOKEN_SPACE_H


#include <map>
#include <stack>

#include <BeBuild.h>
#include <Locker.h>
#include <SupportDefs.h>


// token types as specified in targets
#define B_PREFERRED_TOKEN	-2		/* A little bird told me about this one */
#define B_NULL_TOKEN		-1
#define B_ANY_TOKEN			0

// token types in the token list
#define B_HANDLER_TOKEN		1
#define B_SERVER_TOKEN		2


namespace BPrivate {

typedef void (*new_token_callback)(int16, void*);
typedef void (*remove_token_callback)(int16, void*);
typedef bool (*get_token_callback)(int16, void*);

class BTokenSpace : public BLocker {
	public:
		BTokenSpace();
		~BTokenSpace();

		int32		NewToken(int16 type, void* object,
						new_token_callback callback = NULL);
		bool		RemoveToken(int32 token, remove_token_callback callback = NULL);
		bool		CheckToken(int32 token, int16 type) const;
		status_t	GetToken(int32 token, int16 type, void** object,
						get_token_callback callback = NULL) const;

	private:
		struct token_info {
			int16	type;
			void*	object;
		};
		typedef std::map<int32, token_info> TokenMap;

		TokenMap	fTokenMap;
		int32		fTokenCount;
};

extern _IMPEXP_BE BTokenSpace gDefaultTokens;

}	// namespace BPrivate

#endif	// _TOKEN_SPACE_H
