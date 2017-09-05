#include "arkapi.h"

/// --------------------------------------------------
/// ARK API - BASE FUNCTIONS
/// --------------------------------------------------

/* callback for curl fetch */
size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;                             /* calculate buffer size */
    ArkRestResponse *p = (ArkRestResponse *) userp;   /* cast pointer to fetch struct */

    /* expand buffer */
    p->data = (char *) realloc(p->data, p->size + realsize + 1);

    /* check buffer */
    if (p->data == NULL) {
        /* this isn't good */
        fprintf(stderr, "ERROR: Failed to expand buffer in curl_callback");
        /* free buffer */
        free(p->data);
        /* return */
        return -1;
    }

    /* copy contents to buffer */
    memcpy(&(p->data[p->size]), contents, realsize);

    /* set new buffer size */
    p->size += realsize;

    /* ensure null termination */
    p->data[p->size] = 0;

    /* return size */
    return realsize;
}

/* fetch and return url body via curl */
ArkRestResponse *ark_api_get(const char *url)
{
    ArkRestResponse restResponse;                    /* curl fetch struct */
    ArkRestResponse *response = &restResponse;       /* pointer to fetch struct */

    /* init payload */
    response->data = (char *) calloc(1, sizeof(response->data));

    /* check payload */
    if (response->data == NULL)
    {
        /* log error */
        fprintf(stderr, "ERROR: Failed to allocate payload in curl_fetch_url");
        /* return error */
        return response;
    }

    CURL *curl;

    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "ERROR: Failed to initialize curl");
        return response;
    }

    /* init size */
    response->size = 0;

    /* set url to fetch */
    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* set calback function */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);

    /* pass fetch struct pointer */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) response);

    /* set default user agent */
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* set timeout */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);

    /* enable location redirects */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    /* set maximum allowed redirects */
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 1);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    /* fetch the url */
    CURLcode rcode = curl_easy_perform(curl);

    /* return */
    return response;
}

/// --------------------------------------------------
/// ARK API - ACCOUNT(S) FUNCTIONS
/// --------------------------------------------------

//ArkAccount ark_api_accounts_getByAddress()

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

/// --------------------------------------------------
/// ARK API - DELEGATE(S) FUNCTIONS
/// --------------------------------------------------

ArkDelegateArray ark_api_delegates(char* ip, int port)
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

ArkDelegate ark_api_delegates_getByUsername(char* ip, int port, char* username)
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

// api/delegates/forging/getForgedByAccount

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

/// --------------------------------------------------
/// ARK API - NETWORK(S) FUNCTIONS
/// --------------------------------------------------

ArkNetwork ark_api_network_autoconfigure(char *ip, int port)
{
    printf("[ARK API] Getting network configuration for an ArkPeer: [IP = %s, Port = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/loader/autoconfigure", ip, port);

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

/// --------------------------------------------------
/// ARK API - PEER(S) FUNCTIONS
/// --------------------------------------------------

ArkPeerArray ark_api_peers(char* ip, int port)
{
    printf("[ARK API] Getting peers: [IP = %s, Port: = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peers", ip, port);

    ArkPeerArray apa = {0};
    ArkRestResponse *ars = ark_api_get(url);

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
    printf("[ARK API] Getting peer list: [IP = %s, Port: = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peer/list", ip, port);

    ArkPeerArray apa = {0};
    ArkRestResponse *ars = ark_api_get(url);

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
    printf("[ARK API] Getting ArkPeer details: [IP = %s, Port = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peers/get?port=%d&ip=%s", peer.ip, peer.port, port, ip);

    ArkPeer arkpeer = {0};
    ArkRestResponse *ars = ark_api_get(url);

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

int ark_api_peers_getStatus(char* ip, int port)
{
    printf("[ARK API] Getting ArkPeer status: [IP = %s, Port: = %d]\n", ip, port);

    char url[255];
    snprintf(url, sizeof url, "%s:%d/api/peer/status?port=%d&ip=%s", ip, port, port, ip);

    ArkPeerArray apa = {0};
    ArkRestResponse *ars = ark_api_get(url);

    if (ars->size == 0 || ars->data == NULL)
        return 0;

    json_object *root = json_tokener_parse(ars->data);

    if (ark_helpers_isResponseSuccess(root) == 0)
        return 0;

    array_list *peers = json_object_object_get(root, "peers");
    int total = json_object_array_length(peers);

    ArkPeer *data = malloc(total * sizeof(ArkPeer));
    if (!data)
        return 0;

    for (int i = 0; i < total; i++)
    {
        data[i] = ark_helpers_getArkPeer_fromJSON(json_object_array_get_idx(peers, i));
    }

    apa.length = total;
    apa.data = data;

    free(peers);
    free(root);
    ars = NULL;

    return 1;
}

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

/// --------------------------------------------------
/// ARK API - OTHER FUNCTIONS
/// --------------------------------------------------
