#include "arkapiaccounts.h"

/// --------------------------------------------------
/// ARK API - ACCOUNT(S) FUNCTIONS
/// --------------------------------------------------

//ArkAccount ark_api_accounts_getByAddress()

ArkAccountArray ark_api_accounts(char *ip, int port, char *address)
{
    printf("[%s][ARK API] Getting accounts: [IP = %s, Port = %d, Address = %s]\n", ark_helpers_getTimestamp(), ip, port, address);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/accounts?address=%s", ip, port, address);

    ArkAccountArray aaa = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return aaa;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return aaa;

    array_list *accounts = json_object_object_get(root, "accounts");
    int total = json_object_array_length(accounts);

    ArkAccount *data = malloc(total * sizeof(ArkAccount));
    if (!data)
        return aaa;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkAccount_fromJSON(json_object_array_get_idx(accounts, i));
    }

    aaa.length = total;
    aaa.data = data;

    free(accounts);
    free(root);
    ars = NULL;

    return aaa;
}

char *ark_api_accounts_getBalance(char *ip, int port, char *address)
{
    printf("[%s][ARK API] Getting account balance: [IP = %s, Port = %d, Address = %s]\n", ark_helpers_getTimestamp(), ip, port, address);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/accounts/getBalance?address=%s", ip, port, address);

    char *balance = "";
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return balance;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return balance;

    free(root);
    ars = NULL;

    return balance;
}

char *ark_api_accounts_getPublicKey(char *ip, int port, char *address)
{
    printf("[%s][ARK API] Getting account public key: [IP = %s, Port = %d, Address = %s]\n", ark_helpers_getTimestamp(), ip, port, address);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/accounts/getPublicKey?address=%s", ip, port, address);

    char *pKey = "";
    ArkRestResponse *ars = ark_api_get(url, NULL);

    if (ars->size == 0 || ars->data == NULL)
        return pKey;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return pKey;

    free(root);
    ars = NULL;

    return pKey;
}

ArkDelegateArray ark_api_accounts_getDelegates(char *ip, int port, char *address)
{
    printf("[%s][ARK API] Getting account delegates: [IP = %s, Port = %d, Address = %s]\n", ark_helpers_getTimestamp(), ip, port, address);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/accounts/delegates?address=%s", ip, port, address);

    ArkDelegateArray ada = {0};
    ArkRestResponse *ars = ark_api_get(url, NULL);

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
