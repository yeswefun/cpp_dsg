#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <string>

using namespace std;

// 迭代器接口
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

// 具体迭代器
class VectorConcreteIterator : public Iterator {
public:
    explicit VectorConcreteIterator(vector<int> v) : v(v), index(0) {}

    bool hasNext() override {
        return index < v.size();
    }

    int next() override {
        return v[index++];
    }

private:
    vector<int> v;
    int index;
};

class DequeConcreteIterator : public Iterator {
public:
    explicit DequeConcreteIterator(deque<int> q) : q(q), index(0) {}

    bool hasNext() override {
        return index < q.size();
    }

    int next() override {
        return q[index++];
    }

private:
    deque<int> q;
    int index;
};

class ArrayConcreteIterator : public Iterator {
public:
    explicit ArrayConcreteIterator(array<int, 16> arr, int size) : arr(arr), size(size), index(0) {}

    bool hasNext() override {
        return index < size;
    }

    int next() override {
        return arr[index++];
    }
private:
    array<int, 16> arr;
    int index;
    int size;
};

class StringConcreteIterator : public Iterator {
public:
    explicit StringConcreteIterator(string str) : str(str), index(0) {}

    bool hasNext() override {
        return index < str.size();
    }

    int next() override {
        return str[index++];
    }
private:
    string str;
    int index;
};

// 聚合对象接口
class Aggregate {
public:
    virtual Iterator* createIterator() = 0;
};

// 具体聚合对象
class VectorConcreteAggregate : public Aggregate {
public:
    void add(int item) {
        v.push_back(item);
    }

    Iterator* createIterator() override {
        return new VectorConcreteIterator(v);
    }

private:
    vector<int> v;
};

class DequeConcreteAggregate : public Aggregate {
public:
    void add(int item) {
        q.push_back(item);
    }

    Iterator* createIterator() override {
        return new DequeConcreteIterator(q);
    }

private:
    deque<int> q;
};

class ArrayConcreteAggregate : public Aggregate {
public:
    ArrayConcreteAggregate() : index(0) {}
    void add(int item) {
        if (index < arr.size()) {
            arr[index++] = item;
        }
    }

    Iterator *createIterator() override {
        return new ArrayConcreteIterator(arr, index);
    }
private:
    array<int, 16> arr;
    int index;
};

class StringConcreteAggregate : public Aggregate {
public:
    void add(char c) {
        str += c;
    }

    void printString() {
        cout << "str: " << str << endl;
    }

    Iterator *createIterator() override {
        return new StringConcreteIterator(str);
    }
private:
    string str;
};

void printWithIterator(Iterator *iterator) {
    cout << "******************" << endl;
    while (iterator->hasNext()) {
        cout << iterator->next() << endl;
    }
}

/*
C++ STL 中支持随机访问的容器
    vector
    deque
    string
    
    array，不是STL的一部分，而是C++11引入的标准库组件
*/
int main() {
    
    Iterator* iterator;

    VectorConcreteAggregate vca;
    vca.add(1);
    vca.add(2);
    vca.add(3);
    iterator = vca.createIterator();
    printWithIterator(iterator);
    delete iterator;

    DequeConcreteAggregate dca;
    dca.add(11);
    dca.add(22);
    dca.add(33);
    iterator = dca.createIterator();
    printWithIterator(iterator);
    delete iterator;

    ArrayConcreteAggregate acg;
    acg.add(111);
    acg.add(222);
    acg.add(333);
    iterator = acg.createIterator();
    printWithIterator(iterator);
    delete iterator;

    StringConcreteAggregate scg;
    scg.add('A');
    scg.add('B');
    scg.add('C');
    scg.printString();
    iterator = scg.createIterator();
    printWithIterator(iterator);
    delete iterator;

    return 0;
}