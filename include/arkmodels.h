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
    long delegate;
    long multiSignature;
    long secondSignature;
    long send;
    long vote;
} ArkFee;

typedef struct {
    char*   id;
    int     height;
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
    char*   address;
    long    balance;
    char*   publicKey;
    char*   username;
} ArkVoter;

typedef struct {
    int         length;
    ArkVoter*   data;
} ArkVoterArray;

typedef struct {
    char*   explorer;
    char*   netHash;
    char*   symbol;
    char*   token;
    int     version;
} ArkNetwork;

typedef struct {
    double              amount;
    //                  ASSET
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
    ARKTRANSACTIONTYPE  type;
    char*               vendorField;
} ArkTransaction;

typedef struct {
    int                 length;
    ArkTransaction*     data;
} ArkTransactionArray;

#endif /* __arkmodels_h__ */
