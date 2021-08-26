#include <iostream>
#include "listobject.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
    Ad_List list;

    Ad_String_Object* obj = new Ad_String_Object();
    obj->value = "buna";

    list.Add(0, obj);
    list.Add(1, new Ad_String_Object("dimineata"));
    list.Add(2, new Ad_String_Object("pe"));
    list.Add(3, new Ad_String_Object("racoare"));

    list.Inspect();

    list.Add(4, new Ad_String_Object("dex"));

    list.Inspect();

    Ad_List test;
    test.Add(0, obj);
    test.Add(1, obj);
    test.Add(2, obj);
    test.Add(3, obj);
    test.Add(4, obj);

    std::cout << test.Size() << " " << list.Capacity() << "\n"; 

    std::cout << test.Remove(4) << "\n";

    std::cout << test.Size() << " " << test.Capacity() << "\n";

    std::cout << test.Remove(3) << "\n";

    std::cout << test.Size() << " " << test.Capacity() << "\n";

    test.Append(obj);

    std::cout << test.Size() << " " << test.Capacity() << "\n";

    test.Append(obj);

    std::cout << test.Size() << " " << test.Capacity() << "\n";

    return 0;
}
