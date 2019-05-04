#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

class Point {

private:
    int x;
    int y;

public:
    Point() {
        cout<<"Point()"<<endl;
    }
    Point(int x, int y) : x(x), y(y) {
        cout<<"Point(int x, int y)"<<endl;
    }

    Point(const Point &p) {
        cout<<"Point(const Point &p)"<<endl;
        x = p.x;
        y = p.y;
    }

    ~Point(){
        cout<<"~Point()"<<endl;
    }

    int getx(){ return x;   }
    int gety(){ return y;   }
    void setx(int x){ this->x = x; }
    void sety(int y){ this->y = y; }

    void print_info(){
        cout << "x = "<<x<<", y = "<<y<<"\n";
    }

    friend Point add(Point &p1, Point &p2);
    friend Point operator+(Point &p1, Point &p2);
    friend Point operator++(Point &p, int a);
    friend Point& operator++(Point &p);
    friend ostream& operator<<(ostream &o, const Point &n);

};


Point add(Point &p1, Point &p2){
    Point n;
    n.x = p1.x+p2.x;
    n.y = p1.y+p2.y;
    return n;
}

Point operator+(Point &p1, Point &p2){
    cout << "operator+"<<endl;
    Point n;
    n.x = p1.x+p2.x;
    n.y = p1.y+p2.y;
    return n;
}


/* Point p1(1, 2); p++ ;*/
Point operator++(Point &p, int a){  //��������β�û�����ã�
    cout<<"p++"<<endl;
    Point n;
    n = p;
    p.x++;
    p.y++;
    return n;
}


/* Point p1(1, 2); ++p ;*/
Point& operator++(Point &p){
    cout<<"++p"<<endl;
    p.x++;
    p.y++;
    return p;
}

//���һ�������������ã��̳���δ�ᵽ
ostream& operator<<(ostream &o, const Point &n){
    //cout<<"<<"<<endl;
    cout << "x = "<<n.x<<", y = "<<n.y;
    return o;
}

int main(int argc, char **argv){

    Point p1(1, 2);
    Point p2(2, 3);

    cout<<p1<<" "<<p2<<endl;

    //�����������������ʹ��
    operator+(p1, p2);
    operator++(p1);
    //�ں�++�����غ�����ߣ����һ���ββ�δʹ�ã�ֻ��Ϊ�˷ֱ���ǰ++���Ǻ�++
    //��˺��һ��ʵ�������һ������ֵ
    operator++(p1, 0);
    operator<<(cout, p1);

    return 0;
}


