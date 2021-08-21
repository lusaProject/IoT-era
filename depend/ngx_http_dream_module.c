#include "pluginsHttp.h"
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <stdio.h>
 
#define PB_SIZE (1024 * 2)
#define CONTENT_TYPE "application/json;charset=GB2312"
 
static char* ngx_http_dream(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
 
static ngx_int_t ngx_http_dream_handler(ngx_http_request_t *r);
  
static ngx_command_t  ngx_http_dream_commands[] =
{
 
    {
        ngx_string("api"),
        NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LMT_CONF | NGX_CONF_NOARGS,
        ngx_http_dream,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },
 
    ngx_null_command
};
 
static ngx_http_module_t  ngx_http_dream_module_ctx =
{
    NULL,                              /* preconfiguration */
    NULL,                              /* postconfiguration */
 
    NULL,                              /* create main configuration */
    NULL,                              /* init main configuration */
 
    NULL,                              /* create server configuration */
    NULL,                              /* merge server configuration */
 
    NULL,                              /* create location configuration */
    NULL                               /* merge location configuration */
};
 
ngx_module_t  ngx_http_dream_module =
{
    NGX_MODULE_V1,
    &ngx_http_dream_module_ctx,           /* module context */
    ngx_http_dream_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};
 
static char *ngx_http_dream(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf;
 
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
 
    clcf->handler = ngx_http_dream_handler;
 
    return NGX_CONF_OK;
}

static ngx_int_t ngx_http_dream_handler(ngx_http_request_t *r)
{

#if 0
    if (!(r->method & (NGX_HTTP_POST|NGX_HTTP_GET|NGX_HTTP_PUT|NGX_HTTP_DELETE)))
    {
        return NGX_HTTP_NOT_ALLOWED;
    }

    if (strstr((char *)r->uri.data, "get_test_tp") && (r->method & NGX_HTTP_GET))
    {
        ngx_int_t rc = get_test_handler(r);
        return rc;
    }

    if (strstr((char *)r->uri.data, "post_test_tp") && (r->method & NGX_HTTP_POST))
    {
        ngx_int_t rc = post_test_handler(r);
        return rc;
    }
    else
    {
        return NGX_HTTP_NOT_ALLOWED;
    }   
#endif

    ngx_int_t rc = serviceHttp_handler(r);
    return rc;

}
