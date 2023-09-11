#include "BinaryNode.h"

// BinaryNode::BinaryNode() {
// }

BinaryNode::BinaryNode(char c, class Express left, class Express right) : m_op(c), m_left(left), m_right(right) {
}

BinaryNode::~BinaryNode() {
}

void BinaryNode::print(ostream &out) const {
    out << "(" << m_left << m_op << m_right << ")";
}

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
    }
    throw "err: binary merge, invalid operator";
}
