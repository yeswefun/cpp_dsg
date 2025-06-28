#include <iostream>

using namespace std;


//PC, Mobile, Pad
class MakeOrder {
public:
    virtual void startOrder() = 0;
    virtual void replyStart() = 0;
    //...
    virtual void finishOrder() = 0;
    virtual void replyFinish() = 0;

    //模板方法，固定流程
    void make() {
        startOrder();
        replyStart();
        finishOrder();
        replyFinish();
    }
protected:
    MakeOrder() {}
};

class Foxcom : public MakeOrder {
public:
    void startOrder() {
        cout << "Foxcom order start" << endl;
    }
    void replyStart() {
        cout << "Foxcom reply start" << endl;
    }
    void finishOrder() {
        cout << "Foxcom order finish" << endl;
    }
    void replyFinish() {
        cout << "Foxcom reply finish" << endl;
    }
};

class Samsung : public MakeOrder {
public:
    void startOrder() {
        cout << "Samsung order start" << endl;
    }
    void replyStart() {
        cout << "Samsung reply start" << endl;
    }
    void finishOrder() {
        cout << "Samsung order finish" << endl;
    }
    void replyFinish() {
        cout << "Samsung reply finish" << endl;
    }
};


/*
将"动作"封装成对象是理解行为型模式的重要基础

模板方法
    对子类的动作顺序约束
    动作延迟到子类中实现
*/
int main() {

    cout << "************************" << endl;
    MakeOrder *p1 = new Foxcom;
    p1->make();
    // p1->startOrder();
    // p1->replyStart();
    // p1->finishOrder();
    // p1->replyFinish();

    cout << "************************" << endl;
    MakeOrder *p2 = new Samsung;
    p2->make();
    // p2->startOrder();
    // p2->replyStart();
    // p2->finishOrder();
    // p2->replyFinish();
    
    return 0;
}
