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

class Guangximan : public Chineseman{
public:
    void eating(void) { cout<<"using chopsticks to eat, i come from Guangxi" << endl; }

};

void test_eating(Human &h){


    //ָ��ת�����ɹ�������NULL
    //����ת�����ɹ���������
    //���Զ�̬����ת���У�����ʹ��ָ�룬��ʹ������
#if 1
    Englishman &pe = dynamic_cast<Englishman &>(h);   //terminate called after throwing an instance of 'std::bad_cast'
    Chineseman &pc = dynamic_cast<Chineseman &>(h);
    Guangximan &pg = dynamic_cast<Guangximan &>(h);
#else
    Englishman &pe = reinterpret_cast<Englishman &>(h);
    Chineseman &pc = reinterpret_cast<Chineseman &>(h);
    Guangximan &pg = reinterpret_cast<Guangximan &>(h);


#endif
    h.eating();

}

int main(int argc, char **argv){
    Human h;
//    Englishman e;
//    Chineseman c;
    Guangximan g;

    // static_cast����ת��OK������ת������

    Englishman *pe1 = static_cast<Englishman *>(&h);

    //Englishman *pe2 = static_cast<Englishman *>(&g);  //error

    Chineseman *pc = static_cast<Chineseman *>(&g);


    return 0;
}

