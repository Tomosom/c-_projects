#include <iostream>
#include <string.h>
#include <unistd.h>

#include "RefBase.h"

using namespace std;
using namespace android::RSC;

class Person : public LightRefBase<Person>{

private:
    sp<Person> father;
    sp<Person> son;

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

template<typename T>
void test_func(sp<T> &other){
    sp<T> s = other;
    cout<<"in call test_func: "<<s->getStrongCount()<<endl;
    s->printInfo();
}

int main(void){
	int i;

    /* �൱�ڣ�
    * 1.    Person *p = new Person();
    * 2.    SmartPoint tmp(p);                  => SmartPoint(Person *p)
    * 3.
    * 3.1   SmartPoint other(tmp);              => SmartPoint(SmartPoint &sp)
    * 3.2   SmartPoint other( (Person *)tmp )   => SmartPoint(Person *p)
    */

    /* ����"  Person *"; ��"SmartPoint<Person>"������"  Person *"
    * Person *per;
    * �����ֲ���:              per->XXX, (*per).XXX
    * SmartPoint sp;
    * ҲӦ���У����ֲ���: sp->XXX, (*sp).XXX
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
