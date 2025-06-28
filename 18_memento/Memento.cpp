#include <iostream>

using namespace std;


class OriginalMessage;

//如何在不破坏类的封装性的前提下，来保存和恢复对象的状态。
class Memento {
public:
    Memento(string msg) : m_msg(msg) {}

private:
    friend class OriginalMessage;
    
    // OriginalMessage 是 Memento 的友元函数
    // 在 OriginalMessage 中，可以调用 Memento 的私有函数
    string getMsg() {
        return m_msg;
    }
    
    string m_msg;
};

// 使用 Memento 记录 OriginalMessage 的快照
class OriginalMessage {
public:
    OriginalMessage(string msg) : m_msg(msg) {}

    //存档
    Memento* saveMsg() {
        return new Memento(m_msg);
    }

    //恢复存档
    void restoreMsg(Memento *memento) {
        m_msg = memento->getMsg(); // OriginalMessage 是 Memento 的友元函数
    }

    void showMsg() {
        cout << m_msg << endl;
    }
private:
    string m_msg;
};

//设置快照，获得快照
class CareTaker {
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
备忘录
    如何在不破坏类的封装性的前提下，来保存和恢复对象的状态。
    应用: 消息管理器

数据库快照

Http 的 Session 机制
    Session，备忘录
    服务器，CareTaker
    原消息，浏览器

浏览器的 Cookie 机制
    Cookie，备忘录
    浏览器，CareTaker
    原消息，服务器
*/
int main() {

    OriginalMessage *msg = new OriginalMessage("Hello");
    cout << "********************* the first msg" << endl;
    msg->showMsg();

    CareTaker *care = new CareTaker;
    care->setMemento(msg->saveMsg()); // save

    msg = new OriginalMessage("World");
    cout << "********************* the second msg" << endl;
    msg->showMsg();

    msg = new OriginalMessage("haha");
    cout << "********************* the third msg" << endl;
    msg->showMsg();

    //恢复备忘录
    msg->restoreMsg(care->getMemento()); // restore
    cout << "********************* restore the first msg" << endl;
    msg->showMsg();

    return 0;
}
