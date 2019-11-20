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

};

class Englishman : public Human{

public:
    void eating(void) { cout<<"using knife to eat" << endl; }

};

class Chineseman : public Human{

public:
    void eating(void) { cout<<"using chopsticks to eat" << endl; }

};

void test_eating(Human h){

    h.eating();

}

int main(int argc, char **argv){
    Human h;
    Englishman e;
    Chineseman c;

    test_eating(h);
    test_eating(e);
    test_eating(c);

    cout<<"sizeof(Human) = "<<sizeof(h)<<endl;
    cout<<"sizeof(Englishman) = "<<sizeof(e)<<endl;
    cout<<"sizeof(Chineseman) = "<<sizeof(c)<<endl;

    return 0;
}

