#include "builtins.h"

Builtin::Builtin(std::string n, BuiltinFunction bf) {
    name = n;
    //builtin_function = bf;
    builtin_object = new AdObjectBuiltin(bf);
}

AdObject* len_builtin(std::vector<AdObject*> args, GarbageCollector* gc) {
    AdObject *obj = args.at(0);
    if (obj->type == OT_LIST) {
        AdObjectInteger *result = new AdObjectInteger(((AdObjectList *)obj)->elements.size());
        gc->addObject(result);
        return result;
    }
    return NULL;
}

AdObject* print_builtin(std::vector<AdObject*> args, GarbageCollector* gc) {
    AdObject *obj = args.at(0);
    std::cout << obj->inspect();
    return NULL;
}

AdObject* println_builtin(std::vector<AdObject*> args, GarbageCollector* gc) {
    AdObject *obj = args.at(0);
    std::cout << obj->inspect() << '\n';
    return NULL;
}

void finalize_free_all_builtin_objects() {
    for (auto &builtin : builtins) {
        free_memory_AdObject(builtin.builtin_object);
    }
}