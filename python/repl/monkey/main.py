import sys
from repl import Repl

if __name__ == '__main__':
    print 'welcome to mokey'
    if len(sys.argv) > 1:
        r = Repl(sys.argv[1])
        r.loop()
    else:
        r = Repl()
        r.loop()
