#include <iostream>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

using namespace std;
class Person{
private:
    static int cnt;
    char *name;
    int age;
    char *work;
public:
    Person(){
        name = NULL;
        work = NULL;
        cnt++;
    }
    Person(const char *name){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->work = NULL;
        cnt++;
    }

    Person(const char *name, int age, const char *work = "none"){
        cout<<"Person(char *, int), name = "<<name<<", age = "<<age<<", work = "<<work<<endl;
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->age = age;
        this->work = new char[strlen(work)+1];
        strcpy(this->work, work);
        cnt++;
    }

    Person(const Person &per){
        cout<<"Person(Person &)"<<endl;
        this->name = new char[strlen(per.name)+1];
        strcpy(this->name, per.name);
        this->age = per.age;
        this->work = new char[strlen(per.work)+1];
        strcpy(this->work, per.work);
        cnt++;
    }

    ~Person(){
        cout << "~Person()" << endl;
        if(this->name)
        {
            cout << "name = "<<name<<endl;
            delete this->name;
        }
        if(this->work)
        {
            cout << "work = "<<work<<endl;
            delete this->work;
        }

    }

    static int Getcnt();

	int SetName(char *name){
        this->name = name;
        return 0;
    }

 	int SetAge(int age){
        this->age = age;
        return 0;
    }

 	int SetWork(char *work){
        this->work = work;
        return 0;
    }

	void printf_info(void) const{ //const����ֻ�ܵ���const����
		printf("name : %s, age : %d, work : %s\n", name, age, work);
	}
#if 1
    Person& operator=(const Person &p){
        cout<<"operator=(const Person &p)"<<endl;

        if(this == &p)
            return *this;
        this->age = p.age;

        if(this->name)
            delete this->name;
        if(this->work)
            delete this->work;

        this->name = new char[strlen(p.name)+1];
        strcpy(this->name, p.name);
        this->work = new char[strlen(p.work)+1];
        strcpy(this->work, p.work);
        return *this;
    }
#endif
};

int Person::cnt = 0;
int Person::Getcnt(){
    return cnt;
}

int main(void){
	const Person p1("zhangsan", 10, "student");
	Person p2 = p1;   // �ȼ��� Person p2(p1),���ÿ������캯��
    Person p3;
    p3 = p1;

    p1.printf_info(); //const����ֻ�ܵ���const����
    p2.printf_info();
    p3.printf_info();

    cout << "person number = "<<Person::Getcnt()<<endl;

//    p1.printf_info();


    return 0;
}
