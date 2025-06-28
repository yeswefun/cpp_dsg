#include <iostream>
#include <vector>

using namespace std;

// 抽象迭代器
template <typename T>
class Iterator {
public:
    virtual T next() = 0;
    virtual bool hasNext() = 0;
};

// 具体迭代器
template <typename T>
class MyListIterator : public Iterator<T> {
public:
    MyListIterator(const vector<T>& data) : v(data), index(0) {}

    T next() override {
        if (hasNext()) {
            return v[index++];
        } else {
            throw out_of_range("No more elements");
        }
    }

    bool hasNext() override {
        return index < v.size();
    }

private:
    vector<T> v;
    size_t index;
};

// 聚合对象
template <typename T>
class MyList {
public:
    MyList() {}

    void add(const T& item) {
        data_.push_back(item);
    }

    Iterator<T>* createIterator() {
        return new MyListIterator<T>(data_);
    }

private:
    vector<T> data_;
};

/*
迭代器模式
    它用于提供一种统一的方式来访问聚合对象(如数组，列表，集合等)中的元素，而无需暴露其内部结构。
    迭代器模式分离了聚合对象的遍历算法和数据存储，使得遍历过程更加灵活和可扩展。

迭代器模式通常包括以下几个关键角色：
    Iterator(迭代器)：迭代器是一个抽象接口或类，定义了用于访问聚合对象中元素的方法，例如获取下一个元素，检查是否还有元素等。
    ConcreteIterator(具体迭代器)：具体迭代器是实现迭代器接口的具体类，它实现了遍历聚合对象的具体逻辑。

    Aggregate(聚合对象)：聚合对象是包含一组元素的对象，通常具有一个方法，用于创建迭代器对象以访问其元素。
    ConcreteAggregate(具体聚合对象)：具体聚合对象是实现聚合接口的具体类，它创建并返回具体迭代器对象，以便遍历其元素。
*/
int main() {
    MyList<int> myList;
    myList.add(1);
    myList.add(2);
    myList.add(3);

    Iterator<int>* iterator = myList.createIterator();

    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;

    delete iterator;

    return 0;
}
