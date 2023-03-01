#include<bits/stdc++.h>
using namespace std;

mutex m;
condition_variable cv;

long long balance=0;

void addMoney(int money){
    lock_guard<mutex> lg(m);
    balance+=money;
    cout<<"Amount added, current balance:"<<balance<<'\n';
    cv.notify_one();
}

void withdrawMoney(int money){
    unique_lock<mutex> ul(m);
    cv.wait(ul,[]()->bool{return (balance!=0)?true:false;});
    if(balance>=money){
        balance-=money;
        cout<<"Amount deducted "<<money<<'\n';
    }else{
        cout<<"Amount cant be deducted, current balance is less than "<<money<<'\n';
    }
    cout<<"Current balance is "<<balance<<'\n';
}

int main(){
    thread t1(withdrawMoney,600);
    thread t2(addMoney,500);
    t1.join();
    t2.join();
    return 0;
}