#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 策略接口
class SortingStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
};

// 具体策略 - 冒泡排序
class BubbleSort : public SortingStrategy {
public:
    void sort(vector<int>& data) override {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (data[j] < data[j + 1]) { // > 表示(升序排列)，此处使用 < ，表示从大到小，降序排列
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

// 具体策略 - 快速排序
class QuickSort : public SortingStrategy {
public:
    void sort(vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

// 上下文 - 排序器
class Sorter {
public:
    Sorter(SortingStrategy* strategy) : m_strategy(strategy) {}

    void setStrategy(SortingStrategy* strategy) {
        m_strategy = strategy;
    }

    void sort(vector<int>& data) {
        if (m_strategy) {
            m_strategy->sort(data);
        }
    }

private:
    SortingStrategy* m_strategy;
};

void printData(string tag, vector<int> data) {
    cout << tag;
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;
}

/*
策略模式
    允许定义一系列算法，将每个算法封装为一个独立的对象，并使它们可以互相替换。
    这种模式使得算法的选择可以在运行时动态改变，而不需要修改客户端代码。

策略模式通常包括以下几个关键角色：
    Context(上下文)：上下文是包含一个策略对象的类，它负责将客户端的请求委派给具体的策略对象来执行。上下文类通常具有一个指向策略对象的指针或引用，并提供一个接口来切换策略。
    Strategy(策略) ：策略是一个接口或抽象类，定义了一组算法的共同接口，具体策略类实现了这个接口，每个具体策略类代表了一个不同的算法。
*/
int main() {
    vector<int> data = {5, 1, 4, 2, 8};

    BubbleSort bubbleSort;
    QuickSort quickSort;

    Sorter sorter(&bubbleSort);
    sorter.sort(data);
    printData("Using Bubble Sort: ", data);

    sorter.setStrategy(&quickSort);
    sorter.sort(data);
    printData("Using Quick Sort: ", data);

    return 0;
}
