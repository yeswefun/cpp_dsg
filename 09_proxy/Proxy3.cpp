#include <iostream>
#include <string>

using namespace std;

class AbstractServer {
public:
    virtual void request() = 0;
protected:
    AbstractServer(){}
};


class RealServer : public AbstractServer {
public:
    void request() {
        cout << "服务器启动" << endl;
    }
};

class ProxyServer : public AbstractServer {
public:
    ProxyServer(string name, string code) : m_name(name), m_code(code) {
        m_server = new RealServer;
    }

    void request() {
        if ("root" == m_name && "1234" == m_code) {
            cout << "success" << endl;
            cout << "************************ before request" << endl;
            m_server->request();
            cout << "************************ after request" << endl;
        } else {
            cout << "failure" << endl;
        }
    }
private:
    string m_name;
    string m_code;
    AbstractServer *m_server;
};


int main() {

    AbstractServer *proxy = new ProxyServer("root", "1234");
    proxy->request();

    return 0;
}
