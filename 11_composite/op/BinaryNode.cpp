#include "BinaryNode.h"

BinaryNode::BinaryNode(char op, Express left, Express right) : m_op(op), m_left(left), m_right(right) {
}

BinaryNode::~BinaryNode() {
}

// (1 + 2)
void BinaryNode::print(ostream &out) const {
    // out << "(" << m_left << m_op << m_right << ")";
    out << "(" << m_left << " " << m_op << " " << m_right << ")";
}

// 1 + 2
int BinaryNode::eval() const {
    int opl = m_left.eval();
    int opr = m_right.eval();
    switch (m_op) {
        case '+':
            return opl + opr;
        case '-':
            return opl - opr;
        case '*':
            return opl * opr;
        case '/':
            if (opr != 0)
                return opl / opr;
        default:
            throw "err: binary merge, invalid operator";
    }
}
