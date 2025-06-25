#include <iostream>

using namespace std;

class IOS {
public:
    IOS() {}
    virtual ~IOS() {}
    virtual void run() = 0;
};

class Windows : public IOS {
public:
    void run() {
        cout << "-> Windows" << endl;
    }
};

class Linux : public IOS {
public:
    void run() {
        cout << "-> Linux" << endl;
    }
};

class MacOS : public IOS {
public:
    void run() {
        cout << "-> MacOS" << endl;
    }
};

//桥接的核心
class IComputer {
public:
    virtual void install(IOS *os) = 0;
};

class Redmi : public IComputer {
public:
    void install(IOS *os) {
        cout << "Redmi: ";
        os->run();
    }
};

class Dell : public IComputer {
public:
    void install(IOS *os) {
        cout << "Dell: ";
        os->run();
    }
};


/*
一维扩展看继承
多维变化用桥接

方案整合商 & 操作系统, 多 对 多

多维变化用桥接

桥接: Computer x OS

Computer
    redmi
    dell
    mac

OS
    linux
    macos
    windows
*/
int main() {
    IOS *win = new Windows;
    IOS *lin = new Linux;
    IOS *mac = new MacOS;
    
    IComputer *pRedmi = new Redmi;
    pRedmi->install(win);
    pRedmi->install(lin);
    pRedmi->install(mac);

    IComputer *pDell = new Dell;
    pDell->install(win);
    pDell->install(lin);
    pDell->install(mac);

    return 0;
}
