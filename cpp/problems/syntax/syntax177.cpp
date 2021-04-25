// define and instantiate object without referencing them as pointers
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

template<typename T>
class Object {
private:
    T data;
public:
    Object(T e) {
        data = e;
    }
    void toString() {
        cout << data;
    }
};

class Object2 {
private:
    string literal;
    int type; // int, boolean, function, etc... used by evaluator
public:
    Object2(int t, string l) {
        literal = l;
        type = t;
    }

    string getLiteral() {
        return literal;
    }

    int getType() {
        return type;
    }
};

class Parser {
private:
    string source;
    vector< Object<int> > objects;
public:
    Parser(string s) {
        source = s;
    }
    void parse() {
        for (int i = 0; i < source.size(); i++) {
            cout << source[i] << "\n";
        }
    }
};

class Evaluator {
private:
    vector<Object2> objects;
public:
    Evaluator(vector<Object2> o) {
        objects = o;
    }
    void eval() {
        for (int i = 0; i < objects.size(); i++) {
            switch(objects[i].getType()) {
                case 1:
                    cout << "stringul: " << objects[i].getLiteral() << "\n";
                break;
                case 2:
                    cout << "intul: " << objects[i].getLiteral() << "\n"; // trbuie sa fac cu atoi
                break;
                case 3:
                    cout << "functia: " << objects[i].getLiteral() << "()\n";
                break;
            }
        }
    }
};

int main(int argc, char *argv[]) {
    string s = "aabbcc";
    Parser p(s);
    p.parse();

    vector<Object2> objects;
    objects.push_back(Object2(1, "maca"));
    objects.push_back(Object2(2, "2"));
    objects.push_back(Object2(3, "maca"));
    Evaluator evaluator(objects);
    evaluator.eval();
    return 0;
}
