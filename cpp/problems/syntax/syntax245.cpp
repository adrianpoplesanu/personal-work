// testing memory leak runnage
// MACOS:
// run: leaks -atExit -- ./syntax245
// LINUX:
// run: valgrind --tool=memcheck --leak-check=full ./main

#include <iostream>

class Entity {

};

int main(int argc, char* argv[]) {
    Entity *e = new Entity();
    delete e;
    return 0;
} 
