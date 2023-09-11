#include "ExpressNode.h"
#include "ValueNode.h"
#include "UnaryNode.h"
#include "BinaryNode.h"
#include "Express.h"

/*
Composite
Component

$ g++ -I . .\Z.cpp .\Express.cpp .\ExpressNode.cpp .\UnaryNode.cpp .\BinaryNode.cpp; ./a.exe

递归型
部分也是整个
*/
int main() {

    Express t = Express(3);
    t = Express('+', t, 12);
    cout << t  << " = " << t.eval() << endl;

    Express y = Express('-', 4);
    cout << y << " = " << y.eval() << endl;

    Express t1 = Express('*', Express('-', 5), Express('+', 3, 4));
    cout << t1 << " = " << t1.eval() << endl;

    return 0;
}
