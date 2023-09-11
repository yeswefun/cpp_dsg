#include <iostream>

using namespace std;

class XiaoMi;
class RedMi;

//++++++++++++++++++++++++++++++
class CellPhoneVisitor {
public:
    virtual void visit(XiaoMi *p) = 0;
    virtual void visit(RedMi *p) = 0;
    //...
protected:
    CellPhoneVisitor() {}
};

/*
Solaris
Win7
Win8
Win10
...
*/
class CellPhone {
public:
    virtual void dial() = 0;
    virtual void sendMsg() = 0;
    virtual void hand() = 0;
    virtual void recvMsg() = 0;
    //++++++++++++++++++++++++++++++
    virtual void accept(CellPhoneVisitor *p) = 0;
protected:
    CellPhone() {}
};

class XiaoMi : public CellPhone {
public:
    void dial() {
        cout << "XiaoMi -> dial" << endl;
    }
    void sendMsg() {
        cout << "XiaoMi -> sendMsg" << endl;
    }
    void hand() {
        cout << "XiaoMi -> hand" << endl;
    }
    void recvMsg() {
        cout << "XiaoMi -> recvMsg" << endl;
    }
    void accept(CellPhoneVisitor *p) {
        p->visit(this);
    }
};

class RedMi : public CellPhone {
public:
    void dial() {
        cout << "RedMi -> dial" << endl;
    }
    void sendMsg() {
        cout << "RedMi -> sendMsg" << endl;
    }
    void hand() {
        cout << "RedMi -> hand" << endl;
    }
    void recvMsg() {
        cout << "RedMi -> recvMsg" << endl;
    }
    void accept(CellPhoneVisitor *p) {
        p->visit(this);
    }
};

class SolarisConfigure : public CellPhoneVisitor {
public:
    void visit(XiaoMi *p) {
        cout << "********************* XiaoMi" << endl;
        p->sendMsg();
        p->recvMsg();
    }
    void visit(RedMi *p) {
        cout << "********************* RedMi" << endl;
        p->dial();
        p->hand();
        p->sendMsg();
        p->recvMsg();
    }
};


/*
Visitor
    双重分发
        两个多态
            accept
                SolarisConfigure -> CellPhoneVisitor
            visit
                XiaoMi/RedMi -> CellPhone
*/
int main() {

    CellPhoneVisitor *visitor = new SolarisConfigure;
    XiaoMi *xm = new XiaoMi;
    RedMi *rm = new RedMi;
    xm->accept(visitor);
    rm->accept(visitor);

    return 0;
}
