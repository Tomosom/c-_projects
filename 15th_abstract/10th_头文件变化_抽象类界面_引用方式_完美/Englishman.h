#ifndef __ENGLISHMAN_H__
#define __ENGLISHMAN_H__


#include <iostream>
#include <string.h>
#include <unistd.h>

#include "Human.h"  //��ʡ�ԣ�

using namespace std;

class Englishman:public Human{
private:
    char adress[1000000];
    int age;


public:


    void eating(void);
    void wearing(void);
    void driving(void);

    Englishman();
    Englishman(const char *name, int age, const char *address);


    virtual ~Englishman(){cout<<"~Englishman()"<<endl;}


};

#endif
