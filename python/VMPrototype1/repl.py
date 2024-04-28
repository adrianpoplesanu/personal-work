class Repl:
    def __init__(self, parser=None, program=None, evaluator=None, compiler=None, vm=None):
        self.parser = parser
        self.program = program
        self.evaluator = evaluator
        self.compiler = compiler
        self.vm = vm

    def execute_file(self, source):
        self.parser.load(source)
        self.program.reset()
        self.parser.build_program_statements(self.program)
        print(str(self.program))

        self.compiler.reset()
        self.compiler.compile(self.program)
        bytecode = self.compiler.get_bytecode()
        self.compiler.code.instructions = bytecode.instructions
        print(self.compiler.code.to_string(), end='')

        self.vm.load(bytecode)
        self.vm.run()
        result = self.vm.last_popped_stack_elem()
        if result:
            print(result.inspect())

    def loop(self):
        while True:
            line = input(">> ")
            if line == "exit()":
                break
            if line == "stack()":
                self.vm.print_stack()
                continue
            self.parser.load(line)
            self.program.reset()
            self.parser.build_program_statements(self.program)
            print(str(self.program))

            self.compiler.reset()
            self.compiler.compile(self.program)
            bytecode = self.compiler.get_bytecode()
            self.compiler.code.instructions = bytecode.instructions
            print(self.compiler.code.to_string(), end='')

            self.vm.load(bytecode)
            self.vm.run()
            result = self.vm.last_popped_stack_elem()
            if result:
                print(result.inspect())
