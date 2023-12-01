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
            self.parser.build_program_statements(self.program)

            self.compiler.reset()
            self.compiler.compile(self.program)
            bytecode = self.compiler.bytecode

            self.vm.load(bytecode)
            self.vm.run()
            result = self.vm.last_popped_stack_element()
            if result:
                print(result.inspect())
