#ifndef __PROGRAM_H
#define __PROGRAM_H

#include "lexer.h"

class Program {
private:
    Lexer lexer;
public:
    Program();
    ~Program();
    void Run();
    void Loop();
    void ParseLine(std::string line);
};

#endif
