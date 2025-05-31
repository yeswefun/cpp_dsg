#include <iostream>

using namespace std;


class A {
public:
    A() {
        cout << "A()" << endl;
    }

    A(int id) : m_id(id) {
        cout << "A(id): " << id << endl;
    }

    //赋值运算符重载，=
    A& operator=(const A& o) {

        //no operator "==" matches these operands
        // if (this == o) {}

        cout << "assign" << endl;

        return *this;
    }

    ~A() {
        cout << "~A(), id: " << m_id << endl;
    }
private:
    int m_id;
};

/*
------------------------
A(id): 1
A(id): 2
------------------------
A(id): 26
assign
~A(), id: 26
~A(), id: 2
~A(), id: 1
*/
int main() {

    cout << "------------------------" << endl;
    A a1(1);
    A a2(2);

    cout << "------------------------" << endl;
    A az(26);
    az = az; // assign
    

    return 0;
}