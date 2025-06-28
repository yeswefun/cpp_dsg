#include <iostream>
#include <string>
#include <vector>

using namespace std;

//抽象的表达式对象 和 Context对象
//用于保存计算的蹭结果 和 当前执行的操作符
class Context {
public:
    int m_value;
    char m_op;
    Context() : m_value(0), m_op('\0') {}
};

//1+3-2

//表示所有表达式的抽象接口
class IExpression {
public:
    virtual void eval(Context *p) = 0;
};

//拆分表达式的元素
class Operator : public IExpression {
public:
    Operator(char op) : m_op(op) {}

    void eval(Context *p) {
        p->m_op = m_op;
    }
private:
    char m_op;
};


//拆分操作数
class Operand : public IExpression {
public:
    Operand(int num) : m_num(num) {}
    void eval(Context *p) {
        switch (p->m_op) {
            case '\0':
                p->m_value = m_num;
                break;
            case '+':
                p->m_value += m_num;
                break;
            case '-':
                p->m_value -= m_num;
                break;
            default:
                break;
        }
    }
private:
    int m_num;
};

class Calculator {
public:
    int calc(string expression) {
        
        //通过 Context 保护中间结果
        Context *p = new Context;
        vector<IExpression*> tree;
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == '+' || expression[i] == '-') {
                tree.push_back(new Operator(expression[i]));
                cout << "********* ep: " << i << " : " << expression[i] << endl;
            } else {
                tree.push_back(new Operand((int)(expression[i]-48)));
                cout << "--------- op: " << i << " : " << ((int)(expression[i]-48)) << endl;
            }
        }

        for (vector<IExpression*>::iterator it = tree.begin(); it != tree.end(); it++) {
            (*it)->eval(p);
            cout << p->m_value << " : " << p->m_op << endl;
        }

        return p->m_value;
    }
};


/*
一个简单加减法运算器

解释器与数据结构，算法和编译原理的内在关系
*/
int main() {

    Calculator *p = new Calculator;
    string s = "1+2-3+6";
    cout << s << endl << p->calc(s) << endl;

    return 0;
}
