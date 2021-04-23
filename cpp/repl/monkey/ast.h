#ifndef __AST_H
#define __AST_H

#include <iostream>
namespace ast {

    class Node {
    public:
        virtual void ToString() {
            std::cout << "ToString from Node\n";
        }
    };

    class Statement : virtual public Node {
    public:
        virtual void ToString() {
            std::cout << "ToString from Statement\n";
        }
    };

    class LetStatement : virtual public Statement {
    public:
        virtual void ToString() {
            std::cout << "ToString from LetStatement\n";
        }
    };

    /*class ReturnStatement : virtual public Node, virtual public Statement {

    };*/

    class ReturnStatement : virtual public Statement {

    };

    class Program : virtual public Node {
        //...
    };

    class Identifier {
        //...
    };

    class IntegerLiteral {
        //...
    };

}
#endif