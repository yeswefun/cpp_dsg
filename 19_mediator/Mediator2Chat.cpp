#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 前向声明
class ChatMediator;

// 抽象同事
class User {
public:
    User(const string& name, ChatMediator* mediator);

    virtual void sendMessage(const string& message);
    virtual void receiveMessage(const string& message);

protected:
    string m_name;
    ChatMediator* m_mediator;
};

// 抽象中介者
class ChatMediator {
public:
    virtual void sendMessage(const string& message, User* user) = 0;
    virtual void addUser(User* user) = 0;
};

// 具体中介者
class ChatRoom : public ChatMediator {
public:
    void sendMessage(const string& message, User* user) override {
        for (User* u : m_users) {
            if (u != user) {
                u->receiveMessage(message);
            }
        }
    }

    void addUser(User* user) override {
        m_users.push_back(user);
    }

private:
    vector<User*> m_users;
};

// 具体同事
User::User(const string& name, ChatMediator* mediator) : m_name(name), m_mediator(mediator) {
    m_mediator->addUser(this);
}

void User::sendMessage(const string& message) {
    m_mediator->sendMessage(message + "("+m_name+")", this);
}

void User::receiveMessage(const string& message) {
    cout << m_name << " received message: " << message << endl;
}

/*
中介模式
    用于降低多个对象之间的直接通信，将对象之间的交互集中到一个中介对象中。
    中介模式有助于解耦系统中的对象，使它们不需要直接了解彼此，从而提高了系统的可维护性和可扩展性

    在中介模式中，通常会有一个中介者对象，它负责处理不同对象之间的通信和协作。
    每个对象都通过中介者来发送和接收消息，而不是直接与其他对象通信。
    这种方式有助于减少对象之间的依赖关系，使系统更容易维护和扩展。

中介模式通常包括以下几个关键角色：
    Mediator（中介者）：中介者是一个抽象类或接口，它定义了用于处理对象之间通信的方法，通常包括注册对象、发送消息等操作。
    ConcreteMediator（具体中介者）：具体中介者是中介者的实现类，它负责协调和管理不同对象之间的交互。

    Colleague（同事）：同事是指系统中的各个对象，它们通过中介者来进行通信，而不是直接与其他同事对象交互。
    ConcreteColleague（具体同事）：具体同事是同事的实现类，它们通过中介者与其他同事对象交互。
*/
int main() {
    ChatMediator* mediator = new ChatRoom();
    User* user1 = new User("Alice", mediator);
    User* user2 = new User("Bob", mediator);
    //User* user3 = new User("Jerry", mediator); // try

    user1->sendMessage("Hello, Bob!");
    user2->sendMessage("Hi, Alice!");
    //user3->sendMessage("Hi, Everyone!"); // try

    delete user1;
    delete user2;
    delete mediator;

    return 0;
}
