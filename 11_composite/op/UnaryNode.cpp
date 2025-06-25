#include "Express.h"
#include "UnaryNode.h"

UnaryNode::UnaryNode(char c, Express right) : m_op(c), m_right(right) {
}

UnaryNode::~UnaryNode() {
}

// (-1)
void UnaryNode::print(ostream &out) const {
    out << "(" << m_op << m_right << ")";
}

// -1
int UnaryNode::eval() const {
    if (m_op == '-') {
        return (-1) * m_right.eval();
    }
    // '+'
    throw "err: invalid operator";
}
