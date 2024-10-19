from typing import Optional

from emitted_instruction import EmittedInstruction
from instructions import Instructions


class CompilationScope:
    def __init__(self, instructions: Instructions = None,
                 last_instruction: EmittedInstruction = None,
                 previous_instruction: EmittedInstruction = None):
        self.instructions = instructions
        self.last_instruction: Optional[EmittedInstruction] = last_instruction
        self.previous_instruction: Optional[EmittedInstruction] = previous_instruction
