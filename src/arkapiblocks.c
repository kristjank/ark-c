#include "arkapiblocks.h"

/// --------------------------------------------------
/// ARK API - BLOCK(S) FUNCTIONS
/// --------------------------------------------------

//ArkBlockHeight ark_api_blocks_getLastBlockHeight()

ArkBlockHeight ark_api_blocks_getHeight(char* ip, int port)
{
    printf("[ARK API] Getting ArkPeers height: [IP = %s, Port = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getHeight", ip, port);

    ArkBlockHeight arkblockheight = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return arkblockheight;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return arkblockheight;

    arkblockheight.id = json_object_get_string(json_object_object_get(root, "id"));
    arkblockheight.height = json_object_get_int(json_object_object_get(root, "height"));

    free(root);
    ars = NULL;

    return arkblockheight;
}

char* ark_api_blocks_getEpoch(char* ip, int port)
{
    printf("[ARK API] Getting ArkBlock Epoch: [IP = %s, Port = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getEpoch", ip, port);

    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return NULL;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return NULL;

    char* time = "";
    time = json_object_get_string(json_object_object_get(root, "epoch"));

    free(root);
    ars = NULL;

    return time;
}

int ark_api_blocks_getFee(char *ip, int port)
{
    printf("[ARK API] Getting ArkFee from: [IP = %s, Port = %d]\n", ip, port);

    int fee = -1;
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getFee", ip, port);

    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return fee;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return fee;

    fee = json_object_get_int(json_object_object_get(root, "fee"));

    free(root);
    ars = NULL;

    return fee;
}

char *ark_api_blocks_getNethash(char* ip, int port)
{
    printf("[ARK API] Getting NetHash from: [IP = %s, Port = %d]\n", ip, port);

    char* nethash = "";
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getNethash", ip, port);

    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return nethash;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return nethash;

    nethash = json_object_get_string(json_object_object_get(root, "nethash"));

    free(root);
    ars = NULL;

    return nethash;
}

int ark_blocks_getMilestone(char *ip, int port)
{
    printf("[ARK API] Getting milestone from: [IP = %s, Port = %d]\n", ip, port);

    int milestone = -1;
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getMilestone", ip, port);

    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return milestone;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return milestone;

    milestone = json_object_get_int(json_object_object_get(root, "milestone"));

    free(root);
    ars = NULL;

    return milestone;
}
