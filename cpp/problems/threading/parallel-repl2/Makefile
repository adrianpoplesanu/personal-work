all:
	g++ -g -std=c++17 runner.cpp -c -o runner.o
	g++ -g -std=c++17 task.cpp -c -o task.o
	g++ -g -std=c++17 main.cpp -c -o main.o
	g++ -g -std=c++17 main.o -o main
%:
	g++ -pthread -std=c++11 -o $* $*.cpp
clean:
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
