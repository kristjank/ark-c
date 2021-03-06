#include "arkapiaccounts.h"
#include "arkapiblocks.h"
#include "arkapidelegates.h"
#include "arkapinetworks.h"
#include "arkapipeers.h"
#include "arkapitransactions.h"

ARKNETWORKTYPE global_networkType;
ArkNetwork global_network;
ArkPeer* global_filteredPeers;
ArkPeer global_selectedPeer;
ArkFee global_selectedPeerFee;
int global_selectedPeerFee_value;

/// --------------------------------------------------
/// PUBLIC
/// --------------------------------------------------

int ark_client_setEnvironment(ARKNETWORKTYPE networkType);

/// --------------------------------------------------
/// INTERNAL
/// --------------------------------------------------

int ark_client_filterPeers();

ArkPeer ark_client_get_randomPeer();

struct curl_slist* ark_client_getApiHeaders();
