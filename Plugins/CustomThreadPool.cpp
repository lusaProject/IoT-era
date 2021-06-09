#include "CustomThreadPool.h"

#include <iostream>
#include <unistd.h>

using namespace std;


void requestfunc(CustomThreadPool<SqlData>::ResourcePtr r, void *arg)
{
    cout << r->sql << endl;
    cout << r->handl << endl;
}

int threadPool()
{
    CustomThreadPool<SqlData> pool;

    const int thread_num = 100;

    int star = pool.startWork(requestfunc, NULL, thread_num);

    if (star == 0) {
        cout << "startWork" << endl;
    }

    SqlData *sd = new SqlData;
    sd->sql = "sql111111";
    sd->handl = "handl222222";

    CustomThreadPool<SqlData>::ResourcePtr resPtr(sd);
    pool.append(resPtr);

    while (1) {
        sleep(1);

    }

    return 0;
}
