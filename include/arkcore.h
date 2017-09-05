#include "arkapi.h"

ARKNETWORKTYPE global_networkType;
ArkNetwork global_network;
ArkPeer* global_filteredPeers;
ArkPeer global_selectedPeer;
ArkFee global_selectedPeerFee;

/// --------------------------------------------------
/// PUBLIC
/// --------------------------------------------------

int ark_core_setEnvrionment(ARKNETWORKTYPE networkType);

/// --------------------------------------------------
/// INTERNAL
/// --------------------------------------------------

int ark_core_filterPeers();

ArkPeer ark_core_get_randomPeer();
