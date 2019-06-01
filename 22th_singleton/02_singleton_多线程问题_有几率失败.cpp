#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class Singleton;

Singleton *gInstance;



class Singleton {
public:
    static Singleton *getInstance(){
        if(gInstance == NULL){  // �п��������̻߳����ͬʱִ����䣬��������ʵ��
            gInstance = new Singleton;
        }
        return gInstance;
    }

    Singleton(){
        cout<<"Singleton()"<<endl;
    }

    void printInfo(){
        cout<<"this is singleton"<<endl;
    }
};

void *start_routine_thread1(void *arg){
    cout<<"this is thread1 ..."<<endl;
    Singleton *s2 = Singleton::getInstance();
    s2->printInfo();
    return NULL;
}
void *start_routine_thread2(void *arg){
    cout<<"this is thread1 ..."<<endl;
    Singleton *s2 = Singleton::getInstance();
    s2->printInfo();
    return NULL;
}

int main(){

    Singleton *s = Singleton::getInstance();
    s->printInfo();
    Singleton *s1 = Singleton::getInstance();
    s1->printInfo();
    Singleton *s2 = Singleton::getInstance();
    s2->printInfo();

    /*�����߳�*/
    pthread_t thread1ID;
    pthread_t thread2ID;
    pthread_create(&thread1ID, NULL, start_routine_thread1, NULL);
    pthread_create(&thread2ID, NULL, start_routine_thread2, NULL);

    sleep(3);
    return 0;
}


