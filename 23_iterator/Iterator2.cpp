#include <iostream>
#include <vector>
#include <array>
using namespace std;


/*
STL: STandard Template Library
    算法 与 容器 的隔离 -- Iterator
*/
int main() {

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }

    cout << "************************" << endl;
    array<int, 3> a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    for (auto it = a.begin(); it != a.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
