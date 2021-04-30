#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

std::vector<ast::Node> Parser::BuildStatements_old() {
    //...
    // TODO: this is void for now, but it definately needs to return an AST node
    // ASTA NU MERGE IN FORMA ASTA pentru ca nu face polimorfismul obiectelor
    std::vector<ast::Node> statements;
    ast::Statement a;
    ast::LetStatement b;
    statements.push_back(a);
    statements.push_back(b);
    for (std::vector<ast::Node>::iterator it = statements.begin(); it != statements.end(); ++it) {
        //std::cout << (*it).ToString() << '\n';
        (*it).ToString();
    }
    return statements;
}

std::vector<ast::Node*> Parser::BuildStatements() {
    //...
    // TODO: this is void for now, but it definately needs to return an AST node
    // ASTA MERGE pentru ca face polimorfismul print adresa de memorie, ceea ce e confirmat si in array_list4
    // PROBLEMA aici e ca a si b stau pe stiva la cum sunt declarate si sunt dezalocate la finalul acestul apel
    std::vector<ast::Node*> statements;
    ast::Statement a;
    ast::LetStatement b;
    statements.push_back(&a);
    statements.push_back(&b);
    for (std::vector<ast::Node*>::iterator it = statements.begin(); it != statements.end(); ++it) {
        //std::cout << (*it).ToString() << '\n';
        (*it)->ToString();
    }
    return statements;
}