#ifndef __arkapivoters_h__
#define __arkapivoters_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - VOTER(S) FUNCTIONS
/// --------------------------------------------------

ArkVoterArray ark_api_voters_getByDelegate(char* ip, int port, char* publicKey);

#endif /* __arkapivoters_h__ */
