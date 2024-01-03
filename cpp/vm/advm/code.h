#ifndef __CODE_H
#define __CODE_H

#include "opcode.h"
#include "definition.h"
#include "instructions.h"
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

class Code {
public:
    Instructions instructions;
    std::map<unsigned char, Definition*> definitionsMap;

    Code();
    ~Code();
    unsigned char* make(OpCode opCode, int n, std::vector<int>&, int&);
    Definition* lookup(unsigned char);
    std::string toString();
};

std::vector<unsigned char> intToBytes(int);
void readOperands(Definition*, Instructions, int, std::vector<int>&, int&);
int readUint16(Instructions, int);
std::string formatInt(int);
std::string formatInstruction(Definition*, std::vector<int>);

#endif