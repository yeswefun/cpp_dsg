#include "ExpressNode.h"
#include "ValueNode.h"
#include "UnaryNode.h"
#include "BinaryNode.h"
#include "Express.h"

/*
Composite
Component

$ g++ -I ./include Z.cpp Express.cpp ExpressNode.cpp UnaryNode.cpp BinaryNode.cpp && ./a.exe

组合模式
递归型: 部分也是整体

Express::ExpressNode

ExpressNode
    ValueNode
    UnaryNode
    BinaryNode

cout << t << endl; // Express#operator<<
cout << (*t.m_pEn) << endl; // ExpressNode#operator<<
en.print(out); // ExpressNode#print 是 虚函数，所以该函数延迟到子类中实现
*/
int main() {

    Express t = Express(3); // ValueNode
    cout << t << " = " << t.eval() << endl;

    t = Express('+', t, 12); // BinaryNode
    cout << t  << " = " << t.eval() << endl;

    Express y = Express('-', 4); // UnaryNode
    cout << y << " = " << y.eval() << endl;

    Express t1 = Express('*', Express('-', 5), Express('+', 3, 4)); // BinaryNode
    cout << t1 << " = " << t1.eval() << endl;

    return 0;
}

/*
            +
        5       x
            -       4
        1       2
*/
