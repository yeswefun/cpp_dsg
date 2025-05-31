#include <iostream>

using namespace std;


class A {
public:
    A() {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }
};

class B : public A {
public:
    B() {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }
};

class C : public B {
public:
    C() {
        cout << "C()" << endl;
    }

    ~C() {
        cout << "~C()" << endl;
    }
};

/*
A()
B()
C()
~C()
~B()
~A()
*/
int main(int argc, char const *argv[]){
    C c;
    return 0;
}
