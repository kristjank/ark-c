#ifndef __arkapidelegates_h__
#define __arkapidelegates_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - DELEGATE(S) FUNCTIONS
/// --------------------------------------------------

ArkDelegateArray ark_api_delegates(char* ip, int port);

ArkDelegate ark_api_delegates_getByUsername(char* ip, int port, char* username);

// api/delegates/forging/getForgedByAccount

#endif /* __arkapidelegates_h__ */
