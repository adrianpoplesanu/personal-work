#ifndef __REPL_H
#define __REPL_H

#include <iostream>
#include "parser.h"

class Repl {
private:
    bool ParseLine(std::string);
    Parser parser;
public:

    Repl();
    ~Repl();
    void Loop();
    void ExecuteFile(std::ifstream&);
};

#endif
