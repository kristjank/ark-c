#include "arkapiblocks.h"

/// --------------------------------------------------
/// ARK API - BLOCK(S) FUNCTIONS
/// --------------------------------------------------

ArkFee ark_api_blocks_getFees(char *ip, int port)
{
    printf("[%s][ARK API] Getting fees for an ArkPeer: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getfees", ip, port);

    ArkFee fee = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return fee;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return fee;

    json_object *feeJson = json_object_object_get(root, "fees");

    fee = ark_helpers_getArkFee_fromJSON(feeJson);

    free(feeJson);
    free(root);
    ars = NULL;

    return fee;
}

ArkBlock ark_api_blocks_get(char *ip, int port, char *id)
{
    printf("[%s][ARK API] Getting ArkBlock details: [IP = %s, Port = %d, ID = %s]\n", ark_helpers_getTimestamp(), ip, port, id);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/get?id=%s", ip, port, id);

    ArkBlock block = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return block;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return block;

    json_object *blockJson = json_object_object_get(root, "block");

    block = ark_helpers_getArkBlock_fromJSON(blockJson);

    free(blockJson);
    free(root);
    ars = NULL;

    return block;
}

ArkBlockArray ark_api_blocks(char* ip, int port)
{
    printf("[%s][ARK API] Getting ArkBlocks: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks", ip, port);

    ArkBlockArray aba = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return aba;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return aba;

    array_list *blocks = json_object_object_get(root, "blocks");
    int total = json_object_array_length(blocks);

    ArkBlock *data = malloc(total * sizeof(ArkBlock));
    if (!data)
        return aba;

    for (int i = 0; i < total; i++)
    {
        //data[i] = ark_helpers_getArkBlock_fromJSON(json_object_array_get_idx(blocks, i));
    }

    aba.length = total;
    aba.data = data;

    free(blocks);
    free(root);
    ars = NULL;

    return aba;
}

ArkBlockHeight ark_api_blocks_getHeight(char *ip, int port)
{
    printf("[%s][ARK API] Getting ArkPeers height: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getHeight", ip, port);

    ArkBlockHeight arkblockheight = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

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

char *ark_api_blocks_getEpoch(char *ip, int port)
{
    printf("[%s][ARK API] Getting ArkBlock Epoch: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getEpoch", ip, port);

    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return NULL;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return NULL;

    char *time = "";
    time = json_object_get_string(json_object_object_get(root, "epoch"));

    free(root);
    ars = NULL;

    return time;
}

int ark_api_blocks_getFee(char *ip, int port)
{
    printf("[%s][ARK API] Getting ArkFee from: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    int fee = -1;
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getFee", ip, port);

    ArkRestResponse *ars = ark_api_get(url, NULL);

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

char *ark_api_blocks_getNethash(char *ip, int port)
{
    printf("[%s][ARK API] Getting NetHash from: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    char *nethash = "";
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getNethash", ip, port);

    ArkRestResponse *ars = ark_api_get(url, NULL);

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
    printf("[%s][ARK API] Getting milestone from: [IP = %s, Port = %d]\n", ark_helpers_getTimestamp(), ip, port);

    int milestone = -1;
    char url[255];

    snprintf(url, sizeof url, "%s:%d/api/blocks/getMilestone", ip, port);

    ArkRestResponse *ars = ark_api_get(url, NULL);

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
