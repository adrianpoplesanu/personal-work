#include <iostream>
#include <vector>

class Token {
public:
    Token(int t, std::string v) {
        type = t;
        value = v;
    }

    int type;
    std::string value;
};

class Parser {
std::vector<Token> tokens;
public:
    void addToken(Token token) {
        tokens.push_back(token);
    }

    void parse(bool (*predicate)(const int&)) const {
	for (auto t : tokens) {
            if (predicate(t.type)) {
                std::cout << t.value << "\n";
            }
        }
    }
};


int main(int argc, char *argv[]) {
    Token a(0, "aaa");
    Token b(1, "bbb");
    Token c(2, "ccc");

    Parser parser;

    parser.addToken(a);
    parser.addToken(b);
    parser.addToken(c);

    parser.parse([](const int& x) -> bool { return x == 1; });

    return 0;
}
