#ifndef __arkapitransactions_h__
#define __arkapitransactions_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - TRANSACTION(S) FUNCTIONS
/// --------------------------------------------------

ArkTransactionArray ark_api_transactions(char* ip, int port);

ArkTransactionArray ark_api_transactions_unconfirmed(char* ip, int port);

ArkTransaction ark_api_transactions_get(char* ip, int port, char* id);

ArkTransaction ark_api_transactions_getUnconfirmed(char* ip, int port, char* id);

#endif /* __arkapitransactions_h__ */
