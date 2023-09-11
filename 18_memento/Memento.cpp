#include <iostream>

using namespace std;


class OriginalMessage;

class Memento {
public:
    Memento(string msg) : m_msg(msg) {}
private:
    friend class OriginalMessage;
    string getMsg() {
        return m_msg;
    }
    string m_msg;
};

class OriginalMessage {
public:
    OriginalMessage(string msg) : m_msg(msg) {}

    //存档
    Memento* saveMsg() {
        return new Memento(m_msg);
    }

    //恢复存档
    void restoreMsg(Memento *memento) {
        m_msg = memento->getMsg();
        cout << "restoreMsg" << endl;
    }

    void showMsg() {
        cout << m_msg << endl;
    }
private:
    string m_msg;
};

//设置快照，获得快照
class CareTake {
public:
    void setMemento(Memento *memento) {
        m_memento = memento;
    }
    Memento* getMemento() {
        return m_memento;
    }
private:
    Memento* m_memento;
};


/*
*/
int main() {

    OriginalMessage *msg = new OriginalMessage("Hello");
    cout << "********************* the first msg" << endl;
    msg->showMsg();

    CareTake *care = new CareTake;
    care->setMemento(msg->saveMsg());

    OriginalMessage *msg2 = new OriginalMessage("World");
    cout << "********************* the second msg" << endl;
    msg2->showMsg();

    OriginalMessage *msg3 = new OriginalMessage("haha");
    cout << "********************* the third msg" << endl;
    msg3->showMsg();

    //恢复备忘录
    msg->restoreMsg(care->getMemento());
    cout << "********************* restore the first msg" << endl;
    msg->showMsg();

    return 0;
}
