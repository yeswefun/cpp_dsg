#include "Express.h"
#include "UnaryNode.h"


// UnaryNode::UnaryNode() {
// }

UnaryNode::UnaryNode(char c, class Express left) : m_op(c), m_left(left) {
}

UnaryNode::~UnaryNode() {
}

void UnaryNode::print(ostream &out) const {
    out << "(" << m_op << m_left << ")";
}

int UnaryNode::eval() const {
    if (m_op == '-') {
        return (-1) * m_left.eval();
    }
    // '+'
    throw "err: invalid operator";
}
