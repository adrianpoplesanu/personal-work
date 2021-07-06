#include <iostream>
#include <vector>
#include <map>

class GenericObject;

class FunctionObject {
public:
    std::string name;
    std::vector<GenericObject> arguments;
};

class GenericObject {
public:
    int type;
    int int_val;
    bool bool_val;
    std::string string_val;
    FunctionObject function_val;
    std::vector<GenericObject> list_val;
    std::map<GenericObject, GenericObject> dict_val;
};

int main(int argc, char *argv[]) {
    GenericObject go;
    return 0;
}
