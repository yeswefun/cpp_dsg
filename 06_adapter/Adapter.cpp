#include <iostream>

using namespace std;


class ThreePhaseOutlet {
public:
    void doThreePhasePlug() {
        cout << "three phase" << endl;
    }
};


class TwoPhaseOutlet {
public:
    virtual void doPlug() = 0;
};


/*
类适配
    从 二相插头 派生出来的类都可以转换
*/
class OutletConvertor : public TwoPhaseOutlet, public ThreePhaseOutlet {
public:
    void doPlug() {
        doConvert();
        doThreePhasePlug();
    }

    void doConvert() {
        cout << "three phase -> two phase" << endl;
    }
};


/*
对象适配
    单个对象
    更常用，更加灵活
*/
class OutletObjConvertor : public TwoPhaseOutlet {
public:
    //只针对某个对象
    OutletObjConvertor(ThreePhaseOutlet *out) : m_out(out) {
    }

    void doPlug() {
        doConvert();
        m_out->doThreePhasePlug();
    }

    void doConvert() {
        cout << "three phase -> two phase" << endl;
    }
private:
    ThreePhaseOutlet *m_out;
};


/*
三相 转换成 二相

类适配
    从 二相插头 派生出来的类都可以转换

对象适配
    单个对象
    更常用，更加灵活
*/
int main() {

    cout << "****************** class" << endl;
    TwoPhaseOutlet *pOutlet = new OutletConvertor();
    pOutlet->doPlug();

    cout << "****************** object" << endl;
    TwoPhaseOutlet *pOutlet2 = new OutletObjConvertor(new ThreePhaseOutlet());
    pOutlet2->doPlug();

    return 0;
}
