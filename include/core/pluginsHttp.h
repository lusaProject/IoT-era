#ifdef __cplusplus
extern "C" {
#endif


#ifndef PLUGINSHTTP_H
#define PLUGINSHTTP_H

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

void init_handler();

ngx_int_t serviceHttp_handler(ngx_http_request_t *r);

void exit_plugins();

#endif


#ifdef __cplusplus
}
#endif
