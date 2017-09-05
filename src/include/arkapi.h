#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "arkconstants.h"
#include "arkhelpers.h"

/// --------------------------------------------------
/// ARK API - BASE FUNCTIONS
/// --------------------------------------------------

/* callback for curl fetch */
size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp);

/* fetch and return url body via curl */
ArkRestResponse* ark_api_get(const char *url);

/// --------------------------------------------------
/// ARK API - ACCOUNT(S) FUNCTIONS
/// --------------------------------------------------

//ArkAccount ark_api_accounts_getByAddress()

/// --------------------------------------------------
/// ARK API - BLOCK(S) FUNCTIONS
/// --------------------------------------------------

//ArkBlockHeight ark_api_blocks_getLastBlockHeight()

ArkBlockHeight ark_api_blocks_getHeight(char *ip, int port);

char* ark_api_blocks_getEpoch(char* ip, int port);

int ark_api_blocks_getFee(char* ip, int port);

char *ark_api_blocks_getNethash(char *ip, int port);

int ark_blocks_getMilestone(char* ip, int port);

/// --------------------------------------------------
/// ARK API - DELEGATE(S) FUNCTIONS
/// --------------------------------------------------

ArkDelegateArray ark_api_delegates(char* ip, int port);

ArkDelegate ark_api_delegates_getByUsername(char* ip, int port, char* username);

// api/delegates/forging/getForgedByAccount

/// --------------------------------------------------
/// ARK API - FEE(S) FUNCTIONS
/// --------------------------------------------------

ArkFee ark_api_fees_get(char *ip, int port);

/// --------------------------------------------------
/// ARK API - NETWORK(S) FUNCTIONS
/// --------------------------------------------------

ArkNetwork ark_api_network_autoconfigure(char *ip, int port);

/// --------------------------------------------------
/// ARK API - PEER(S) FUNCTIONS
/// --------------------------------------------------

ArkPeerArray ark_api_peers(char* ip, int port);

ArkPeerArray ark_api_peers_getList(char* ip, int port);

ArkPeer ark_api_peers_get(ArkPeer peer, char *ip, int port);

// NOT WORKING YET
int ark_api_peers_getStatus(char* ip, int port);

/// --------------------------------------------------
/// ARK API - TRANSACTION(S) FUNCTIONS
/// --------------------------------------------------

ArkTransactionArray ark_api_transactions();

ArkTransactionArray ark_api_transactions_unconfirmed();

ArkTransaction ark_api_transactions_get(char* id);

ArkTransaction ark_api_transactions_getUnconfirmed(char* id);

/// --------------------------------------------------
/// ARK API - VOTER(S) FUNCTIONS
/// --------------------------------------------------

ArkVoterArray ark_api_voters_getByDelegate(char* ip, int port, char* publicKey);

/// --------------------------------------------------
/// ARK API - OTHER FUNCTIONS
/// --------------------------------------------------
