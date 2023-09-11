#include <iostream>

using namespace std;



//********************************* Ref_Ptr
template <class T>
class Auto_Ptr;

template <class T>
class Ref_Ptr {
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
    cout << "Ref_Ptr<T>::Ref_Ptr(T *p)" << endl;
}

template <class T>
Ref_Ptr<T>::~Ref_Ptr() {
    if (m_ptr) {
        m_refCount = 0;
        delete m_ptr;
        m_ptr = nullptr;
        cout << "Ref_Ptr<T>::~Ref_Ptr()" << endl;
    }
}



//********************************* Auto_Ptr, 智能指针对象
template <class T>
class Auto_Ptr {
public:
    Auto_Ptr();
    Auto_Ptr(T *p);
    Auto_Ptr(const Auto_Ptr &o);
    ~Auto_Ptr();
    //运算符重载
    Auto_Ptr<T>& operator=(const Auto_Ptr &o);
    T& operator*();
    T* operator->();
private:
    Ref_Ptr<T> *m_ref;
};

template <class T>
Auto_Ptr<T>::Auto_Ptr() {
    m_ref = nullptr;
}

template <class T>
Auto_Ptr<T>::Auto_Ptr(T *p) {
    m_ref = new Ref_Ptr<T>(p);
    cout << "Auto_Ptr<T>::Auto_Ptr(T *p)" << endl;
}

template <class T>
Auto_Ptr<T>::Auto_Ptr(const Auto_Ptr<T>& o) {
    m_ref = o.m_ref;
    ++(m_ref->m_refCount);
    cout << "Auto_Ptr<T>::Auto_Ptr(Auto_Ptr<T>& o)" << endl;
}

template <class T>
Auto_Ptr<T>& Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o) {
    //防止自赋值
    //if (this == o) {return *this;}

    //左操作数指向了新的对象，所以引用-1
    if (m_ref) {
        if (--(m_ref->m_refCount) == 0) {
            delete m_ref;
            m_ref = nullptr;
        }
    }

    //右操作数引用+1
    ++(o.m_ref->m_refCount);

    m_ref = o.m_ref;

    cout << "Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o)" << endl;
    return *this;
}

template <class T>
T& Auto_Ptr<T>::operator*() {
    return *(m_ref->m_ptr);
}

template <class T>
T* Auto_Ptr<T>::operator->() {
    return m_ref->m_ptr;
}

template <class T>
Auto_Ptr<T>::~Auto_Ptr() {
    cout << "Auto_Ptr<T>::~Auto_Ptr()" << endl;
    if (--(m_ref->m_refCount) == 0) {
        delete m_ref;
        m_ref = nullptr;
    }
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
            Auto_Ptr<int> inner(new int(4));
            cout << "*inner: " << *inner << endl;

            //tag-2
            //assignment operator
            outer = inner;
        }//tag-3

        //tag-4
        //new int(4)没有销毁
        Auto_Ptr<int> x(new int(3));

        //tag-5
        outer = x;

        //nothing happens
        Auto_Ptr<int> *y = &x;
        cout << "*(*y): " << *(*y) << endl;
    }

    return 0;
}

/*
//tag-1
Ref_Ptr<T>::Ref_Ptr(T *p)
Auto_Ptr<T>::Auto_Ptr(T *p)
*inner: 4

//tag-2
Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o)

//tag-3
Auto_Ptr<T>::~Auto_Ptr()

//tag-4
Ref_Ptr<T>::Ref_Ptr(T *p)
Auto_Ptr<T>::Auto_Ptr(T *p)

//tag-5
Ref_Ptr<T>::~Ref_Ptr()
Auto_Ptr<T>::operator=(const Auto_Ptr<T>& o)
*(*y): 3
Auto_Ptr<T>::~Auto_Ptr()
Auto_Ptr<T>::~Auto_Ptr()
Ref_Ptr<T>::~Ref_Ptr()
*/