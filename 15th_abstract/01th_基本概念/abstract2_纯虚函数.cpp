#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

// �麯������
// ��̬���ࣺ���麯���ڱ���ʱ��ȷ�����˵�����һ��
// ��̬���ࣺ������ʱȷ��������һ��
//           ��������ָ�룬ָ���麯����
//           ͨ��ָ�룬�ҵ��������麯��


class Human {       //������
private:
    int a;


public:
    virtual void eating(void) = 0;
    virtual void wearing(void) = 0;
    virtual void driving(void) = 0;

    virtual ~Human() { cout<<"~Human()"<<endl; }
    virtual Human *test(void) {cout<<"Human's test"<<endl; return this;}

};

class Englishman : public Human{

public:
    void eating(void) { cout<<"using knife to eat" << endl; }
    void wearing(void){cout<<"wear english style"<<endl;}
    void driving(void){cout<<"drive english car"<<endl;}

    virtual ~Englishman(){ cout<<"~Englishman()"<<endl     ; }
    virtual Englishman *test(void) {cout<<"Englishman's test"<<endl; return this;}


};

class Chineseman : public Human{    //�����д��麯��δʵ�֣�������Ȼ��һ��������

public:
    void eating(void) { cout<<"using chopsticks to eat" << endl; }
    void wearing(void){cout<<"wear chinese style"<<endl;}
    //void driving(void){cout<<"drive chinese car"<<endl;}
    virtual ~Chineseman(){ cout<<"~Chineseman()"     <<endl; }
    virtual Chineseman *test(void) {cout<<"Chineseman's test"<<endl; return this;}

};

class Guangximan : public Chineseman{

public:
    void driving(void){cout<<"drive guangxi car"<<endl;}

};


void test_eating(Human &h){

    h.eating();

}

void test_return(Human &h){

    h.test();

}

int main(int argc, char **argv){
    //Human h;
    Englishman e;
    //Chineseman c;
    Guangximan g;

    //test_return(h);
    test_return(e);
    //test_return(c);
    test_eating(g);

    return 0;
}

