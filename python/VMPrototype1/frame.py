from instructions import Instructions
from objects import AdCompiledFunction


class Frame:
    def __init__(self, fn: AdCompiledFunction, ip: int, base_pointer: int = 0):
        self.fn = fn
        self.ip = ip
        self.base_pointer = base_pointer

    def instructions(self) -> Instructions:
        return self.fn.instructions


def new_frame(fn: AdCompiledFunction, base_pointer: int) -> Frame:
    return Frame(fn, -1, base_pointer)
