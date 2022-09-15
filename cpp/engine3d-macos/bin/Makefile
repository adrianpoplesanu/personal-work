all:
	g++ -g --std=c++11 -I../dependencies/include -L../dependencies/library ../src/*.cpp ../src/glad.c -lglfw3dll -o main

macos:
	g++ -std=c++11 -fcolor-diagnostics -fansi-escape-codes -Wall -g -I ../dependencies/include -L ../dependencies/library ../dependencies/library/libglfw.3.3.dylib ../src/*.cpp ../src/glad.c -o app -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated