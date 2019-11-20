#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class Singleton;


class Singleton {
private:
    static Singleton *gInstance;
    static pthread_mutex_t g_tMutex;    //����ߵ�static��Ա����Ҫ���������ʼ��

public:
    static Singleton *getInstance(){
        if(gInstance == NULL){
            pthread_mutex_lock(&g_tMutex);
            if(gInstance == NULL){  // �п��������̻߳����ͬʱִ����䣬��������ʵ��
                gInstance = new Singleton;
            }
            pthread_mutex_unlock(&g_tMutex);
        }
        return gInstance;
    }
    void printInfo(){
        cout<<"this is singleton"<<endl;
    }

private:
    Singleton(){
        cout<<"Singleton()"<<endl;
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

/* ����ģʽ���õ�ʱ������ */
Singleton *Singleton::gInstance;
pthread_mutex_t Singleton::g_tMutex = PTHREAD_MUTEX_INITIALIZER;  //error : Singleton::g_tMutex = PTHREAD_MUTEX_INITIALIZER;


int main(){

    Singleton *s = Singleton::getInstance();
    s->printInfo();
    Singleton *s1 = Singleton::getInstance();
    s1->printInfo();
    Singleton *s2 = Singleton::getInstance();
    s2->printInfo();

//    Singleton *s3 = new Singleton;
//    Singleton s4;

    /*�����߳�*/
    pthread_t thread1ID;
    pthread_t thread2ID;
    pthread_create(&thread1ID, NULL, start_routine_thread1, NULL);
    pthread_create(&thread2ID, NULL, start_routine_thread2, NULL);

    sleep(3);
    return 0;
}


