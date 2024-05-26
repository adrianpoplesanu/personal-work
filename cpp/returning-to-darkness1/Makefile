all:
	clang++ main.cpp ./glad/src/glad.c -I/Library/Frameworks/SDL2.framework/Headers -I./glad/include -F/Library/Frameworks -framework SDL2 -o main

clean:
	find . -type f ! -name "*.h" ! -name "*.cpp" ! -name "README.md" ! -name "Makefile" ! -name "*.*" -delete
	find . -name "*.o" -delete
