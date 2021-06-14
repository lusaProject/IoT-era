#include "businessRequest.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "cJSON.h"
#include "datapacket.h"
#include <mysql/mysql.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

extern MYSQL *mysql;


#ifdef __cplusplus
extern "C" {
#endif

void http_test_body_hander(ngx_http_request_t *r)
{
    string body_buf;
    get_body_hander(r, body_buf);

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "%s\n", "post_test_handler");
    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "%s\n", body_buf.c_str());

    /*-------Parse json-------*/

    rapidjson::Document dom;

    cout << body_buf << endl;

    if (!dom.Parse((char *)body_buf.c_str()).HasParseError()) {
        if (dom.HasMember("id") && dom["id"].IsString()) {
            //fprintf(stdout, "id: %s\n", dom["id"].GetString());
        }

        if (dom.HasMember("name") && dom["name"].IsString()) {
            //fprintf(stdout, "name: %s\n", dom["name"].GetString());
        }

    }

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "post");
    cJSON_AddStringToObject(root, "name", "tp");
    char *json_data = cJSON_PrintUnformatted(root);

    string send_buf = json_data;
    ngx_http_post_send(r, send_buf);
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

#if 1
    /* 插入数据 */
    char buf[] = "INSERT INTO `weixx`.`test` (`ID`, `name`, `age`) VALUES (14, 'aaaaa', '213');";

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

    string send_buf = json_data;

    ngx_http_get_send(r, send_buf);
}

#ifdef __cplusplus
}
#endif
