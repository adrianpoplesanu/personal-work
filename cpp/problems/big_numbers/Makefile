#%:
#	g++ -o $* $*.cpp
all:
	g++ big_number.cpp -c -o big_number.o
	g++ main.cpp -c -o main.o
	g++ main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "README.md" ! -name "Makefile" -delete
