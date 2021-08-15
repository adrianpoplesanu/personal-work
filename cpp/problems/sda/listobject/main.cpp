#include <iostream>
#include "listobject.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
    Ad_List list;

    Ad_String_Object* obj = new Ad_String_Object();
    obj->value = "buna";

    std::cout << obj << "\n";

    list.add(0, obj);
    list.add(1, new Ad_String_Object("dimineata"));
    list.add(2, new Ad_String_Object("pe"));
    list.add(3, new Ad_String_Object("racoare"));

    list.Inspect();

    list.add(4, new Ad_String_Object("dex"));

    list.Inspect();

    return 0;
}
