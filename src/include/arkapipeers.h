#ifndef __arkapipeers_h__
#define __arkapipeers_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - PEER(S) FUNCTIONS
/// --------------------------------------------------

ArkPeerArray ark_api_peers(char* ip, int port);

ArkPeerArray ark_api_peers_getList(char* ip, int port);

ArkPeer ark_api_peers_get(ArkPeer peer, char *ip, int port);

ArkPeerStatus ark_api_peers_getStatus(char* ip, int port);

#endif /* __arkapipeers_h__ */
