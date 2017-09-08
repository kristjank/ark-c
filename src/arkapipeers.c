#include "arkapipeers.h"

/// --------------------------------------------------
/// ARK API - PEER(S) FUNCTIONS
/// --------------------------------------------------

ArkPeerArray ark_api_peers(char* ip, int port)
{
    printf("[%s][ARK API] Getting peers: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peers", ip, port);

    ArkPeerArray apa = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return apa;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return apa;

    array_list *peers = json_object_object_get(root, "peers");
    int total = json_object_array_length(peers);

    ArkPeer *data = malloc(total * sizeof(ArkPeer));
    if (!data)
        return apa;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkPeer_fromJSON(json_object_array_get_idx(peers, i));
    }

    apa.length = total;
    apa.data = data;

    free(peers);
    free(root);
    ars = NULL;

    return apa;
}

ArkPeerArray ark_api_peers_getList(char* ip, int port)
{
    printf("[%s][ARK API] Getting peer list: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/peer/list", ip, port);

    ArkPeerArray apa = {0};
    ArkRestResponse *ars = ark_api_get(url, ark_client_getApiHeaders());

    if (ars->size == 0 || ars->data == NULL)
        return apa;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return apa;

    array_list *peers = json_object_object_get(root, "peers");
    int total = json_object_array_length(peers);

    ArkPeer *data = malloc(total * sizeof(ArkPeer));
    if (!data)
        return apa;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkPeer_fromJSON(json_object_array_get_idx(peers, i));
    }

    apa.length = total;
    apa.data = data;

    free(peers);
    free(root);
    ars = NULL;

    return apa;
}

ArkPeer ark_api_peers_get(ArkPeer peer, char *ip, int port)
{
    printf("[%s][ARK API] Getting ArkPeer details: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peers/get?port=%d&ip=%s", peer.ip, peer.port, port, ip);

    ArkPeer arkpeer = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return arkpeer;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return arkpeer;

    json_object *peerJson = json_object_object_get(root, "peer");

    arkpeer = ark_helpers_getArkPeer_fromJSON(peerJson);

    free(peerJson);
    free(root);
    ars = NULL;

    return arkpeer;
}

ArkPeerStatus ark_api_peers_getStatus(char* ip, int port)
{
    printf("[%s][ARK API] Getting ArkPeer status: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/peer/status?port=%d&ip=%s", ip, port, port, ip);

    ArkPeerStatus aps = {0};
    ArkRestResponse *ars = ark_api_get(url, ark_client_getApiHeaders());

    if (ars->size == 0 || ars->data == NULL)
        return aps;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return aps;

    aps = ark_helpers_getArkPeerStatus_fromJSON(root);
    
    free(root);
    ars = NULL;

    return aps;
}
