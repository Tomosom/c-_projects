#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

// �麯������
// ��̬���ࣺ���麯���ڱ���ʱ��ȷ�����˵�����һ��
// ��̬���ࣺ������ʱȷ��������һ��
//           ��������ָ�룬ָ���麯����
//           ͨ��ָ�룬�ҵ��������麯��


class Human {
private:
    int a;


public:
    virtual void eating(void){cout<<"using hand to eat" << endl;}

    ~Human() { cout<<"~Human()"<<endl; }


};

class Englishman : public Human{

public:
    void eating(void) { cout<<"using knife to eat" << endl; }

    ~Englishman(){ cout<<"~Englishman()"     ; }


};

class Chineseman : public Human{

public:
    void eating(void) { cout<<"using chopsticks to eat" << endl; }
    ~Chineseman(){ cout<<"~Chineseman()"     ; }

};

void test_eating(Human &h){

    h.eating();

}

int main(int argc, char **argv){
    Human *h = new Human;
    Englishman *e = new Englishman;
    Chineseman *c = new Chineseman;

    Human *p[3] = { h, e, c };
    int i;
    for(i = 0; i<3; i++){
        p[i]->eating();
        delete p[i];
    }

    return 0;
}

