#include <string>

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

void get_body_hander(ngx_http_request_t *r,  std::string &bodyData);

int ngx_http_get_send(ngx_http_request_t *r,  std::string &sendData);

void ngx_http_post_send(ngx_http_request_t *r, std::string &sendData);

void exit_plugins();

#endif


#ifdef __cplusplus
}
#endif
