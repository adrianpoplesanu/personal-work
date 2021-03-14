#include <iostream>

#include "test.h"
#include "token.h"
#include "token.cpp"
#include "lexer.h"
#include "lexer.cpp"

using namespace std;

Test::Test() {
    id = 0;
}

Test::Test(int id) {
    this->id = id;
}

Test::~Test() {

}

int Test::GetTestID() {
    return id;
}

void Test::RunTokenTypeTest() {
    cout << "runnint test id: " << id << "\n";
    Token t(ILLEGAL);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(IDENT);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(INT);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(ASSIGN);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(PLUS);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(MINUS);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(SLASH);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(ASTERICKS);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(BANG);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(LET);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(RETURN);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(WHILE);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(LPAREN);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(RPAREN);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(LBRACE);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(RBRACE);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(COLON);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(SEMICOLON);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(LT);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(GT);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(EQ);
    cout << t.GetTokenType() << "\n";
    t.SetTokenType(NOT_EQ);
    cout << t.GetTokenType() << "\n";
}

void Test::RunLexerTest() {
    string s = "let a = 5;";
    Lexer l;
    l.Load(s);
    while(l.NextToken() != 0) {
        cout << l.NextToken();
        l.ReadChar();
    }
    cout << '\n';
}