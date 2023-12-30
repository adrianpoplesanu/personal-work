from instructions import Instructions


class Bytecode:
    def __init__(self):
        self.instructions = Instructions()
        # List<Ad_Object>
        self.constants = []
