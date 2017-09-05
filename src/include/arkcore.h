#include "arkapiaccounts.h"
#include "arkapiblocks.h"
#include "arkapidelegates.h"
#include "arkapifees.h"
#include "arkapinetworks.h"
#include "arkapipeers.h"
#include "arkapitransactions.h"
#include "arkapivoters.h"

ARKNETWORKTYPE global_networkType;
ArkNetwork global_network;
ArkPeer* global_filteredPeers;
ArkPeer global_selectedPeer;
ArkFee global_selectedPeerFee;

/// --------------------------------------------------
/// PUBLIC
/// --------------------------------------------------

int ark_core_setEnvironment(ARKNETWORKTYPE networkType);

/// --------------------------------------------------
/// INTERNAL
/// --------------------------------------------------

int ark_core_filterPeers();

ArkPeer ark_core_get_randomPeer();
