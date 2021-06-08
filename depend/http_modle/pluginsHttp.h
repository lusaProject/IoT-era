#ifndef PLUGINSHTTP_H
#define PLUGINSHTTP_H

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

ngx_int_t serviceHttp_handler(ngx_http_request_t *r);

#endif
