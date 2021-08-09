#include <cstring>
#include <iostream>
using namespace std;

struct A {
    int age;
    char name[10240];
};

void test_0() {
    A* p = new A;
    p->age = 10;
    //char t[100] = "hello";
    //strcpy(p->name, t);

    delete p;

    cout << "test_0" << endl;

}

void test_1() {
    A a = {};

    cout << "test_1" << endl;
}


int main() {
    test_0();
    test_0();
    test_0();
    test_0();
    test_0();


    return 0;
}