#include<bits/stdc++.h>
using namespace std;

// deadlock arrised because there were 2 threads t1 and t2 at time=0;
// they aquired lock on mutex 1 and mutex 2 respectively;
// now they want lock on mutex 2 and mutex 1 respectively at time=1;
// but they cannot get locks because both locks are held by opposite threads respectively

mutex m1,m2;

void thread1(){
    m1.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m2.lock();
    cout<<"Critical section of thread 1"<<'\n';
    m1.unlock();
    m2.unlock();   
}

void thread2(){
    m2.lock();
    this_thread::sleep_for(chrono::seconds(1));
    m1.lock();
    cout<<"Critical section of thread 2"<<'\n';
    m2.unlock();
    m1.unlock();   
}

int main(){
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();
    return 0;
}