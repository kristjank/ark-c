#include "arkapitransactions.h"

/// --------------------------------------------------
/// ARK API - TRANSACTION(S) FUNCTIONS
/// --------------------------------------------------

ArkTransactionArray ark_api_transactions()
{
    printf("[ARK API] Getting transactions\n");

    char url[255];
    snprintf(url, sizeof url, "%s:%d/transactions", "TBD", 0);

    ArkTransactionArray ata = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return ata;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return ata;

    array_list *transactions = json_object_object_get(root, "transactions");
    int total = json_object_array_length(transactions);

    ArkTransaction *data = malloc(total * sizeof(ArkTransaction));
    if (!data)
        return ata;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkTransaction_fromJSON(json_object_array_get_idx(transactions, i));
    }

    ata.length = total;
    ata.data = data;

    free(transactions);
    free(root);
    ars = NULL;

    return ata;
}

ArkTransactionArray ark_api_transactions_unconfirmed()
{
    printf("[ARK API] Getting unconfirmed transactions\n");

    char url[255];
    snprintf(url, sizeof url, "%s:%d/transactions/unconfirmed", "TBD", 0);

    ArkTransactionArray ata = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return ata;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return ata;

    array_list *transactions = json_object_object_get(root, "transactions");
    int total = json_object_array_length(transactions);

    ArkTransaction *data = malloc(total * sizeof(ArkTransaction));
    if (!data)
        return ata;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkTransaction_fromJSON(json_object_array_get_idx(transactions, i));
    }

    ata.length = total;
    ata.data = data;

    free(transactions);
    free(root);
    ars = NULL;

    return ata;
}

ArkTransaction ark_api_transactions_get(char* id)
{
    printf("[ARK API] Getting ArkTransaction details: [ID = %s]\n", id);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/transactions/get?id=%s", "TBD", 0, id);

    ArkTransaction arkTransaction = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return arkTransaction;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return arkTransaction;

    json_object *transactionJson = json_object_object_get(root, "transaction");

    arkTransaction = ark_helpers_getArkTransaction_fromJSON(transactionJson);

    free(transactionJson);
    free(root);
    ars = NULL;

    return arkTransaction;
}

ArkTransaction ark_api_transactions_getUnconfirmed(char* id)
{
    printf("[ARK API] Getting ArkTransaction details: [ID = %s]\n", id);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/transactions/unconfirmed/get?id=%s", "TBD", 0, id);

    ArkTransaction arkTransaction = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return arkTransaction;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return arkTransaction;

    json_object *transactionJson = json_object_object_get(root, "transaction");

    arkTransaction = ark_helpers_getArkTransaction_fromJSON(transactionJson);

    free(transactionJson);
    free(root);
    ars = NULL;

    return arkTransaction;
}
