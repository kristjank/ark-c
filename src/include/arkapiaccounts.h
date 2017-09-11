#ifndef __arkapiaccounts_h__
#define __arkapiaccounts_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - ACCOUNT(S) FUNCTIONS
/// --------------------------------------------------

//ArkAccount ark_api_accounts_getByAddress()

ArkAccount ark_api_accounts(char* ip, int port, char* address);

ArkAccountBalance ark_api_accounts_getBalance(char* ip, int port, char* address);

char* ark_api_accounts_getPublicKey(char *ip, int port, char *address);

ArkDelegateArray ark_api_accounts_getDelegates(char *ip, int port, char *address);

#endif /* __arkapiaccounts_h__ */
