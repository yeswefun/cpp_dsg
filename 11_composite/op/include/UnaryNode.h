#pragma once

#include "Express.h"
#include "ExpressNode.h"

class UnaryNode : public ExpressNode {
public:
    friend class Express;
    UnaryNode(char c, Express right);
    ~UnaryNode();
private:
    void print(ostream &out) const;
    int eval() const;
    char m_op;
    // -1
    Express m_right;
};
