// forward declaration does not work for inheriting or any operation that needs contextual information
// forward declaration just tells the compiler that a class with that name __will__ exist
#include <iostream>

class B;
class A : B {

};

class B {

};

int main(int argc, char* argv[]) {
    std::cout << "checking class ordering & inheritancce operator\n";
    return 0;
}
