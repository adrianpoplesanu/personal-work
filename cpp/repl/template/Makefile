all:
	g++ lexer.cpp -c -o lexer.o
	g++ parser.cpp -c -o parser.o
	g++ program.cpp -c -o program.o
	g++ main.cpp -c -o main.o
	g++ main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "*.bn" ! -name "README.md" ! -name "expresii_regulate.txt" ! -name "Makefile" -delete
test:
	echo "Not implemented"
test2:
	echo "Not implemented"
clean-win:
	del program.o main.o lexer.o parser.o main.exe
