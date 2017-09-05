#ifndef __arkapitransactions_h__
#define __arkapitransactions_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - TRANSACTION(S) FUNCTIONS
/// --------------------------------------------------

ArkTransactionArray ark_api_transactions();

ArkTransactionArray ark_api_transactions_unconfirmed();

ArkTransaction ark_api_transactions_get(char* id);

ArkTransaction ark_api_transactions_getUnconfirmed(char* id);

#endif /* __arkapitransactions_h__ */
