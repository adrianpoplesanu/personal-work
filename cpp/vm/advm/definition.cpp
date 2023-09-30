#include "definition.h"

Definition::Definition(std::string n, int *ow) {
    name = n;
    operandWidths = ow;
}

Definition::~Definition() {
    delete[] operandWidths;
}