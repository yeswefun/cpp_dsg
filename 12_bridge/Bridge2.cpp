#include <iostream>

using namespace std;

class IOS {
public:
    IOS() {}
    virtual ~IOS() {}
    virtual void run() = 0;
};

class CWindows : public IOS {
public:
    void run() {
        cout << "-> Windows" << endl;
    }
};

class CLinux : public IOS {
public:
    void run() {
        cout << "-> Linux" << endl;
    }
};

//桥接的核心
class IComputer {
public:
    virtual void install(IOS *os) = 0;
};

class CRedmi : public IComputer {
public:
    void install(IOS *os) {
        cout << "Redmi: ";
        os->run();
    }
};

class CDell : public IComputer {
public:
    void install(IOS *os) {
        cout << "Dell: ";
        os->run();
    }
};


/*
IComputer - IOS

IArchive - IFile
*/
int main() {
    IOS *win = new CWindows;
    IOS *lin = new CLinux;
    
    IComputer *pRedmi = new CRedmi;
    pRedmi->install(win);
    pRedmi->install(lin);

    IComputer *pDell = new CDell;
    pDell->install(win);
    pDell->install(lin);

    return 0;
}
