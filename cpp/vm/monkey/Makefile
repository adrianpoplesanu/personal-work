all:
	g++ -g -std=c++17 token.cpp -c -o token.o
	g++ -g -std=c++17 ast.cpp -c -o ast.o
	g++ -g -std=c++17 lexer.cpp -c -o lexer.o
	g++ -g -std=c++17 parser.cpp -c -o parser.o
	g++ -g -std=c++17 program.cpp -c -o program.o
	g++ -g -std=c++17 objects.cpp -c -o objects.o
	g++ -g -std=c++17 evaluator.cpp -c -o evaluator.o
	g++ -g -std=c++17 code.cpp -c -o code.o
	g++ -g -std=c++17 compiler.cpp -c -o compiler.o
	g++ -g -std=c++17 vm.cpp -c -o vm.o
	g++ -g -std=c++17 main.cpp -c -o main.o
	g++ -g -std=c++17 main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "*.bn" ! -name "README.md" ! -name "expresii_regulate.txt" ! -name "Makefile" -delete
test:
	echo "Not implemented"
test2:
	echo "Not implemented"
clean-win:
	del program.o main.o main.exe
