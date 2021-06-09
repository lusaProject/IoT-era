#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

template  <typename Resource>
class CustomThreadPool
{

public:
    //!资源类型
    typedef shared_ptr<Resource> ResourcePtr;

    //!资源处理函数 ResourcePtr 为要处理的资源对象, void * 为用户参数
    typedef void (*thread_func)(ResourcePtr, void *);

    //!消费者线程池
    CustomThreadPool()
    {

    }

    //!资源队列大小
    size_t resourceSize() const
    {
        return  _res.size();
    }

    //!线程是否工作
    bool isWorking() const
    {
        return _bRun;
    }

    //!获取线程执行函数指针
    thread_func funcation() const
    {
        return  _thFunc;
    }

    //!获取线程执行的参数
    void *funcationArg() const
    {
        return  _thArg;
    }

    //！添加待处理资源
    void append(ResourcePtr r)
    {
        unique_lock<mutex> lk(_mutex);
        _res.push(r);
        lk.unlock();
        _rwCV.notify_all();
    }

    //启动线程池
    //return 0:成功; 1:线程池已启动; -1:回调函数为NULL
    int startWork(thread_func func, void *arg, int thread_num = 2)
    {
        if (!_thds.empty())
            return 1;
        if (func == NULL)
            return -1;

        //回调
        _bRun = true;
        _thFunc = func;
        _thArg = arg;

        //初始化资源队列
        _res = queue<ResourcePtr>();

        //创建线程
        for (int i = 0; i < max(thread_num, 1); ++i) {
            thread *th = new thread (run, this);
            _thds.push_back(th);
        }
        return 0;
    }

    void stopWork()
    {
        //停止
        _bRun = false;

        //通知所有线程
        _rwCV.notify_all();
        if (! _thds.empty()) {
            //释放线程
            for (thread *th : _thds) {
                th->join();
                delete th;
            }

            _thds.clear();
        }

    }

protected:

    //!线程执行函数
    static int run(void *arg)
    {
        CustomThreadPool<Resource> *ptr = (CustomThreadPool<Resource> *) arg;

        while (ptr->_bRun) {
            unique_lock<mutex> lk(ptr->_mutex);

            //等待资源
            if (ptr->_res.empty())
                ptr->_rwCV.wait(lk, [ = ]() {
                return !(ptr->_res.empty()) || !ptr->_bRun;
            });

            //线程退出
            if (!ptr->_bRun) {
                lk.unlock();
                return  0;
            }

            //获取一个资源
            ResourcePtr r = ptr->_res.front();
            ptr->_res.pop();
            lk.unlock();
            assert(ptr->_thFunc != NULL);

            //调用用户的回调函数处理
            ptr->_thFunc(r, ptr->_thArg);

        }

        return  0;
    }

protected:
    //资源队列
    queue<ResourcePtr> _res;

    //读写锁
    mutex _mutex;

    //并发控制
    condition_variable _rwCV;

    //线程对象
    vector<thread *> _thds;

    //用户线程处理函数的传参
    void *_thArg = NULL;

    //用户线程处理函数地址
    thread_func _thFunc = NULL;

    //线程池是否运行
    volatile bool _bRun = false;
};

struct SqlData {
    string sql;
    string handl;
};


#endif // THREADPOOL_H
