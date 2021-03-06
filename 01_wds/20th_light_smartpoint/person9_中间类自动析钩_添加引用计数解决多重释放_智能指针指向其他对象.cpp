#include <iostream>
#include <string.h>
#include <unistd.h>

#include "RefBase.h"

using namespace std;
using namespace android::RSC;

//class RefBase{
//private:
//    int count;  //引用计数
//public:
//    RefBase() : count(0){ cout<<"RefBase()"<<endl; }
//    void incStrong(){count++;}
//    void decStrong(){count--;}
//    int getStrongCount(){
//        return count;
//    }
//
//};



class Person : public LightRefBase<Person>{


public:
    Person(){
        cout << "Person()" << endl;
    }

    ~Person(){
        cout << "~Person()" << endl;
    }

	void printInfo(void){
		cout<<"just a simple test"<<endl;
	}
};


//template<typename T>
//class SmartPoint {
//private:
//    T *p;
//
//public:
//
////    int getStrongCount(){
////            return p->getStrongCount();
////    }
//
//
//    SmartPoint():p(0) {
//        cout<<"SmartPoint()"<<endl;
//    }
//
//    SmartPoint(T *p){
//        cout<<"SmartPoint(Person *p)"<<endl;
//        this->p = p;
//        this->p->incStrong();   //引用计数加一
//    }
//
//    SmartPoint(const SmartPoint &sp){ //拷贝构造函数
//        cout<<"SmartPoint(SmartPoint &sp)"<<endl;
//        this->p = sp.p;
//        this->p->incStrong();   //引用计数加一
//    }
//
//    ~SmartPoint(){
//        cout<<"~SmartPoint()"<<endl;
//
//        if(p){
//            p->decStrong();
//            if(p->getStrongCount() == 0){
//                delete p;
//                p = NULL;
//            }
//
//        }
//    }
//
//    T *operator->(){
//        return p;
//    }
//
//    T& operator*(){
//        return *p;
//    }
//
//
//};


template<typename T>
void test_func(sp<T> &other){
//void test_func(void){

//    SmartPoint sp = new Person();
//    SmartPoint sp(new Person());

    sp<T> s = other;

    cout<<"in call test_func: "<<s->getStrongCount()<<endl;


    s->printInfo();
}

int main(void){
	int i;

    /* 相当于：
    * 1.    Person *p = new Person();
    * 2.    SmartPoint tmp(p);                  => SmartPoint(Person *p)
    * 3.
    * 3.1   SmartPoint other(tmp);              => SmartPoint(SmartPoint &sp)
    * 3.2   SmartPoint other( (Person *)tmp )   => SmartPoint(Person *p)
    */

    /* 少用"  Person *"; 用"SmartPoint<Person>"来代替"  Person *"
    * Person *per;
    * 有两种操作:              per->XXX, (*per).XXX
    * SmartPoint sp;
    * 也应该有；两种操作: sp->XXX, (*sp).XXX
    *
    */

    sp<Person> other = new Person();
    //SmartPoint other(new Person());


    (*other).printInfo();

    cout<<"before call test_func: "<<other->getStrongCount()<<endl;

    for(i = 0; i < 2; i++){
        test_func(other);
        cout<<"after call test_func: "<<other->getStrongCount()<<endl;
    }



    return 0;
}
