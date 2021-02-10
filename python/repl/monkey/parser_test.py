from parser import Parser
from lexer import Lexer


if __name__ == '__main__':
    input = '''let a = 5;
    let b = 6;
    let foobar = 7474;
    '''

    lexer = Lexer()
    lexer.New(input)
    parser = Parser()
    parser.new(lexer)
    program = parser.ParseProgram()
    program.String()
    print 'tests have run...'
