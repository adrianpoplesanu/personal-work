all:
	g++ objects.cpp -c -o objects.o
	g++ listobject.cpp -c -o listobject.o
	g++ main.cpp -c -o main.o
	g++ main.o -o main
clean:
	find . -type f  ! -name "*.h" ! -name "*.cpp" ! -name "*.bn" ! -name "README.md" ! -name "*.*" ! -name "Makefile" -delete
	find . -type f -name "*.o" -delete
test:
	echo "Not implemented"
test2:
	echo "Not implemented"
clean-win:
	del program.o main.o main.exe
