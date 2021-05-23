import sys
from repl import Repl


if __name__ == '__main__':
    if len(sys.argv) > 1:
        r = Repl(sys.argv[1])
        r.loop()
    else:
        print 'welcome to mokey'
        r = Repl()
        r.test_parse_program_ast_node()
        r.loop()
