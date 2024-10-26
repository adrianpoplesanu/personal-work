#include "compilation_scope.h"

CompilationScope::CompilationScope() {
    instructions = Instructions();
    previousInstruction = EmittedInstruction();
    lastInstruction = EmittedInstruction();
}

CompilationScope::CompilationScope(Instructions i) {
    instructions = i;
    previousInstruction = EmittedInstruction();
    lastInstruction = EmittedInstruction();
}

CompilationScope::CompilationScope(Instructions i, EmittedInstruction e1, EmittedInstruction e2) {
    instructions = i;
    previousInstruction = e1;
    lastInstruction = e2;
}