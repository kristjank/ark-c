#include "arkapifees.h"

/// --------------------------------------------------
/// ARK API - FEE(S) FUNCTIONS
/// --------------------------------------------------

ArkFee ark_api_fees_get(char* ip, int port)
{
    printf("[ARK API] Getting fees for an ArkPeer: [IP = %s, Port = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/blocks/getfees", ip, port);

    ArkFee fee = {0};
    ArkRestResponse *ars = ark_api_get(url);

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
