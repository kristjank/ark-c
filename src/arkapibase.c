#include "arkapibase.h"

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
ArkRestResponse *ark_api_get(const char *url, struct curl_slist *headers)
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

    //struct curl_slist *headers = NULL;
    //if (headers == NULL)
    {
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charsets: utf-8");
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

    /* fetch the url */
    CURLcode rcode = curl_easy_perform(curl);

    /* return */
    return response;
}
