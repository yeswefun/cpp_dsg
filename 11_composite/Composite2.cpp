#include <iostream>
#include <string>
#include <list>

using namespace std;

class IFile {
public:
    virtual void display() = 0;

    virtual int add(IFile *iFile) = 0;

    virtual int remove(IFile *iFile) = 0;

    virtual list<IFile*>* getChildList() = 0;
};

//Leaf
class File : public IFile {
public:
    File(string name) : m_name(name) {}
    void display() {
        cout << m_name << endl;
    }
    //只有目录才能添加文件
    int add(IFile *iFile) {
        return -1;
    }
    //只有目录才能删除文件
    int remove(IFile *iFile) {
        return -1;
    }
    //只有目录才能获取文件列表
    list<IFile*>* getChildList() {
        return nullptr;
    }
private:
    string m_name;
};

//Composite
class Dir : public IFile {
public:
    Dir(string name) : m_name(name) {
        m_list = new list<IFile*>;
    }
    void display() {
        cout << m_name << endl;
    }
    int add(IFile *iFile) {
        m_list->push_back(iFile);
        return 0;
    }
    int remove(IFile *iFile) {
        m_list->remove(iFile);
        return 0;
    }
    list<IFile*>* getChildList() {
        return m_list;
    }
private:
    string m_name;
    list<IFile*> *m_list;
};


void showTree(IFile *root, int level) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        cout << "\t";
    }

    root->display();
    list<IFile*> *lst = root->getChildList();
    if (lst != nullptr) {
        for (list<IFile*>::iterator it = lst->begin(); it != lst->end(); it++) {
            if ((*it)->getChildList() == nullptr) {
                //file
                for (int i = 0; i < level+1; i++) {
                    cout << "\t";
                }
                (*it)->display();
            } else {
                showTree(*it, level+1);
            }
        }
    }
}


int main() {

    Dir *root = new Dir("/home/lin/");

    Dir *dir1 = new Dir("proj");
    Dir *dir2 = new Dir("note");

    File *file1 = new File("a.txt");
    File *file2 = new File("b.txt");
    File *file3 = new File("c.txt");
    File *file4 = new File("d.txt");

    root->add(dir1);
    root->add(dir2);
    root->add(file1);

    dir1->add(file2);
    dir1->add(file3);

    dir2->add(file4);

    showTree(root, 0);

    return 0;
}
