#include <iostream>
#include <string>
#include <list>

using namespace std;


class Leaf {
public:
    Leaf(string name) : m_name(name) {}
    void showStruct(string preStr) {
        cout << preStr << "-" << m_name << endl;
    }
private:
    string m_name;
};

//目录
class Composite {
public:
    Composite(string name) : m_name(name) {}
    void addComposite(Composite *pCom) {
        childComposite.push_back(pCom);
    }
    void addLeaf(Leaf *pLeaf) {
        childLeaf.push_back(pLeaf);
    }
    void showStruct(string preStr) {
        cout << preStr << "+" << m_name << endl;
        preStr += "\t";
        //当前对象包含的叶子对象列表
        for (list<Leaf*>::iterator it = childLeaf.begin(); it != childLeaf.end(); it++) {
            (*it)->showStruct(preStr);
        }
        //当前对象
        for (list<Composite*>::iterator it = childComposite.begin(); it != childComposite.end(); it++) {
            (*it)->showStruct(preStr);
        }
    }
private:
    string m_name;
    list<Leaf*> childLeaf;
    list<Composite*> childComposite;
};


int main() {
    Composite *pRoot = new Composite("/home/lin/");
    Composite *pC1 = new Composite("proj");
    Composite *pC2 = new Composite("tool");
    Leaf *pLeaf1 = new Leaf("a.txt");
    Leaf *pLeaf2 = new Leaf("a.py");
    Leaf *pLeaf3 = new Leaf("a.cpp");
    pRoot->addComposite(pC1);
    pRoot->addComposite(pC2);
    pC1->addLeaf(pLeaf1);
    pC1->addLeaf(pLeaf2);
    pC2->addLeaf(pLeaf3);
    pRoot->showStruct("");
    return 0;
}
