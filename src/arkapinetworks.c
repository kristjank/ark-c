#include "arkapinetworks.h"

/// --------------------------------------------------
/// ARK API - NETWORK(S) FUNCTIONS
/// --------------------------------------------------

ArkNetwork ark_api_network_autoconfigure(char *ip, int port)
{
    printf("[%s][ARK API] Getting network configuration for an ArkPeer: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    sprintf(url, "%s:%d/api/loader/autoconfigure", ip, port);

    /// Alternative of string concatenating
    //size_t len = (size_t)snprintf(NULL, 0, "%s:%d/api/loader/autoconfigure", ip, port) + 1;
    //char* url = malloc(len);
    //snprintf(url, len, "%s:%d/api/loader/autoconfigure", ip, port);

    ArkNetwork network = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return network;

    json_object *root = json_tokener_parse(ars->data);
    
    if (ark_helpers_isResponseSuccess(root) == 0)
        return network;

    json_object *networkJson = json_object_object_get(root, "network");
    network = ark_helpers_getArkNetwork_fromJSON(networkJson);
        
    free(networkJson);
    free(root);
    ars = NULL;

    return network;
}
