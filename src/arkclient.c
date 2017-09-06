#include "arkclient.h"

/// --------------------------------------------------
/// PUBLIC
/// --------------------------------------------------

int ark_client_setEnvironment(ARKNETWORKTYPE networkType)
{
    printf("[ARK CLIENT] Setting NetworkType to '%d'\n", networkType);
    global_networkType = networkType;

    ArkNetwork peerNetworkConfiguration = {0};
    ArkPeer randomPeer = {0};

    int fail = 1;
    int iterations = 5;
    while (iterations > 0 && fail == 1)
    {
        randomPeer = ark_client_get_randomPeer();
        peerNetworkConfiguration = ark_api_network_autoconfigure(randomPeer.ip, randomPeer.port);
        fail = ark_helpers_isNetworkNull(peerNetworkConfiguration);

        iterations--;
    }

    if (fail == 1)
        return 0;

    global_network = peerNetworkConfiguration;
    global_selectedPeer = ark_api_peers_get(randomPeer, randomPeer.ip, randomPeer.port);

    if (ark_helpers_isPeerNull(global_selectedPeer) == 1)
        return 0;

    global_selectedPeerFee = ark_api_blocks_getFee(global_selectedPeer.ip, global_selectedPeer.port);
    if (ark_helpers_isFeeNull(global_selectedPeerFee) == 1)
        return 0;

    return ark_client_filterPeers();
}

/// --------------------------------------------------
/// INTERNAL
/// --------------------------------------------------

int ark_client_filterPeers()
{
    printf("[ARK CLIENT] Filtering peers (valid are ArkPeers with status OK)...\n");

    ArkPeerArray tuple = ark_api_peers(global_selectedPeer.ip, global_selectedPeer.port);

    int maxheight = global_selectedPeer.height;
    printf("[ARK CLIENT] Active Peer with bigger block height: [IP = %s, Port = %d, Height = %d]\n", global_selectedPeer.ip, global_selectedPeer.port, global_selectedPeer.height);

    int numOfValidPeers = 0;
    for (int i=0 ; i<tuple.length ; i++)
    {
        if (tuple.data[i].status == OK)
        {
            numOfValidPeers++;
            if (tuple.data[i].height > maxheight)
            {
                global_selectedPeer = tuple.data[i];
                printf("[ARK CLIENT] Setting new active Peer with bigger block height: [IP = %s, Port = %d, Height = %d]\n", global_selectedPeer.ip, global_selectedPeer.port, global_selectedPeer.height);
            }
        }
    }
    printf("[ARK CLIENT] Filtering peers returned '%d' valid peers...\n", numOfValidPeers);

    return 1;
}

ArkPeer ark_client_get_randomPeer()
{
    ArkPeer peer = {0};

    int peerCount = 0;

    if (global_networkType == MAIN)
        peerCount = sizeof(seedArray) / sizeof(seedArray[0]);
    if (global_networkType == DEVELOPMENT)
        peerCount = sizeof(seedArrayTest) / sizeof(seedArrayTest[0]);

    time_t t;
    srand((unsigned) time(&t));
    int index = rand() % peerCount;

    char* element;
    if (global_networkType == MAIN)
        element = seedArray[index];
    if (global_networkType == DEVELOPMENT)
        element = seedArrayTest[index];

    int x = strchr(element, ':') - element;
    int y = strlen(element) - x - 1;

    char* ip = malloc(sizeof(char));
    strncpy(ip, element, x);
    ip[x] = '\0';

    char* port = malloc(sizeof(char));
    strncpy(port, element + x + 1, y);
    port[y] = '\0';

    peer.ip = ip;
    peer.port = atoi(port);

    element = NULL;
    ip = NULL;
    port = NULL;

    return peer;
}
