#ifndef __arkhelpers_h__
#define __arkhelpers_h__

#include <json/json.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arkmodels.h"

/// --------------------------------------------------
/// ENUM CONVERTERS
/// --------------------------------------------------

ARKPEERSTATUS ark_helpers_getArkPeerStatus_fromString(const char* string);

ARKTRANSACTIONTYPE ark_helpers_getArkTransactionType_fromString(const char* string);

/// --------------------------------------------------
/// JSON TO STRUCTURE CONVERTERS
/// --------------------------------------------------

ArkAccount ark_helpers_getArkAccount_fromJSON(struct json_object * json);

ArkBlock ark_helpers_getArkBlock_fromJSON(struct json_object * json);

ArkDelegate ark_helpers_getArkDelegate_fromJSON(struct json_object * json);

ArkFee ark_helpers_getArkFee_fromJSON(struct json_object * json);

ArkForgedDetails ark_helpers_getArkForgedDetails_fromJSON(struct json_object * json);

ArkNetwork ark_helpers_getArkNetwork_fromJSON(struct json_object * json);

ArkPeer ark_helpers_getArkPeer_fromJSON(struct json_object * json);

ArkTransaction ark_helpers_getArkTransaction_fromJSON(struct json_object * json);

ArkVoter ark_helpers_getArkVoter_fromJSON(struct json_object * json);

/// --------------------------------------------------
/// NULL CHECKS
/// --------------------------------------------------

int ark_helpers_isFeeNull(ArkFee fee);

int ark_helpers_isNetworkNull(ArkNetwork network);

int ark_helpers_isPeerNull(ArkPeer peer);

int ark_helpers_isResponseSuccess(struct json_object * json);

#endif /* __arkhelpers_h__ */
