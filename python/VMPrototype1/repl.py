class Repl:
    def __init__(self, parser=None, program=None, evaluator=None, compiler=None, vm=None):
        self.parse = parser
        self.program = program
        self.evaluator = evaluator
        self.compiler = compiler
        self.vm = vm

    def execute_file(self, source):
        pass

    def loop(self):
        while True:
            line = input(">> ")
            if line == "exit()":
                break
