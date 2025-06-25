#pragma once

#include <iostream>
#include "ExpressNode.h"

using namespace std;

class Express {
public:
    ~Express();
    Express(int); // ValueNode, eg: Express(3)
    Express(char, const Express); // UnaryNode(char, int); eg: Express('+', t, 12);
    Express(char, const Express, const Express); // BinaryNode(char, int, int); eg: ('+', 3, 4);
    Express(const Express&);
    Express& operator=(const Express&);

    // Express t = Express(3);
    // cout << t << endl;
    friend ostream& operator<<(ostream &out, const Express &e) {
        out << *(e.m_pEn);
        return out;
    }

    int eval() const;

private:
    //各种表达式
    ExpressNode *m_pEn;
};