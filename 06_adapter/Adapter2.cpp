#include <iostream>
#include <deque>
#include <stack>

using namespace std;


/*
用 STL 默认的适配器 将 deque 转换成 stack
*/
int main() {

    deque<int> myDeque(3, 100);
    
    stack<int> myStack;
    stack<int> myStack2(myDeque); // 转换
    cout << "stack size: " << myStack.size() << endl;
    cout << "stack2 size: " << myStack2.size() << endl;

    myStack2.pop();
    cout << "stack2 size: " << myStack2.size() << endl;
    cout << "stack2 top: " << myStack2.top() << endl;

    cout << "deque size: " << myDeque.size() << endl;

    return 0;
}
