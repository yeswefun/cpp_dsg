#include <iostream>
#include <deque>

using namespace std;

//声明提前
template <class T>
class Auto_Ptr;


//********************************* Ref_Ptr
template <class T>
class Ref_Ptr {
    //声明友元类
    friend class Auto_Ptr<T>;
private:
    //实际指针
    T* m_ptr;
    
    //引用计数
    size_t m_refCount;

    Ref_Ptr(T *p);
    virtual ~Ref_Ptr();
};

template <class T>
Ref_Ptr<T>::Ref_Ptr(T *p) {
    m_ptr = p;
    m_refCount = 1;
    cout << "主题构造: Ref_Ptr<T>::Ref_Ptr(T *p)" << endl;
}

template <class T>
Ref_Ptr<T>::~Ref_Ptr() {
    if (m_ptr) {
        m_refCount = 0;
        delete m_ptr;
        m_ptr = nullptr;
        cout << "主题析构: Ref_Ptr<T>::~Ref_Ptr()" << endl;
    }
}



//********************************* Auto_Ptr, 智能指针
template <class T>
class Auto_Ptr {
public:
    Auto_Ptr();
    Auto_Ptr(T *p);
    //拷贝构造
    Auto_Ptr(const Auto_Ptr &o);
    ~Auto_Ptr();
    //运算符重载，难理解
    Auto_Ptr<T>& operator=(const Auto_Ptr &o);
    T& operator*();
    T* operator->();
private:
    Ref_Ptr<T> *m_ref;
};

template <class T>
Auto_Ptr<T>::Auto_Ptr() {
    m_ref = nullptr;
    cout << "代理构造: Auto_Ptr<T>::Auto_Ptr()" << endl;
}

template <class T>
Auto_Ptr<T>::Auto_Ptr(T *p) {
    m_ref = new Ref_Ptr<T>(p);
    cout << "代理构造: Auto_Ptr<T>::Auto_Ptr(T *p)" << endl;
}

/*
    Auto_Ptr<int> ap1(new int(6));
    Auto_Ptr<int> ap2(ap1);  // invoked
    Auto_Ptr<int> ap2 = ap1; // invoked
*/
template <class T>
Auto_Ptr<T>::Auto_Ptr(const Auto_Ptr<T>& o) {
    m_ref = o.m_ref;
    ++(m_ref->m_refCount);
    cout << "代理构造: Auto_Ptr<T>::Auto_Ptr(Auto_Ptr<T>& o)" << endl;
}

/*
    Auto_Ptr<int> ap1(new int(6));
    Auto_Ptr<int> ap2;
    ap1 = ap2; // invoked
*/
template <class T>
Auto_Ptr<T>& Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o) {
    //防止自赋值
    //if (this == o) {return *this;}

    //左操作数指向了新的对象，所以左操作数-1
    if (m_ref) {
        if (--(m_ref->m_refCount) == 0) {
            delete m_ref;
            m_ref = nullptr;
        }
    }

    //右操作数引用+1
    ++(o.m_ref->m_refCount);

    m_ref = o.m_ref;

    cout << "代理构造: Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o), ptr:" << m_ref->m_ptr << ", cnt: " << m_ref->m_refCount << endl;
    return *this;
}

/*
    Auto_Ptr<int> inner(new int(6));
    cout << "*inner: " << *inner << endl; // 6
*/
template <class T>
T& Auto_Ptr<T>::operator*() {
    return *(m_ref->m_ptr);
}

/*
    deque<int> *d = new deque<int>;
    d->push_back(1);
    d->push_back(2);
    d->push_back(3);
    Auto_Ptr<deque<int>> ap(d);

    cout << "size: " << (*ap).size() << endl; // size: 3
    cout << "size: " << ap->size() << endl;   // size: 3
*/
template <class T>
T* Auto_Ptr<T>::operator->() {
    return m_ref->m_ptr;
}

template <class T>
Auto_Ptr<T>::~Auto_Ptr() {
    if (--(m_ref->m_refCount) == 0) {
        delete m_ref;
        m_ref = nullptr;
    }
    cout << "代理析构: Auto_Ptr<T>::~Auto_Ptr()";
    if (m_ref) {
        cout << ", ptr: " << m_ref->m_ptr << ", cnt: " << m_ref->m_refCount;
    }
    cout << endl;
}



/*
智能指针
    代理模式
*/
int main() {

    {
        Auto_Ptr<int> outer;

        {
            //tag-1
            Auto_Ptr<int> inner(new int(888));
            cout << "*inner: " << *inner << endl; // 888

            //tag-2
            //assignment operator
            outer = inner;
        }//tag-3

        //tag-4
        //new int(888)没有销毁
        Auto_Ptr<int> x(new int(666));

        //tag-5
        //new int(888)被销毁
        outer = x;

        //ref_count has no effect
        Auto_Ptr<int> *y = &x;
        cout << "*(*y): " << *(*y) << endl; // 666
    }

    cout << "---------------------------" << endl;
    deque<int> *d = new deque<int>;
    d->push_back(1);
    d->push_back(2);
    d->push_back(3);
    Auto_Ptr<deque<int>> ap(d);

    cout << "size: " << (*ap).size() << endl;
    cout << "size: " << ap->size() << endl;

    return 0;
}

/*

代理构造: Auto_Ptr<T>::Auto_Ptr()
主题构造: Ref_Ptr<T>::Ref_Ptr(T *p)
代理构造: Auto_Ptr<T>::Auto_Ptr(T *p)
*inner: 888
代理构造: Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o), ptr:0xeb6ef0, cnt: 2
代理析构: Auto_Ptr<T>::~Auto_Ptr(), ptr: 0xeb6ef0, cnt: 1
主题构造: Ref_Ptr<T>::Ref_Ptr(T *p)
代理构造: Auto_Ptr<T>::Auto_Ptr(T *p)
主题析构: Ref_Ptr<T>::~Ref_Ptr()
代理构造: Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o), ptr:0xeb6f60, cnt: 2
*(*y): 666
代理析构: Auto_Ptr<T>::~Auto_Ptr(), ptr: 0xeb6f60, cnt: 1
主题析构: Ref_Ptr<T>::~Ref_Ptr()
代理析构: Auto_Ptr<T>::~Auto_Ptr()
---------------------------
主题构造: Ref_Ptr<T>::Ref_Ptr(T *p)
代理构造: Auto_Ptr<T>::Auto_Ptr(T *p)
size: 3
size: 3
主题析构: Ref_Ptr<T>::~Ref_Ptr()
代理析构: Auto_Ptr<T>::~Auto_Ptr()

*/