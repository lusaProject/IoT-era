#ifdef __cplusplus
extern "C" {
#endif

#include "nginx.h"
#include "pluginsHttp.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv)
{
    /*-----初始化句柄----*/
    init_handler();

    for (int i =0; i<argc; i++) {
        printf("%s\n", argv[i]);
    }

    int argcu = 5;
    char** argvu;

    char *a = "./nginx";
    char *b = "-p";
    char *c = "../esdata";
    char *d = "-c";
    char *e = "conf/nginx.conf";

    argvu[0] = a;
    argvu[1] = b;
    argvu[2] = c;
    argvu[3] = d;
    argvu[4] = e;

    for (int i =0; i<argcu; i++) {
        printf("%s\n", argvu[i]);
    }

    int ret = dream_main(argcu, argvu);

    /*---程序退出清理-----*/
     exit_plugins();

    return ret;
}

#ifdef __cplusplus
}
#endif
