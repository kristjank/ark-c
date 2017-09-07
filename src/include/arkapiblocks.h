#ifndef __arkapiblocks_h__
#define __arkapiblocks_h__

#include "arkapibase.h"

/// --------------------------------------------------
/// ARK API - BLOCK(S) FUNCTIONS
/// --------------------------------------------------

ArkFee ark_api_blocks_getFees(char *ip, int port);

ArkBlock ark_api_blocks_get(char *ip, int port, char *id);

ArkBlockArray ark_api_blocks(char* ip, int port);

ArkBlockHeight ark_api_blocks_getHeight(char *ip, int port);

char* ark_api_blocks_getEpoch(char* ip, int port);

int ark_api_blocks_getFee(char* ip, int port);

char *ark_api_blocks_getNethash(char *ip, int port);

int ark_blocks_getMilestone(char* ip, int port);

#endif /* __arkapiblocks_h__ */
