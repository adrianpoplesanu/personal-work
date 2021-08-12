#include <iostream>
#include "listobject.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
    Ad_List list;

    Ad_String_Object* obj = new Ad_String_Object();
    obj->value = "buna";

    std::cout << obj << "\n";

    list.add(obj);
    list.add(new Ad_String_Object("dimineata"));
    list.add(new Ad_String_Object("pe"));
    list.add(new Ad_String_Object("racoare"));

    list.Inspect();

    list.add(new Ad_String_Object("dex"));

    list.Inspect();

    return 0;
}
