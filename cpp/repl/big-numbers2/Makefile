all:
	g++ -g -std=c++17 parser.cpp -c -o parser.o
	g++ -g -std=c++17 repl.cpp -c -o repl.o
	g++ -g -std=c++17 bn.cpp -c -o bn.o
	g++ -g -std=c++17 bn.o -o bn

clean:
	find . -type f ! -name "*.h" ! -name "*.cpp" ! -name "README.md" ! -name "Makefile" ! -name "*.*" -delete
	find . -name "*.o" -delete

clean-win:
	del token.o lexer.o ast.o parser.o objects.o evaluator.o repl.o main.o main.exe
