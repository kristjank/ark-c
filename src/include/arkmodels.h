#ifndef __arkmodels_h__
#define __arkmodels_h__

#include <stdio.h>

/// --------------------------------------------------
/// ENUMERATIONS
/// --------------------------------------------------

typedef enum { DEVELOPMENT, MAIN } ARKNETWORKTYPE;

typedef enum { OK, EUNAVAILABLE, ETIMEOUT } ARKPEERSTATUS;

typedef enum { SENDARK, SECONDSIGNATURE, CREATEDELEGATE, VOTE, MULTISIGNATURE } ARKTRANSACTIONTYPE;

/// --------------------------------------------------
/// STRUCTURES
/// --------------------------------------------------

typedef struct {
    char*   data;
    size_t  size;
} ArkRestResponse;

typedef struct {
    char*   address;
    char*   balance;
    char*   publicKey;
    char*   secondPublicKey;
    long    secondSignature;
    long    unconfirmedBalance;
    long    unconfirmedSignature;
    //OBJ   multisignatures
    //OBJ   uMultisignatures
} ArkAccount;

typedef struct {
    int             length;
    ArkAccount*     data;
} ArkAccountArray;

typedef struct {
    char*   balance;
    char*   unconfirmedBalance;
} ArkAccountBalance;

typedef struct {
    long        id;
    long        timestamp;
    char*       blockSignature;
    long        confirmations;
    char*       generatorId;
    char*       generatorPublicKey;
    int         height;
    long        numberOfTransactions;
    char*       payloadHash;
    long        payloadLength;
    int         previousBlock;
    double      reward;
    double      totalAmount;
    double      totalFee;
    char*       totalForged;
    int         version;
} ArkBlock;

typedef struct {
    int         length;
    ArkBlock*    data;
} ArkBlockArray;

typedef struct {
    char*   id;
    long    height;
} ArkBlockHeight;

typedef struct {
    char*   address;
    double  approval;
    long    missedBlocks;
    long    producedBlocks;
    double  productivity;
    char*   publicKey;
    int     rate;
    char*   username;
    char*   vote;
} ArkDelegate;

typedef struct {
    int             length;
    ArkDelegate*    data;
} ArkDelegateArray;

typedef struct {
    long delegate;
    long multiSignature;
    long secondSignature;
    long send;
    long vote;
} ArkFee;

typedef struct {
    long fees;
    long rewards;
    long forged;
} ArkForgedDetails;

typedef struct {
    long    blocksCount;
    long    now;
    int     loaded;
} ArkLoaderStatus;

typedef struct {
    long    blocks;
    long    height;
    char*   id;
    int     syncing;
} ArkLoaderSyncStatus;

typedef struct {
    char*   explorer;
    char*   netHash;
    char*   symbol;
    char*   token;
    int     version;
} ArkNetwork;

typedef struct {
    int             delay;
    int             height;
    char*           ip;
    char*           os;
    int             port;
    char*           version;
    ARKPEERSTATUS   status;
} ArkPeer;

typedef struct {
    int         length;
    ArkPeer*    data;
} ArkPeerArray;

typedef struct {
    char*   id;
    long    timestamp;
    char*   blockSignature;
    char*   generatorPublicKey;
    double  height;
    long    numberOfTransactions;
    char*   payloadHash;
    long    payloadLength;
    char*   previousBlock;
    long    reward;
    long    totalAmount;
    long    totalFee;
    int     version;
} ArkPeerStatusHeader;
    
typedef struct {
    long                    currentSlot;
    int                     forgingAllowed;
    double                  height;
    ArkPeerStatusHeader     header;
} ArkPeerStatus;

typedef struct {
    char*   username;
    char*   publicKey;
} ArkTransactionAssetDelegate;

typedef struct {
    double              amount;
    //                  ASSET
    ArkTransactionAssetDelegate     assetDelegate;
    char*               blockId;
    int                 confirmation;
    double              fee;
    int                 height;
    char*               id;
    char*               recipientId;
    char*               secondSenderPublicKey;
    char*               senderId;
    char*               senderPublicKey;
    char*               signature;
    char*               signSignature;
    time_t              timestamp;
    //ARKTRANSACTIONTYPE  type;
    int                 type;
    char*               vendorField;
} ArkTransaction;

typedef struct {
    int                 length;
    ArkTransaction*     data;
} ArkTransactionArray;

typedef struct {
    char*   id;
    char*   blockId;
    char*   senderId;
    char*   recipientId;
    int     limit;
    int     offset;
    char*   orderBy;
    char*   type;
} ArkTransactionsRequest;

typedef struct {
    char*   address;
    long    balance;
    char*   publicKey;
    char*   username;
} ArkVoter;

typedef struct {
    int         length;
    ArkVoter*   data;
} ArkVoterArray;

#endif /* __arkmodels_h__ */
