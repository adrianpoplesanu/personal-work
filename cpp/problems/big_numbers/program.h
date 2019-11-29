#ifndef __PROGRAM_H
#define __PROGRAM_H

#include <map>
#include "interpreter.h"
#include "big_number.h"

class Program {
private:
    map<string, BigNumber> variables;
public:
    Program();
    void Init();
    string ReadCommand();
    void Loop();
};

#endif
