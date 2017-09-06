#include "arkapidelegates.h"

/// --------------------------------------------------
/// ARK API - DELEGATE(S) FUNCTIONS
/// --------------------------------------------------

ArkDelegateArray ark_api_delegates(char *ip, int port)
{
    printf("[ARK API] Getting delegates: [IP = %s, Port: = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/delegates", ip, port);

    ArkDelegateArray ada = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return ada;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return ada;

    array_list *delegates = json_object_object_get(root, "delegates");
    int total = json_object_array_length(delegates);

    ArkDelegate *data = malloc(total * sizeof(ArkDelegate));
    if (!data)
        return ada;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkDelegate_fromJSON(json_object_array_get_idx(delegates, i));
    }

    ada.length = total;
    ada.data = data;

    free(delegates);
    free(root);
    ars = NULL;

    return ada;
}

ArkDelegate ark_api_delegates_get(char *ip, int port, char *username)
{
    printf("Getting delegate by username: [IP = %s, Port: = %d, Username = %s]\n", ip, port, username);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/delegates/get?username=%s", ip, port, username);

    ArkDelegate delegate = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->data == NULL)
        return delegate;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return delegate;

    json_object *delegateJson = json_object_object_get(root, "delegate");

    delegate = ark_helpers_getArkDelegate_fromJSON(delegateJson);

    free(delegateJson);
    free(root);
    ars = NULL;

    return delegate;
}

ArkVoterArray ark_api_delegates_voters(char *ip, int port, char *publicKey)
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

ArkForgedDetails ark_api_delegates_getForgedData(char *ip, int port, char *publicKey)
{
    printf("[ARK API] Getting forged details by account: [IP = %s, Port: = %d, PublicKey = %s]\n", ip, port, publicKey);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/delegates/forging/getForgedByAccount?username=%s", ip, port, publicKey);

    ArkForgedDetails fDetails = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->data == NULL)
        return fDetails;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return fDetails;

    json_object *forgedDetailsJson = json_object_object_get(root, "forgedDetails");

    fDetails = ark_helpers_getArkForgedDetails_fromJSON(forgedDetailsJson);

    free(forgedDetailsJson);
    free(root);
    ars = NULL;

    return fDetails;
}
