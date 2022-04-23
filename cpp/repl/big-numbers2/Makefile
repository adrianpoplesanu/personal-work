all:
	g++ -g -std=c++17 token.cpp -c -o token.o
	g++ -g -std=c++17 ast.cpp -c -o ast.o
	g++ -g -std=c++17 lexer.cpp -c -o lexer.o
	g++ -g -std=c++17 parser.cpp -c -o parser.o
	g++ -g -std=c++17 repl.cpp -c -o repl.o
	g++ -g -std=c++17 objects.cpp -c -o objects.o
	g++ -g -std=c++17 environment.cpp -c -o environment.o
	g++ -g -std=c++17 bn.cpp -c -o bn.o
	g++ -g -std=c++17 bn.o -o bn

clean:
	find . -type f ! -name "*.h" ! -name "*.cpp" ! -name "README.md" ! -name "Makefile" ! -name "*.*" -delete
	find . -name "*.o" -delete

clean-win:
	del token.o lexer.o ast.o parser.o objects.o evaluator.o repl.o main.o main.exe
