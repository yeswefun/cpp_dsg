#include "ExpressNode.h"


int ExpressNode::getRefCnt() const {
    return m_refCnt;
}

void ExpressNode::setRefCnt(int refCnt) {
    m_refCnt = refCnt;
}

ExpressNode::~ExpressNode() {

}
