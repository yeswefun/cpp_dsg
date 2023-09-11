#include "Express.h"
#include "ValueNode.h"
#include "UnaryNode.h"
#include "BinaryNode.h"

// ValueNode
Express::Express(int a) {
    m_p = new ValueNode(a);
}

// UnaryNode(char, int); eg: Express('+', t, 12);
Express::Express(char c, const Express e) {
    m_p = new UnaryNode(c, e);
}
// BinaryNode(char, int, int); eg: ('+', 3, 4);
Express::Express(char c, const Express el, const Express er) {
    m_p = new BinaryNode(c, el, er);
}

Express::Express(const Express& el) {
    m_p = el.m_p;
    m_p->setUse(m_p->getUse() + 1);
}

Express& Express::operator=(const Express& el) {
    (el.m_p)->setUse((el.m_p)->getUse() + 1);
    m_p->setUse(m_p->getUse() - 1);
    if (m_p->getUse() == 0) {
        delete m_p;
    }
    m_p = el.m_p;
    return *this;
}

Express::~Express() {
    m_p->setUse(m_p->getUse() - 1);
    if (m_p->getUse() == 0) {
        delete m_p;
    }
}

int Express::eval() const {
    return m_p->eval();
}
