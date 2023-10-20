class Repl:
    def __init__(self, parser=None, program=None, evaluator=None, compiler=None, vm=None):
        self.parser = parser
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
            self.parser.load(line)
            self.program.reset()
            self.parser.build_program_statement(self.program)
