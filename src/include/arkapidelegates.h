#ifndef __arkapidelegates_h__
#define __arkapidelegates_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - DELEGATE(S) FUNCTIONS
/// --------------------------------------------------

ArkDelegateArray ark_api_delegates(char* ip, int port);

ArkDelegate ark_api_delegates_get(char* ip, int port, char* username);

ArkVoterArray ark_api_delegates_voters(char* ip, int port, char* publicKey);

ArkForgedDetails ark_api_delegates_getForgedData(char* ip, int port, char* publicKey);

#endif /* __arkapidelegates_h__ */
