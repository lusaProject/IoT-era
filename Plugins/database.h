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

void get_body_hander(ngx_http_request_t *r,  std::string &bodyData);

int ngx_http_get_send(ngx_http_request_t *r,  std::string &sendData);

void ngx_http_post_send(ngx_http_request_t *r, std::string &sendData);


#endif // DATABASE_H

#ifdef __cplusplus
}
#endif
