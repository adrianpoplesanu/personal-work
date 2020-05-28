%:
	g++ -o $* $*.cpp
main:
	g++ tuple.cpp -c -o tuple.o
	g++ main.cpp -o main
clean:
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
	find . -type f -name "*.o" -delete
