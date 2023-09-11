#pragma once

#include "Express.h"
#include "ExpressNode.h"

class BinaryNode : public ExpressNode {
public:
    friend class Express;
    // BinaryNode();
    BinaryNode(char, class Express, class Express);
    ~BinaryNode();
private:
    void print(ostream &out) const;
    int eval() const;
    char m_op;
    class Express m_left;
    class Express m_right;
};
