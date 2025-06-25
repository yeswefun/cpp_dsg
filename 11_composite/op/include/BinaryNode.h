#pragma once

#include "Express.h"
#include "ExpressNode.h"

class BinaryNode : public ExpressNode {
public:
    friend class Express;
    BinaryNode(char, Express, Express);
    ~BinaryNode();
private:
    void print(ostream &out) const;
    int eval() const;
    char m_op;
    Express m_left;
    Express m_right;
};
