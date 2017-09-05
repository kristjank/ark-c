#include "arkapivoters.h"

/// --------------------------------------------------
/// ARK API - VOTER(S) FUNCTIONS
/// --------------------------------------------------

ArkVoterArray ark_api_voters_getByDelegate(char* ip, int port, char* publicKey)
{
    printf("[ARK API] Getting ArkDelegate voters: [IP = %s, Port: = %d, PublicKey = %s]\n", ip, port, publicKey);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/delegates/voters?publicKey=%s", ip, port, publicKey);

    ArkVoterArray ava = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return ava;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return ava;

    array_list *voters = json_object_object_get(root, "accounts");
    int total = json_object_array_length(voters);

    ArkVoter *data = malloc(total * sizeof(ArkVoter));
    if (!data)
        return ava;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkVoter_fromJSON(json_object_array_get_idx(voters, i));
    }

    ava.length = total;
    ava.data = data;

    free(voters);
    free(root);
    ars = NULL;

    return ava;
}
