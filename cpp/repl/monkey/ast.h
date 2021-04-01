#ifndef __AST_H
#define __AST_H

#include <iostream>
using namespace std;

class Node {
public:
    virtual void ToString() {
        cout << "ToString from Node\n";
    }
};

class Statement {
public:
    virtual void ToString() {
        cout << "ToString from Statement\n";
    }
};

class LetStatement : virtual public Statement {
public:
    virtual void ToString() {
        cout << "ToString from LetStatement\n";
    }
};

class ReturnStatement : virtual public Node, virtual public Statement {

};

#endif