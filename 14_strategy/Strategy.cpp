#include <iostream>

using namespace std;

/*
将 quack 和 fly 抽象成为一个对象
*/
class Duck {
public:
    virtual void quack() = 0;

    virtual void test() = 0;
    
    virtual void fly() = 0;
};

class DonaladDuck : public Duck {
public:
    void quack() {
        cout << "donaladDuck" << endl;
    }
   
    void test() {
        quack();
    }

    // 自身不会飞，可以借助工具飞
    void fly(/*int*/) {}
};

class RuberDuck : public Duck {
public:
    void quack() {
        cout << "ruberDuck" << endl;
    }

    void test() {
        cout << "test" << endl;
    }

    // 子类不像父类
    void fly() {} // can not fly
};


class WigeonDuck : public Duck {
public:
    void quack() {
        cout << "ruberDuck" << endl;
    }
    void test() {
        quack();
    }
    void fly() {
        cout << "fly" << endl;
    }
};

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
