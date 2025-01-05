from instructions import Instructions
from objects import AdClosureObject


class Frame:
    def __init__(self, cl: AdClosureObject, ip: int, base_pointer: int = 0):
        self.cl = cl
        self.ip = ip
        self.base_pointer = base_pointer

    def instructions(self) -> Instructions:
        return self.cl.fn.instructions


def new_frame(cl: AdClosureObject, base_pointer: int) -> Frame:
    return Frame(cl, -1, base_pointer)
