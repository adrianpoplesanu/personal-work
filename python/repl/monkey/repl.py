class Repl(object):
    def __init__(self):
        pass

    def loop(self):
        #print '>> ',
        while True:
            line = raw_input('>> ')
            print line
