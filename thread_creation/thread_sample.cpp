#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h> // header file added to use sleep function
#include <mutex>
#include <condition_variable>

using namespace std;

// Synchronization variables to ensure threads wait until priority is set
mutex sync_mutex;
condition_variable sync_cv;
bool ready = false;

void threadFunction1(int arg)
{
    cout <<"Thread1 started \n";
    // Wait until main thread signals that priorities are set
    unique_lock<mutex> lock(sync_mutex);
    sync_cv.wait(lock, [] { return ready; });
    
    int count = 10;
    cout <<"Thread1 invoked with arg = " << arg << endl;
    
    while(count > 0)
    {
        cout << "thread1 running count = " << count << endl;
        count--;
        //sleep(1);
    }
}

void threadFunction2(int arg)
{
    cout <<"Thread2 started \n";
    // Wait until main thread signals that priorities are set
    unique_lock<mutex> lock(sync_mutex);
    sync_cv.wait(lock, [] { return ready; });
    
    int count = 10;
    cout <<"Thread2 invoked with arg = " << arg << endl;
    
    while(count > 0)
    {
        cout << "thread2 running count = " << count << endl;
        count--;
        //sleep(1);
    }
}

int main()
{
    int arg = 1;

    std::cout<<"Sample program to control thread priority from C++ program \n";

    // create thresd using C++ class
    thread t1(threadFunction1, arg);
    thread t2(threadFunction2, arg);

    // Get native POSIX handle to change the thread attributes
    pthread_t thread_handle1 = t1.native_handle();
    pthread_t thread_handle2 = t2.native_handle();
    
    struct sched_param param_t1, param_t2;
    
    std::cout<<"Thread 2 priority is elevated to real-time and thread 1 priority is kept default (non-realtime) \n";
    
    // Set Thread 1 to SCHED_OTHER (normal)
    param_t1.sched_priority = 0;
    pthread_setschedparam(thread_handle2, SCHED_OTHER, &param_t2);
    
    // Set Thread 2 to SCHED_FIFO (real-time) with high priority
    param_t2.sched_priority = 50;
    int ret = pthread_setschedparam(thread_handle1, SCHED_FIFO, &param_t1);
    if (ret != 0) {
        std::cout << "Warning: Could not set SCHED_FIFO. Running with current scheduler.\n";
    }
    
    // Signal both threads to start now that priority is set
    {
        unique_lock<mutex> lock(sync_mutex);
        ready = true;
    }
    sync_cv.notify_all();
    
    t1.join();
    t2.join();

    return 0;
}

