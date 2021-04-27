#include <iostream>
#include <vector>
#include "objects.h"
#include "listobject.h"
/*#include "listobject.h"
#include "listobject.cpp"

void test() {
    ListObject<int> numbers;
    std::cout << numbers.getSize() << "\n";
    numbers.append(7);
    numbers.append(4);
    numbers.append(7);
    numbers.print();
    std::cout << numbers.getSize() << "\n";
    numbers.print_memory_addresses();
    numbers.append(6);
    numbers.append(8);
    int a = numbers.pop();
    std::cout << a << "\n";
    numbers.print();
    std::cout << numbers.getSize() << "\n";
    numbers.print_memory_addresses();
}

int main(int argc, char *argv[]) {
    std::cout << "buna dimineata!\n";
    test();
    test();
    return 0;
}*/

void add_elements(std::vector<GenericObject*> &objects) {
    StringObject a;
    IntObject b;
    a.data = "Tester123";
    a.type = OBJ_TYPE_STRING;
    b.data = 47;
    b.type = OBJ_TYPE_INT;
    objects.push_back(&a); // asta o sa faca segmentation fault pentru ca adresa variabilei a e curatata cand apelul functiei se termina
    objects.push_back(&b);
}

void print_elements(std::vector<GenericObject*> objects, int n) {
    for (int i = 0; i < n; i++) objects[i]->ToString();
}

int main(int argc, char *argv[]) {
    std::vector<GenericObject*> objects;
    StringObject a;
    IntObject b;
    a.data = "test";
    a.type = OBJ_TYPE_STRING;
    b.data = 5;
    b.type = OBJ_TYPE_INT;
    objects.push_back(&a);
    objects.push_back(&b);
    for (int i = 0; i < 2; i++) objects[i]->ToString();
    /*add_elements(objects);
    print_elements(objects, 2);*/

    ListObject lo;
    StringObject *o1 = new StringObject();
    o1->data = "test";
    o1->type = OBJ_TYPE_STRING;
    IntObject *o2 = new IntObject();
    o2->data = 5;
    o2->type = OBJ_TYPE_INT;
    std::cout << lo.size << '\n';

    lo.insert(o1, 0);
    //lo.print(2);

    lo.insert(o2, 1);
    lo.print(2);
    /*lo.insert(a, 0);
    lo.print(2);*/
    //a.ToString();
    //b.ToString();

    return 0;
}