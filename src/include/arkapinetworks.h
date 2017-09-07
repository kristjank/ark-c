#ifndef __arkapinetworks_h__
#define __arkapinetworks_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - NETWORK(S) FUNCTIONS
/// --------------------------------------------------

ArkNetwork ark_api_network_autoconfigure(char *ip, int port);

ArkLoaderStatus ark_api_loader_status(char *ip, int port);

ArkLoaderSyncStatus ark_api_loader_statusSync(char *ip, int port);

#endif /* __arkapinetworks_h__ */
