from ast import Program
from parser import Parser
from lexer import Lexer


if __name__ == '__main__':
    input = '''
    let a = 5;
    let b = 6;
    let foobar = 7474;
    '''

    lexer = Lexer()
    lexer.New(input)
    print lexer.input
    parser = Parser()
    print parser
    parser.new(lexer)
    program = Program()
    parser.ParseProgram(program)
    print program
    program.String()
    print 'tests have run...'

    input = '''
    return 5;
    return 10;
    return 993322;
    '''

    #lexer = Lexer()
    lexer.New(input)
    print lexer.input
    #parser = Parser()
    print parser
    parser.new(lexer)
    program.reset()
    parser.ParseProgram(program)
    print program
    program.String()
    print 'tests have run'
