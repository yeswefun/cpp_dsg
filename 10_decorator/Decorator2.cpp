#include <iostream>

using namespace std;

class Beverage {
public:
    virtual string getDesc() = 0;
    virtual double cost() = 0;
protected:
    string m_desc;
};

/*
Condiment
    调味品; 调味料; 作料; 调味汁(或酱等); 酱料;
*/
class CondimentDecorate : public Beverage {
public:
    virtual string getDesc() = 0;
protected:
    CondimentDecorate() {}
};

//装饰类
class Soy : public CondimentDecorate {
public:
    Soy(Beverage *target) : m_target(target) {}
    string getDesc() {
        return m_target->getDesc() + " + 酱油";
    }
    double cost() {
        return m_target->cost() + 1;
    }
private:
    //持有被装饰的对象
    Beverage *m_target;
};

//装饰类
class Sugar : public CondimentDecorate {
public:
    Sugar(Beverage *target) : m_target(target) {}
    string getDesc() {
        return m_target->getDesc() + " + 糖";
    }
    double cost() {
        return m_target->cost() + 10;
    }
private:
    //持有被装饰的对象
    Beverage *m_target;
};


//装饰类
class Milk : public CondimentDecorate {
public:
    Milk(Beverage *target) : m_target(target) {}
    string getDesc() {
        return m_target->getDesc() + " + 牛奶";
    }
    double cost() {
        return m_target->cost() + 100;
    }
private:
    //持有被装饰的对象
    Beverage *m_target;
};


// 基本产品类 -> 被装饰类
class Lattee : public CondimentDecorate {
public:
    Lattee() {
        m_desc = "拿铁";
    }
    string getDesc() {
        return m_desc;
    }
    double cost() {
        return 1000;
    }
};

class Expresso : public CondimentDecorate {
public:
    Expresso() {
        m_desc = "浓咖啡";
    }
    string getDesc() {
        return m_desc;
    }
    double cost() {
        return 10000;
    }
};

class Mocha : public CondimentDecorate {
public:
    Mocha() {
        m_desc = "摩卡";
    }
    string getDesc() {
        return m_desc;
    }
    double cost() {
        return 100000;
    }
};


/*
组合 大于 继承

Java IO，Stream
*/
int main() {

    Beverage *p = new Expresso;
    cout << p->getDesc() << " : " << p->cost() << endl;

    Beverage *p2 = new Mocha;
    p2 = new Milk(p2);
    p2 = new Sugar(p2);
    p2 = new Soy(p2);
    p2 = new Soy(p2);
    cout << p2->getDesc() << " : " << p2->cost() << endl;

    return 0;
}
