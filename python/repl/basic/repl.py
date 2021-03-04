import signal
import sys

def signal_ctrl_c_handler(sig, frame):
    print "\nleving repl, bye bye!"
    sys.exit(0)


class Repl(object):
    def __init__(self, interpreter=None, program=None):
        self.interpreter = interpreter
        self.program = program

    def loop(self):
        # register a handler for SIGINT = signal interrupt(ctrl + c)
        signal.signal(signal.SIGINT, signal_ctrl_c_handler)
        print "welcome to the repl"
        while True:
            line = raw_input('>> ')
            self.interpreter.execute(line, self.program)

    def execute_file(self, source):
        pass
