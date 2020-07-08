all:
	g++ ast.cpp -c -o ast.o
	g++ node.cpp -c -o node.o
	g++ interpreter.cpp -c -o interpreter.o
	g++ program.cpp -c -o program.o
	g++ main.cpp -c -o main.o
	g++ main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "*.basic" ! -name "*.bn" ! -name "README.md" ! -name "expresii_regulate.txt" ! -name "Makefile" -delete
test:
	g++ big_number.cpp -c -o big_number.o
	g++ aritmetic_evaluator_test.cpp -o aritmetic_evaluator_test
test2:
	g++ big_number.cpp -c -o big_number.o
	g++ aritmetic_minus_test.cpp -o aritmetic_minus_test
clean-win:
	del big_number.o expressions.o interpreter.o main.o main.exe program.o
