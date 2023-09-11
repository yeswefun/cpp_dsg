#include <iostream>
#include <vector>
#include <array>
using namespace std;


class MyVector {
public:
    MyVector(vector<int> v) : m_vector(v) {}
    void showItems() {
        for (vector<int>::iterator it = m_vector.begin(); it != m_vector.end(); it++) {
            cout << *it << endl;
        }
    }
private:
    vector<int> m_vector;
};

class MyArray {
public:
    MyArray(array<int, 16> a) : m_array(a) {}
    void showItems() {
        for (int i = 0; i < m_array.size(); i++) {
            cout << m_array[i] << endl;
        }
    }
private:
    array<int, 16> m_array;
};

/*
STL: STandard Template Library
    算法 与 容器 的隔离 -- Iterator
*/
int main() {
    return 0;
}
