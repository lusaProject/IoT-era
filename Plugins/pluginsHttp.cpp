#include "database.h"
#include "pluginsHttp.h"

//#include <mysql/mysql.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

//MYSQL *mysql;

#ifdef __cplusplus
extern "C" {
#endif

void init_handler()
{
//    // 初始化mysql
//    mysql = mysql_init(NULL);

//    if (!mysql) {
//        printf("Mysql init failed.\n");
//    }

//    if (!mysql_real_connect(mysql, "localhost", "wxx", "654321", "weixx", 0, NULL, 0)) {
//        printf("Failed to connect:%s\n", mysql_error(mysql));
//    } else {
//        printf("Connect sucessfully!\n");
//    }
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
