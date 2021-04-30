all:
	g++ token.cpp -c -o token.o
	g++ ast.cpp -c -o ast.o
	g++ lexer.cpp -c -o lexer.o
	g++ parser.cpp -c -o parser.o
	g++ program.cpp -c -o program.o
	g++ objects.cpp -c -o objects.o
	g++ evaluator.cpp -c -o evaluator.o
	g++ test.cpp -c -o test.o
	g++ main.cpp -c -o main.o
	g++ main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "*.bn" ! -name "README.md" ! -name "expresii_regulate.txt" ! -name "Makefile" -delete
test:
	echo "Not implemented"
test2:
	echo "Not implemented"
clean-win:
	del program.o main.o main.exe
