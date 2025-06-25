#include "Express.h"
#include "ValueNode.h"
#include "UnaryNode.h"
#include "BinaryNode.h"

// ValueNode, eg: Express(3)
Express::Express(int value) {
    m_pEn = new ValueNode(value);
}

// UnaryNode(char, int); eg: Express('-', 4);
Express::Express(char op, const Express e) {
    m_pEn = new UnaryNode(op, e);
}

// BinaryNode(char, int, int); eg: Express('+', 3, 4);
Express::Express(char op, const Express el, const Express er) {
    m_pEn = new BinaryNode(op, el, er);
}

Express::Express(const Express& el) {
    m_pEn = el.m_pEn;
    m_pEn->setRefCnt(m_pEn->getRefCnt() + 1);
}

// el = er;
Express& Express::operator=(const Express& er) {
    (er.m_pEn)->setRefCnt((er.m_pEn)->getRefCnt() + 1); // 右边引用计数+1
    m_pEn->setRefCnt(m_pEn->getRefCnt() - 1); // 左边引用计数-1
    if (m_pEn->getRefCnt() == 0) { // 左边的引用计数 == 0
        delete m_pEn;
    }
    m_pEn = er.m_pEn;
    return *this;
}

Express::~Express() {
    m_pEn->setRefCnt(m_pEn->getRefCnt() - 1);
    if (m_pEn->getRefCnt() == 0) {
        delete m_pEn;
    }
}

int Express::eval() const {
    return m_pEn->eval();
}
