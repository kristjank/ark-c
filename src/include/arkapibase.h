#ifndef __arkapibase_h__
#define __arkapibase_h__

#include <curl/curl.h>

#include "arkconstants.h"
#include "arkhelpers.h"

/// --------------------------------------------------
/// ARK API - BASE FUNCTIONS
/// --------------------------------------------------

/* callback for curl fetch */
size_t curl_callback (void *contents, size_t size, size_t nmemb, void *userp);

/* fetch and return url body via curl */
ArkRestResponse* ark_api_get(const char *url);

#endif /* __arkapibase_h__ */
