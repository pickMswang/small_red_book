#ifndef _PTHREAD_POOL_
#define _PTHREAD_POOL_
 
#include "locker.h"
#include "head.h"
#include "TCPNet.h"
#include "TCPKernel.h"

class TCPNet;
class TCPKernel;
class Task;
class BaseTask;

template<class T>
class threadpool
{
private:
    int thread_number;  //线程池的线程数
    //int max_task_number;  //任务队列中的最大任务数
    pthread_t *all_threads;   //线程数组
    std::queue<T *> task_queue; //任务队列
    mutex_locker queue_mutex_locker;  //互斥锁
    //sem_locker queue_sem_locker;   //信号量
    cond_locker queue_cond_locker; //cond
    bool is_stop; //是否结束线程
public:
    TCPKernel* m_pTCPKernel;
    threadpool(int thread_num=20);
    ~threadpool();
    bool append_task(T *task);  //添加任务
    void start();              //线程池开启
    void stop();               //线程池关闭
private:
    //线程运行的函数。执行run()函数
    static void *worker(void *arg);
    void run();
    T *getTask();   //获取任务
};
 
template <class T>
threadpool<T>::threadpool(int thread_num):
	thread_number(thread_num),is_stop(false), all_threads(NULL)
{       //构造函数
   // printf("threadpool init\n");
   /* if(thread_num <= 0)
	printf("threadpool can't init because thread_number = 0");
 */
    all_threads = new pthread_t[thread_number];
    if(all_threads == NULL)
    	printf("can't init threadpool because thread array can't new");
}
 
template <class T>
threadpool<T>::~threadpool()
{
    delete []all_threads;
    stop();
}
 
template <class T>
void threadpool<T>::stop() //线程池停止
{
        is_stop = true;
        //queue_sem_locker.add();
        queue_cond_locker.broadcast();
}
 
template <class T>
void threadpool<T>::start()  //线程池启动
{

    for(int i = 0; i < thread_number; ++i)
    {
	//printf("create the %dth pthread\n", i);
	if(pthread_create(all_threads + i, NULL, worker, this) != 0)
	{//创建线程失败，清除成功申请的资源并抛出异常
	    delete []all_threads;
	    throw std::exception();
	}
	if(pthread_detach(all_threads[i]))
	{//将线程设置为脱离线程，失败则清除成功申请的资源并抛出异常
	    delete []all_threads;
	    throw std::exception();
	}
    }
}
//添加任务进入任务队列
template <class T>
bool threadpool<T>::append_task(T *task)   //添加任务
{   
//	printf("add success\n");
	//获取互斥锁
    queue_mutex_locker.mutex_lock();
    
    bool is_signal = task_queue.empty();
    //添加进入队列
    task_queue.push(task);
//	printf("push task\n");
    queue_mutex_locker.mutex_unlock();
    //唤醒等待任务的线程
    if(is_signal)
    {
//		printf("signal\n");
            queue_cond_locker.signal();
    }
    return true;
}
 
template <class T>
void *threadpool<T>::worker(void *arg)  //线程工作函数
{
//	printf("run\n");
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}
 
template <class T>
T* threadpool<T>::getTask()   //从任务队列中获取任务
{
//	printf("getTask success\n");
    T *task = NULL;
    queue_mutex_locker.mutex_lock();
    if(!task_queue.empty())
    {
        task = task_queue.front();
        task_queue.pop();
    }
    queue_mutex_locker.mutex_unlock();
    return task;
}
 
template <class T>
void threadpool<T>::run()
{
//		printf("getTask\n");
    while(!is_stop){
        T *task = getTask();
        if(task == NULL)  //队列为空，等待
                queue_cond_locker.wait();
        else              //执行任务
                task->doit();
    }
    //for test
    //printf("exit%d\n", (unsigned long)pthread_self());
}
 
#endif
 
 
