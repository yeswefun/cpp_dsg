#include <iostream>
#include <string>
#include <list>

using namespace std;

/*
文件
*/
class Leaf {
public:
    Leaf(string name) : m_name(name) {}
    void showStruct(string preStr) {
        cout << preStr << "-" << m_name << endl;
    }
private:
    string m_name;
};

/*
目录
    目录
    ...
    文件
    ...
*/
class Composite {
public:
    Composite(string name) : m_name(name) {}
    //子目录列表
    void addComposite(Composite *pCom) {
        childComposite.push_back(pCom);
    }
    //子文件列表
    void addLeaf(Leaf *pLeaf) {
        childLeaf.push_back(pLeaf);
    }
    //难理解
    void showStruct(string preStr) {
        cout << preStr << "+" << m_name << endl;
        preStr += "\t";
        //当前对象包含的目录对象列表
        for (list<Composite*>::iterator it = childComposite.begin(); it != childComposite.end(); it++) {
            (*it)->showStruct(preStr);
        }
        //当前对象包含的叶子对象列表
        for (list<Leaf*>::iterator it = childLeaf.begin(); it != childLeaf.end(); it++) {
            (*it)->showStruct(preStr);
        }
    }
private:
    string m_name;
    list<Leaf*> childLeaf;
    list<Composite*> childComposite;
};

/*
组合模式的实用工程技术——树形(递归)结构的面向对象实现 
*/
int main() {
    Composite *pRoot = new Composite("/home/lin/");
    Composite *pC1 = new Composite("proj");
    Composite *pC2 = new Composite("tool");
    Composite *pC3 = new Composite("note");
    Leaf *pLeaf1 = new Leaf("a.txt");
    Leaf *pLeaf2 = new Leaf("a.py");
    Leaf *pLeaf3 = new Leaf("a.cpp");
    // Composite 添加 子Composite
    pRoot->addComposite(pC1);
    pRoot->addComposite(pC2);
    pRoot->addLeaf(pLeaf1);
    pRoot->addLeaf(pLeaf2);
    pRoot->addLeaf(pLeaf3);
    // Composite 添加 子Leaf
    pC1->addLeaf(pLeaf1);
    pC1->addLeaf(pLeaf2);
    pC2->addLeaf(pLeaf3);
    pC2->addComposite(pC3);
    pC3->addLeaf(pLeaf1);
    pRoot->showStruct("|*|");
    return 0;
}

/*
|*|+/home/lin/
|*|     +proj
|*|             -a.txt
|*|             -a.py
|*|     +tool
|*|             +note
|*|                     -a.txt
|*|             -a.cpp
|*|     -a.txt
|*|     -a.py
|*|     -a.cpp
*/