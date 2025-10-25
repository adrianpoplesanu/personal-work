all:
	gcc main.c -c -o main.o
	gcc main.o -o main

clean:
	find . -type f ! -name "*.h" ! -name "*.cpp" ! -name "*.c" ! -name "README.md" ! -name "Makefile" ! -name "*.*" -delete
	find . -name "*.o" -delete

clean-win:
	del token.o lexer.o ast.o parser.o objects.o evaluator.o repl.o main.o main.exe
