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
    ArkRestResponse *ars = ark_api_get(url, NULL);

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

ArkLoaderStatus ark_api_loader_status(char *ip, int port)
{
    printf("[%s][ARK API] Getting loader status for an ArkPeer: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    sprintf(url, "%s:%d/api/loader/status", ip, port);

    ArkLoaderStatus status = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return status;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return status;

    status = ark_helpers_getArkLoaderStatus_fromJSON(root);

    free(root);
    ars = NULL;

    return status;
}

ArkLoaderSyncStatus ark_api_loader_statusSync(char *ip, int port)
{
    printf("[%s][ARK API] Getting loader sync status for an ArkPeer: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    sprintf(url, "%s:%d/api/loader/status/sync", ip, port);

    ArkLoaderSyncStatus syncStatus = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return syncStatus;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return syncStatus;

    syncStatus = ark_helpers_getArkLoaderSyncStatus_fromJSON(root);

    free(root);
    ars = NULL;

    return syncStatus;
}
