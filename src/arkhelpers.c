#include "arkhelpers.h"

/// --------------------------------------------------
/// ENUM CONVERTERS
/// --------------------------------------------------

ARKPEERSTATUS ark_helpers_getArkPeerStatus_fromString(const char *string)
{
    static struct
    {
        const char *s;
        ARKPEERSTATUS e;
    } map[] = {
        {"OK", OK},
        {"EUNAVAILABLE", EUNAVAILABLE},
        {"ETIMEOUT", ETIMEOUT}};

    ARKPEERSTATUS result = OK;

    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
    {
        if (strcmp(string, map[i].s) == 0)
        {
            result = map[i].e;
            break;
        }
    }

    return result;
}

ARKTRANSACTIONTYPE ark_helpers_getArkTransactionType_fromString(const char *string)
{
    static struct
    {
        const char *s;
        ARKTRANSACTIONTYPE e;
    } map[] = {
        {"SENDARK", SENDARK},
        {"SECONDSIGNATURE", SECONDSIGNATURE},
        {"CREATEDELEGATE", CREATEDELEGATE},
        {"VOTE", VOTE},
        {"MULTISIGNATURE", MULTISIGNATURE}};

    ARKTRANSACTIONTYPE result = OK;

    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
    {
        if (strcmp(string, map[i].s) == 0)
        {
            result = map[i].e;
            break;
        }
    }

    return result;
}

/// --------------------------------------------------
/// JSON TO STRUCTURE CONVERTERS
/// --------------------------------------------------

ArkAccount ark_helpers_getArkAccount_fromJSON(struct json_object *json)
{
    ArkAccount account = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "address");
    if (obj != NULL)
        account.address = json_object_get_string(obj);

    obj = json_object_object_get(json, "balance");
    if (obj != NULL)
        account.balance = json_object_get_string(obj);

    obj = json_object_object_get(json, "publicKey");
    if (obj != NULL)
        account.publicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "unconfirmedSignature");
    if (obj != NULL)
        account.unconfirmedBalance = json_object_get_int64(obj);

    obj = json_object_object_get(json, "secondSignature");
    if (obj != NULL)
        account.secondSignature = json_object_get_int64(obj);

    obj = json_object_object_get(json, "secondPublicKey");
    if (obj != NULL)
        account.secondPublicKey = json_object_get_string(obj);

    free(obj);

    return account;
}


ArkAccountBalance ark_helpers_getArkAccountBalance_fromJSON(struct json_object * json)
{
    ArkAccountBalance aab = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "balance");
    if (obj != NULL)
        aab.balance = json_object_get_string(obj);

    obj = json_object_object_get(json, "unconfirmedBalance");
    if (obj != NULL)
        aab.unconfirmedBalance = json_object_get_string(obj);

    free(obj);

    return aab;   
}

ArkBlock ark_helpers_getArkBlock_fromJSON(struct json_object *json)
{
    ArkBlock block = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "id");
    if (obj != NULL)
        block.id = json_object_get_int64(obj);

    obj = json_object_object_get(json, "timestamp");
    //if (obj != NULL)
    //    account.balance = json_object_get_string(obj);

    obj = json_object_object_get(json, "blockSignature");
    if (obj != NULL)
        block.blockSignature = json_object_get_string(obj);

    obj = json_object_object_get(json, "confirmations");
    if (obj != NULL)
        block.confirmations = json_object_get_int64(obj);

    obj = json_object_object_get(json, "generatorId");
    if (obj != NULL)
        block.generatorId = json_object_get_string(obj);

    obj = json_object_object_get(json, "generatorPublicKey");
    if (obj != NULL)
        block.generatorPublicKey = json_object_get_string(obj);

    free(obj);

    return block;
}

ArkBlockHeight ark_helpers_getArkBlockHeight_fromJSON(struct json_object *json)
{
    ArkBlockHeight bHeight = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "id");
    if (obj != NULL)
        bHeight.id = json_object_get_string(obj);

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        bHeight.height = json_object_get_int64(obj);

    free(obj);

    return bHeight;
}

ArkDelegate ark_helpers_getArkDelegate_fromJSON(struct json_object *json)
{
    ArkDelegate delegate = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "username");
    if (obj != NULL)
        delegate.username = json_object_get_string(obj);

    obj = json_object_object_get(json, "address");
    if (obj != NULL)
        delegate.address = json_object_get_string(obj);

    obj = json_object_object_get(json, "publicKey");
    if (obj != NULL)
        delegate.publicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "vote");
    if (obj != NULL)
        delegate.vote = json_object_get_string(obj);

    obj = json_object_object_get(json, "producedblocks");
    if (obj != NULL)
        delegate.producedBlocks = json_object_get_int64(obj);

    obj = json_object_object_get(json, "missedblocks");
    if (obj != NULL)
        delegate.missedBlocks = json_object_get_int64(obj);

    obj = json_object_object_get(json, "rate");
    if (obj != NULL)
        delegate.rate = json_object_get_int(obj);

    obj = json_object_object_get(json, "approval");
    if (obj != NULL)
        delegate.approval = json_object_get_double(obj);

    obj = json_object_object_get(json, "productivity");
    if (obj != NULL)
        delegate.productivity = json_object_get_double(obj);

    free(obj);

    return delegate;
}

ArkFee ark_helpers_getArkFee_fromJSON(struct json_object *json)
{
    ArkFee fee = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "send");
    if (obj != NULL)
        fee.send = json_object_get_int64(obj);

    obj = json_object_object_get(json, "vote");
    if (obj != NULL)
        fee.vote = json_object_get_int64(obj);

    obj = json_object_object_get(json, "secondsignature");
    if (obj != NULL)
        fee.secondSignature = json_object_get_int64(obj);

    obj = json_object_object_get(json, "delegate");
    if (obj != NULL)
        fee.delegate = json_object_get_int64(obj);

    obj = json_object_object_get(json, "multisignature");
    if (obj != NULL)
        fee.multiSignature = json_object_get_int64(obj);

    free(obj);

    return fee;
}

ArkForgedDetails ark_helpers_getArkForgedDetails_fromJSON(struct json_object *json)
{
    ArkForgedDetails fDetails = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "fees");
    if (obj != NULL)
        fDetails.fees = json_object_get_int64(obj);

    obj = json_object_object_get(json, "rewards");
    if (obj != NULL)
        fDetails.rewards = json_object_get_int64(obj);

    obj = json_object_object_get(json, "forged");
    if (obj != NULL)
        fDetails.forged = json_object_get_int64(obj);

    free(obj);

    return fDetails;
}

ArkLoaderStatus ark_helpers_getArkLoaderStatus_fromJSON(struct json_object *json)
{
    ArkLoaderStatus status = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "blocksCount");
    if (obj != NULL)
        status.blocksCount = json_object_get_int64(obj);

    obj = json_object_object_get(json, "now");
    if (obj != NULL)
        status.now = json_object_get_int64(obj);

    obj = json_object_object_get(json, "loaded");
    if (obj != NULL)
        status.loaded = json_object_get_int(obj);

    free(obj);

    return status;
}

ArkLoaderSyncStatus ark_helpers_getArkLoaderSyncStatus_fromJSON(struct json_object *json)
{
    ArkLoaderSyncStatus syncStatus = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "blocks");
    if (obj != NULL)
        syncStatus.blocks = json_object_get_int64(obj);

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        syncStatus.height = json_object_get_int64(obj);

    obj = json_object_object_get(json, "id");
    if (obj != NULL)
        syncStatus.id = json_object_get_string(obj);

    obj = json_object_object_get(json, "syncing");
    if (obj != NULL)
        syncStatus.syncing = json_object_get_int(obj);

    free(obj);

    return syncStatus;
}

ArkNetwork ark_helpers_getArkNetwork_fromJSON(struct json_object *json)
{
    ArkNetwork network = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "nethash");
    if (obj != NULL)
        network.netHash = json_object_get_string(obj);

    obj = json_object_object_get(json, "token");
    if (obj != NULL)
        network.token = json_object_get_string(obj);

    obj = json_object_object_get(json, "symbol");
    if (obj != NULL)
        network.symbol = json_object_get_string(obj);

    obj = json_object_object_get(json, "explorer");
    if (obj != NULL)
        network.explorer = json_object_get_string(obj);

    obj = json_object_object_get(json, "version");
    if (obj != NULL)
        network.version = json_object_get_int(obj);

    free(obj);

    return network;
}

ArkPeer ark_helpers_getArkPeer_fromJSON(struct json_object *json)
{
    ArkPeer peer = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "ip");
    if (obj != NULL)
        peer.ip = json_object_get_string(obj);

    obj = json_object_object_get(json, "port");
    if (obj != NULL)
        peer.port = json_object_get_int(obj);

    obj = json_object_object_get(json, "version");
    if (obj != NULL)
        peer.version = json_object_get_string(obj);

    obj = json_object_object_get(json, "os");
    if (obj != NULL)
        peer.os = json_object_get_string(obj);

    obj = json_object_object_get(json, "status");
    if (obj != NULL)
        peer.status = ark_helpers_getArkPeerStatus_fromString(json_object_get_string(obj));

    obj = json_object_object_get(json, "delay");
    if (obj != NULL)
        peer.delay = json_object_get_int(obj);

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        peer.height = json_object_get_int(obj);

    free(obj);

    return peer;
}

ArkPeerStatusHeader ark_helpers_getArkPeerStatusHeader_fromJSON(struct json_object *json)
{
    ArkPeerStatusHeader pHeader = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "id");
    if (obj != NULL)
        pHeader.id = json_object_get_string(obj);

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        pHeader.height = json_object_get_int64(obj);

    obj = json_object_object_get(json, "version");
    if (obj != NULL)
        pHeader.version = json_object_get_int(obj);

    obj = json_object_object_get(json, "totalAmount");
    if (obj != NULL)
        pHeader.totalAmount = json_object_get_int64(obj);

    obj = json_object_object_get(json, "totalFee");
    if (obj != NULL)
        pHeader.totalFee = json_object_get_int64(obj);

    obj = json_object_object_get(json, "reward");
    if (obj != NULL)
        pHeader.reward = json_object_get_int64(obj);

    obj = json_object_object_get(json, "payloadHash");
    if (obj != NULL)
        pHeader.payloadHash = json_object_get_string(obj);

    obj = json_object_object_get(json, "payloadHash");
    if (obj != NULL)
        pHeader.payloadHash = json_object_get_string(obj);

    obj = json_object_object_get(json, "payloadLength");
    if (obj != NULL)
        pHeader.payloadLength = json_object_get_int64(obj);

    obj = json_object_object_get(json, "timestamp");
    if (obj != NULL)
        pHeader.timestamp = json_object_get_int64(obj);

    obj = json_object_object_get(json, "numberOfTransactions");
    if (obj != NULL)
        pHeader.numberOfTransactions = json_object_get_int64(obj);

    obj = json_object_object_get(json, "previousBlock");
    if (obj != NULL)
        pHeader.previousBlock = json_object_get_string(obj);

    obj = json_object_object_get(json, "generatorPublicKey");
    if (obj != NULL)
        pHeader.generatorPublicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "blockSignature");
    if (obj != NULL)
        pHeader.blockSignature = json_object_get_string(obj);
    
    free(obj);

    return pHeader;
}

ArkPeerStatus ark_helpers_getArkPeerStatus_fromJSON(struct json_object *json)
{
    ArkPeerStatus pStatus = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        pStatus.height = json_object_get_int64(obj);

    obj = json_object_object_get(json, "forgingAllowed");
    if (obj != NULL)
        pStatus.forgingAllowed = json_object_get_int(obj);

    obj = json_object_object_get(json, "currentSlot");
    if (obj != NULL)
        pStatus.currentSlot = json_object_get_int64(obj);

    obj = json_object_object_get(json, "header");
    if (obj != NULL)
        pStatus.header = ark_helpers_getArkPeerStatusHeader_fromJSON(obj);

    free(obj);
    return pStatus;
}

ArkTransaction ark_helpers_getArkTransaction_fromJSON(struct json_object *json)
{
    ArkTransaction transaction = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "amount");
    if (obj != NULL)
        transaction.amount = json_object_get_double(obj);

    obj = json_object_object_get(json, "blockid");
    if (obj != NULL)
        transaction.blockId = json_object_get_string(obj);

    obj = json_object_object_get(json, "confirmation");
    if (obj != NULL)
        transaction.confirmation = json_object_get_string(obj);

    obj = json_object_object_get(json, "fee");
    if (obj != NULL)
        transaction.fee = json_object_get_double(obj);

    obj = json_object_object_get(json, "height");
    if (obj != NULL)
        transaction.height = json_object_get_int(obj);

    obj = json_object_object_get(json, "id");
    if (obj != NULL)
        transaction.id = json_object_get_string(obj);

    obj = json_object_object_get(json, "recipientid");
    if (obj != NULL)
        transaction.recipientId = json_object_get_string(obj);

    obj = json_object_object_get(json, "secondsenderpublickey");
    if (obj != NULL)
        transaction.secondSenderPublicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "senderid");
    if (obj != NULL)
        transaction.senderId = json_object_get_string(obj);

    obj = json_object_object_get(json, "senderpublickey");
    if (obj != NULL)
        transaction.senderPublicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "signature");
    if (obj != NULL)
        transaction.signature = json_object_get_string(obj);

    obj = json_object_object_get(json, "signsignature");
    if (obj != NULL)
        transaction.signSignature = json_object_get_string(obj);

    obj = json_object_object_get(json, "type");
    if (obj != NULL)
        transaction.type = ark_helpers_getArkTransactionType_fromString(json_object_get_string(obj));

    /// TIMESTAMP

    obj = json_object_object_get(json, "vendorfield");
    if (obj != NULL)
        transaction.vendorField = json_object_get_string(obj);

    free(obj);

    return transaction;
}

ArkVoter ark_helpers_getArkVoter_fromJSON(struct json_object *json)
{
    ArkVoter voter = {0};
    json_object *obj = NULL;

    obj = json_object_object_get(json, "username");
    if (obj != NULL)
        voter.username = json_object_get_string(obj);

    obj = json_object_object_get(json, "address");
    if (obj != NULL)
        voter.address = json_object_get_string(obj);

    obj = json_object_object_get(json, "publicKey");
    if (obj != NULL)
        voter.publicKey = json_object_get_string(obj);

    obj = json_object_object_get(json, "balance");
    if (obj != NULL)
        voter.balance = json_object_get_int64(obj);

    free(obj);

    return voter;
}

/// --------------------------------------------------
/// NULL CHECKS
/// --------------------------------------------------

int ark_helpers_isNetworkNull(ArkNetwork network)
{
    return (network.explorer == NULL &&
            network.netHash == NULL &&
            network.symbol == NULL &&
            network.token == NULL &&
            network.version == 0)
               ? 1
               : 0;
}

int ark_helpers_isPeerNull(ArkPeer peer)
{
    return (peer.delay == 0 &&
            peer.height == 0 &&
            peer.ip == NULL &&
            peer.os == NULL &&
            peer.port == 0 &&
            peer.version == NULL)
               ? 1
               : 0;
}

int ark_helpers_isFeeNull(ArkFee fee)
{
    return (fee.delegate == 0 &&
            fee.multiSignature == 0 &&
            fee.secondSignature == 0 &&
            fee.send == 0 &&
            fee.vote == 0)
               ? 1
               : 0;
}

int ark_helpers_isResponseSuccess(struct json_object *json)
{
    json_object *obj = json_object_object_get(json, "success");
    if (obj == NULL)
        return 0;

    int i = json_object_get_int(obj);
    free(obj);

    return (i == 1) ? 1 : 0;
}

/// --------------------------------------------------
/// OTHER
/// --------------------------------------------------

char* ark_helpers_getTimestamp()
{
    time_t t;
    struct tm *ltm;
    char buf[20];
    char *str = malloc(20);

    t = time(NULL);
    ltm = localtime(&t);

    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);

    for (int i = 0; i < sizeof(buf); i++)
        str[i] = buf[i];

    return str;
}
