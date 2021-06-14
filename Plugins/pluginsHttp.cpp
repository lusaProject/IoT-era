#include "businessRequest.h"
#include "pluginsHttp.h"

#include <mysql/mysql.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <string>

MYSQL *mysql;

#ifdef __cplusplus
extern "C" {
#endif

void init_handler()
{
    // 初始化mysql
    mysql = mysql_init(NULL);

    if (!mysql) {
        printf("Mysql init failed.\n");
    }

    if (!mysql_real_connect(mysql, "localhost", "root", "123456", "weixx", 0, NULL, 0)) {
        printf("Failed to connect:%s\n", mysql_error(mysql));
    } else {
        printf("Connect sucessfully!\n");
    }
}

void get_body_hander(ngx_http_request_t *r, std::string &bodyData)
{
    ngx_chain_t *bufs = r->request_body->bufs;
    ngx_buf_t *buf = NULL;
    uint8_t *data_buf = NULL;
    size_t content_length = 0;
    size_t body_length = 0;

    //get body
    if (r->request_body == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "reqeust_body:null");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }
    if (r->headers_in.content_length == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "r->headers_in.content_length == NULL");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    content_length = atoi((char *)(r->headers_in.content_length->value.data));
    data_buf = (uint8_t *)ngx_palloc(r->pool, content_length + 1);
    size_t buf_length = 0;
    while (bufs) {
        buf = bufs->buf;
        bufs = bufs->next;
        buf_length = buf->last - buf->pos ;
        if (body_length + buf_length > content_length) {
            memcpy(data_buf + body_length, buf->pos, content_length - body_length);
            body_length = content_length ;
            break;
        }
        memcpy(data_buf + body_length, buf->pos, buf->last - buf->pos);
        body_length += buf->last - buf->pos;
    }
    if (body_length) {
        data_buf[body_length] = 0;
    }

    bodyData = (char *)data_buf;
}


void ngx_http_post_send(ngx_http_request_t *r, std::string &sendData)
{

    int status = NGX_HTTP_OK;
    ngx_int_t     rc;
    ngx_chain_t   out;

    // ngx_str_t response = ngx_string(sendData.c_str());

    if (status != NGX_HTTP_OK) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Post failed.");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_str_t type = ngx_string("application/json;charset=GB2312");
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_type = type;
    r->headers_out.content_length_n = sendData.length();

    ngx_buf_t  *b = ngx_create_temp_buf(r->pool, sendData.length());
    if (b == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_memcpy(b->pos, sendData.c_str(), sendData.length());
    b->last = b->pos + sendData.length();
    b->last_buf = 1;

    out.buf = b;
    out.next = NULL;

    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to do ngx_http_send_header.");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return ;
    }

    ngx_http_finalize_request(r, ngx_http_output_filter(r, &out));
    return;
}


int ngx_http_get_send(ngx_http_request_t *r, std::string &sendData)
{
    //  ngx_str_t response = ngx_string(sendData.c_str());

    ngx_str_t type = ngx_string("application/json;charset=GB2312");

    r->headers_out.content_type = type;
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sendData.length();

    ngx_buf_t *b = ngx_create_temp_buf(r->pool, sendData.length());
    if (b == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_memcpy(b->pos, sendData.c_str(), sendData.length());
    b->last = b->pos + sendData.length();
    b->last_buf = 1;

    ngx_chain_t out;
    out.buf = b;
    out.next = NULL;

    ngx_int_t rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    return ngx_http_output_filter(r, &out);
}


ngx_int_t serviceHttp_handler(ngx_http_request_t *r)
{
    if (!(r->method & (NGX_HTTP_POST | NGX_HTTP_GET | NGX_HTTP_PUT | NGX_HTTP_DELETE))) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    if (strstr((char *)r->uri.data, "get_test_tp") && (r->method & NGX_HTTP_GET)) {
        ngx_int_t rc = get_test_handler(r);
        return rc;
    }

    if (strstr((char *)r->uri.data, "post_test_tp") && (r->method & NGX_HTTP_POST)) {
        ngx_int_t rc = post_test_handler(r);
        return rc;
    } else {
        return NGX_HTTP_NOT_ALLOWED;
    }

}

void exit_plugins()
{
    printf("====> exit_handler\n");
}

#ifdef __cplusplus
}
#endif
