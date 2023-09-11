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

    //模板方法
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
        cout << "Foxcom start order" << endl;
    }
    void replyStart() {
        cout << "Foxcom reply start" << endl;
    }
    void finishOrder() {
        cout << "Foxcom finish order" << endl;
    }
    void replyFinish() {
        cout << "Foxcom reply finish" << endl;
    }
};

class Samsung : public MakeOrder {
public:
    void startOrder() {
        cout << "Samsung start order" << endl;
    }
    void replyStart() {
        cout << "Samsung reply start" << endl;
    }
    void finishOrder() {
        cout << "Samsung finish order" << endl;
    }
    void replyFinish() {
        cout << "Samsung reply finish" << endl;
    }
};


/*
模板方法
    对子类的动作约束
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
