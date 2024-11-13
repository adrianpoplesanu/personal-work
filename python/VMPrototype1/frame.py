from instructions import Instructions
from objects import AdCompiledFunction


class Frame:
    def __init__(self, fn: AdCompiledFunction, ip: int):
        self.fn = fn
        self.ip = ip

    def instructions(self) -> Instructions:
        return self.fn.instructions


def new_frame(fn: AdCompiledFunction) -> Frame:
    return Frame(fn, -1)
