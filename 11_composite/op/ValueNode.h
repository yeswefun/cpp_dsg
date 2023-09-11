#pragma once


#include "Express.h"
#include "ExpressNode.h"

class ValueNode : public ExpressNode {
public:
    friend class Express;

    ValueNode();
    ValueNode(int value) : m_value(value) {}
    ~ValueNode() {}
private:
    int m_value;

    void print(ostream &out) const {
        out << m_value;
    }

    int eval() const {
        return m_value;
    }
};
