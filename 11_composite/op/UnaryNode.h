#pragma once

#include "Express.h"
#include "ExpressNode.h"

class UnaryNode : public ExpressNode {
public:
    friend class Express;
    //UnaryNode();
    UnaryNode(char c, class Express left);
    ~UnaryNode();
private:
    void print(ostream &out) const;
    int eval() const;
    char m_op;
    class Express m_left;
};
