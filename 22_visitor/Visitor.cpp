#include <iostream>

using namespace std;

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
};


int main() {

    return 0;
}
