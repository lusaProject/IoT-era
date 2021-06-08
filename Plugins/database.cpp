#include "database.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "cJSON.h"
#include "datapacket.h"
//#include <mysql/mysql.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <string.h>

//extern MYSQL *mysql;


#ifdef __cplusplus
extern "C" {
#endif

void http_test_body_hander(ngx_http_request_t *r)
{
    int status = NGX_HTTP_OK;
    ngx_int_t     rc;
    ngx_chain_t   out;

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

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "%s\n", "post_test_handler");
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "%s\n", data_buf);

    /*-------Parse json-------*/

    rapidjson::Document dom;

    if (!dom.Parse((char *)data_buf).HasParseError()) {
        if (dom.HasMember("id") && dom["id"].IsString()) {
            fprintf(stdout, "id: %s\n", dom["id"].GetString());
        }

        if (dom.HasMember("name") && dom["name"].IsString()) {
            fprintf(stdout, "name: %s\n", dom["name"].GetString());
        }

    }

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "post");
    cJSON_AddStringToObject(root, "name", "tp");
    char *json_data = cJSON_PrintUnformatted(root);

    int json_len = strlen(json_data) + 1;
    char send_buf[json_len];

    strcpy(send_buf, json_data);

    ngx_str_t response = ngx_string(send_buf);

    if (status != NGX_HTTP_OK) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Post failed.");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_str_t type = ngx_string("application/json;charset=GB2312");
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_type = type;
    r->headers_out.content_length_n = response.len;

    ngx_buf_t  *b = ngx_create_temp_buf(r->pool, response.len);
    if (b == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return;
    }

    ngx_memcpy(b->pos, response.data, response.len);
    b->last = b->pos + response.len;
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


int post_test_handler(ngx_http_request_t *r)
{
    /*--------------get body-------------*/
    ngx_int_t rc;
    rc = ngx_http_read_client_request_body(r, http_test_body_hander);
    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }
    return NGX_DONE;
}


int get_test_handler(ngx_http_request_t *r)
{
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "%s\n", "get_test_handler");

#if 0
    /* 插入数据 */
    char buf[] = "INSERT INTO `weixx`.`test` (`ID`, `name`, `age`) VALUES ('5', 'aaaaa', '213');";

    int t = mysql_real_query(mysql, buf, strlen(buf));
    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql));
    } else {
        printf("Insert sucessfully!\n");
    }

#endif


    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", "135246");
    cJSON_AddStringToObject(root, "name", "tp");
    char *json_data = cJSON_PrintUnformatted(root);

//    std::string dirRet =  getDirList("/home");
//    json_data = (char *)dirRet.c_str();

    int json_len = strlen(json_data) + 1;
    char send_buf[json_len];

    strcpy(send_buf, json_data);

    ngx_str_t response = ngx_string(send_buf);

    ngx_str_t type = ngx_string("application/json;charset=GB2312");

    r->headers_out.content_type = type;
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = response.len;

    ngx_buf_t *b = ngx_create_temp_buf(r->pool, response.len);
    if (b == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_memcpy(b->pos, response.data, response.len);
    b->last = b->pos + response.len;
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

#ifdef __cplusplus
}
#endif
