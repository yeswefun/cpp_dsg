#include <iostream>
#include <stack>
#include <deque>
#include <iterator>

using namespace std;

int main() {

    deque<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);

    stack<int> s(q);

    cout << "------------------------ deque-1" << endl;
    for (deque<int>::iterator it = q.begin(); it != q.end(); it++) {
        cout << *it << endl;
    }
    cout << "------------------------ deque-2" << endl;
    for (int v : q) {
        cout << v << endl;
    }
    cout << "------------------------ stack" << endl;
    // class "std::stack<int, std::deque<int, std::allocator<int>>>" has no member "iterator"
    // for (stack<int>::iterator it = s.begin(); it != s.end(); it++) {
    //     cout << *it << endl;
    // }
    // this range-based 'for' statement requires a suitable "begin" function and none was found
    // for (int v : s) {
    //     cout << v << endl;
    // }
    while(!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }   

    return 0;
}
