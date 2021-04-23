#include <iostream>

#include "test.h"
#include "token.h"
#include "token.cpp"
#include "lexer.h"
#include "lexer.cpp"
#include "ast.h"
#include "ast.cpp"

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

void Test::RunAllTests() {
    //RunTokenTypeTest();
    RunLexerTest();
    //RunToStringTest();
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
    t.SetTokenType(END);
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
    string s = "let test = 5; let a=7; if ert;;  let     g       =       67      ;";
    Lexer l;
    l.Load(s);
    Token current_token = l.NextToken();
    while(current_token.token_type != END) {
        cout << current_token.ToString() << "\n";
        current_token = l.NextToken();
    }
    //cout << '\n';
}

void TestToString(ast::Statement &stmt) { // yaaay!!! merge cu referinta, that's how we go about it
    stmt.ToString();
}

void TestToString2(ast::Statement *stmt) { // nu-mi place ca trebuie sa fie un pointer aici
    stmt->ToString();
}

void Test::RunToStringTest() {
    ast::LetStatement *stmt = new ast::LetStatement();
    stmt->ToString();
    ast::LetStatement s;
    s.ToString();
    TestToString(s);
    TestToString2(stmt);
    delete stmt;
}

void Test::RunToStringSimpleTest() {
    ast::LetStatement s;
    s.ToString();
}