#pragma once

#include <iostream>

using namespace std;

class ExpressNode {
public:
    friend class Express;

    ExpressNode() : m_refCnt(1) {}
    ~ExpressNode();

    int getRefCnt() const;
    void setRefCnt(int);

    // out << *(e.m_en)
    friend ostream& operator<<(ostream& out, const ExpressNode &en) {
        en.print(out);
        return out;
    }

protected:
    virtual void print(ostream &out) const = 0;
    virtual int eval() const = 0;

private:
    int m_refCnt;
};
