import sys
from repl import Repl


if __name__ == '__main__':
    if len(sys.argv) > 1:
        r = Repl(sys.argv[1])
        r.loop()
    else:
        print 'welcome to mokey'
        r = Repl()
        r.loop()
