#include <iostream>

using namespace std;

class QuackBehavior {
public:
    virtual void quack() = 0;
protected:
    QuackBehavior() {}
};

class FlyBehavior {
public:
    virtual void fly() = 0;
protected:
    FlyBehavior() {}
};

class FlyWithRocket : public FlyBehavior {
    void fly() {
        cout << "fly with rocket" << endl;
    }
};

class FlyWithWings : public FlyBehavior {
    void fly() {
        cout << "fly with wings" << endl;
    }
};

class FlyWithNoWay : public FlyBehavior {
    void fly() {
        cout << "fly with no way" << endl;
    }
};

class ZhiZhiQuack : public QuackBehavior {
public:
    void quack() {
        cout << "ZhiZhi" << endl;
    }
};

class WuWuQuack : public QuackBehavior {
public:
    void quack() {
        cout << "WuWu" << endl;
    }
};

class WigeonQuack : public QuackBehavior {
public:
    void quack() {
        cout << "Wigeon Quack" << endl;
    }
};


/*
将 quack 和 fly 抽象成为一个对象

Duck has a Quack
Duck has a Fly
*/
class Duck {
public:
    // virtual void quack() = 0;

    virtual void test() = 0;
    
    // virtual void fly() = 0;

    void setFlyBehavior(FlyBehavior *fb) {
        m_pFly = fb;
    }

    void setQuackBehavior(QuackBehavior *qb) {
        m_pQuack = qb;
    }

    virtual void performFly() {
        m_pFly->fly();
    }

    virtual void performQuack() {
        m_pQuack->quack();
    }

protected:
    QuackBehavior *m_pQuack;
    FlyBehavior *m_pFly;
};

// DonaladDuck is Duck
class DonaladDuck : public Duck {
public:
    DonaladDuck() {
        m_pFly = new FlyWithRocket;
        m_pQuack = new WuWuQuack;
    }
  
    void test() {
        performFly();
        performQuack();   
    }
};

class RuberDuck : public Duck {
public:
    RuberDuck() {
        m_pFly = new FlyWithNoWay;
        m_pQuack = new ZhiZhiQuack;
    }

    void test() {
        performFly();
        performQuack();
    }
};


class WigeonDuck : public Duck {
public:
    WigeonDuck() {
        m_pFly = new FlyWithWings;
        m_pQuack = new WigeonQuack;
        //if/else的代码坏味道
    }
    void test() {
        performFly();
        performQuack();
    }
};


/*
is-a
    Inheritance

has-a
    Composite

里氏代换原则(策略模式的本质)
    子类对象可以完全替换父类

组合大于继承
    将公共的方法抽象成单独的一个类

策略模式的工程应用
    if/else的代码坏味道

    支付方式
        微信支付
        支付宝支付
        银联支付
        现金支付
        ...
*/
int main() {

    DonaladDuck dd;
    RuberDuck rd;
    WigeonDuck wd;

    dd.test();
    rd.test();
    wd.test();

    return 0;
}
