#include "compilation_scope.h"

CompilationScope::CompilationScope() {
    instructions = Instructions();
    previousInstruction = EmittedInstruction();
    lastInstruction = EmittedInstruction();
}