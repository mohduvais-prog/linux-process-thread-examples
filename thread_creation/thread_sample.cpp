#include <iostream>
#include <thread>

using namespace std;

void threadRoutine(int arg)
{
    cout <<"Thread running with arg = " << arg << endl;
}

int main()
{
    int arg = 4;
    cout<<"Sample program" << endl;
    
    thread t(threadRoutine, arg); // thread is a class offered in C++
    
    t.join(); // wait until thread is executed.

    return 0;
}
