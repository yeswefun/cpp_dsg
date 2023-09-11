#pragma once

#include <iostream>

using namespace std;

class ExpressNode {
public:
    friend class Express;
    int getUse() const;
    void setUse(int);
    friend ostream& operator<<(ostream& out, const ExpressNode &node) {
        node.print(out);
        return out;
    }
    ExpressNode() : m_use(1) {}
    ~ExpressNode();

protected:
    virtual void print(ostream &out) const = 0;
    virtual int eval() const = 0;

private:
    int m_use;
};
