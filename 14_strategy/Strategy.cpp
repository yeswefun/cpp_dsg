#include <iostream>

using namespace std;

class Duck {
public:
    virtual void quack() = 0;
};

class DonaladDuck : public Duck {
public:
    void quack() {
        cout << "donaladDuck" << endl;
    }
};

class RuberDuck : public Duck {
public:
    void quack() {
        cout << "ruberDuck" << endl;
    }
}


/*
is-a
    Inheritance
has-a
    Composite

里氏代换原则
    子类对象可以完全替换父类

组合大于继承
    将公共的方法抽象成单独的一个类
*/
int main() {

    return 0;
}
