#include "pluginsHttp.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATABASE_H
#define DATABASE_H

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

void http_test_body_hander(ngx_http_request_t *r);

int post_test_handler(ngx_http_request_t *r);

int get_test_handler(ngx_http_request_t *r);

#endif // DATABASE_H

#ifdef __cplusplus
}
#endif
