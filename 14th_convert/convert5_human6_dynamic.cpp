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

    virtual ~Human() { cout<<"~Human()"<<endl; }


};

class Englishman : public Human{

public:
    void eating(void) { cout<<"using knife to eat" << endl; }

    virtual ~Englishman(){ cout<<"~Englishman()"<<endl     ; }


};

class Chineseman : public Human{

public:
    void eating(void) { cout<<"using chopsticks to eat" << endl; }
    virtual ~Chineseman(){ cout<<"~Chineseman()"     <<endl; }

};

void test_eating(Human &h){

    Englishman *pe;
    Chineseman *pc;

    h.eating();

    // ��ֱ������ʱӢ���˻����й���
    // �ֱ���������
    if(pe = dynamic_cast<Englishman *>(&h)){        //��̬����װ����ֻ�����ں����麯��������
        cout<<"this human is Englishman"<<endl;
    }
    if(pc = dynamic_cast<Chineseman *>(&h)){
        cout<<"this human is Chineseman"<<endl;
    }

}

int main(int argc, char **argv){
    Human h;
    Englishman e;
    Chineseman c;

    test_eating(h);
    test_eating(e);
    test_eating(c);

    return 0;
}

