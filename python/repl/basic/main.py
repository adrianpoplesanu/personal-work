class Repl(object):
    def __init__(self, interpreter=None):
        self.interpreter = interpreter

    def loop(self):
        while True:
            line = raw_input('>> ')
            print line

if __name__ == '__main__':
    repl = Repl(interpreter=None)
    repl.loop()
