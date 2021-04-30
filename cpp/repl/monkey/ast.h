#ifndef __AST_H
#define __AST_H

#include <iostream>
namespace ast {

    class Node {
    public:
        virtual void ToString() {
            std::cout << "ToString from Node\n";
        }
        virtual std::string str() {
            return "node";
        }
    };

    class Statement : virtual public Node {
    public:
        virtual void ToString() {
            std::cout << "ToString from Statement\n";
        }
        virtual std::string str() {
            return "statement";
        }
    };

    class LetStatement : virtual public Statement {
    public:
        virtual void ToString() {
            std::cout << "ToString from LetStatement\n";
        }
        virtual std::string str() {
            return "let statement";
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