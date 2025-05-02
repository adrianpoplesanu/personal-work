from instructions import Instructions
from objects import AdClosureObject, AdCompiledInstance


class Frame:
    def __init__(self, cl: AdClosureObject, ip: int, base_pointer: int = 0, bound_instance: AdCompiledInstance = None):
        self.cl = cl
        self.ip = ip
        self.base_pointer = base_pointer
        self.bound_instance = bound_instance

    def instructions(self) -> Instructions:
        return self.cl.fn.instructions


def new_frame(cl: AdClosureObject, base_pointer: int) -> Frame:
    return Frame(cl, -1, base_pointer)
