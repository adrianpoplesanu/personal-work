#include "objects.h"
#include <sstream>

std::string AdObject::inspect() {
    return "unimplemented in subclass";
}

std::string AdObject::toString() {
    return "unimplemented in subclass";
}

std::string AdObject::hash() {
    return "todo: implement this";
}

AdObject *AdObject::copy() {
    return NULL;
}

AdObjectInteger::AdObjectInteger() {
    type = OT_INT;
}

AdObjectInteger::AdObjectInteger(int v) {
    type = OT_INT;
    value = v;
}

std::string AdObjectInteger::inspect() {
    std::string out = "";
    out = std::to_string(value);
    return out;
}

std::string AdObjectInteger::toString() {
    return "todo";
}

std::string AdObjectInteger::hash() {
    return object_type_map[type] + inspect();
}

AdObject *AdObjectInteger::copy() {
    return nullptr;
}

AdObjectBoolean::AdObjectBoolean() {
    type = OT_BOOL;
}

AdObjectBoolean::AdObjectBoolean(bool v) {
    type = OT_BOOL;
    value = v;
}

AdObjectBoolean::AdObjectBoolean(bool v, bool p) {
    type = OT_BOOL;
    value = v;
    permanent = p;
}

std::string AdObjectBoolean::inspect() {
    if (value) {
        return "true";
    }
    return "false";
}

std::string AdObjectBoolean::toString() {
    return "todo";
}

std::string AdObjectBoolean::hash() {
    return "todo: implement this";
}

AdObject *AdObjectBoolean::copy() {
    return nullptr;
}

AdObjectNull::AdObjectNull() {
    //std::cout << "allocating a null object\n";
    type = OT_NULL;
}

AdObjectNull::~AdObjectNull() {
    //std::cout << "freeing a null object\n";
}

std::string AdObjectNull::inspect() {
    return "null";
}

std::string AdObjectNull::toString() {
    return "todo";
}

std::string AdObjectNull::hash() {
    return "todo: implement this";
}

AdObject *AdObjectNull::copy() {
    return nullptr;
}

AdObjectString::AdObjectString() {
    type = OT_STRING;
}

AdObjectString::AdObjectString(std::string v) {
    type = OT_STRING;
    value = v;
}

std::string AdObjectString::inspect() {
    return "'" + value + "'";
}

std::string AdObjectString::toString() {
    return "AdObjectString.toString()";
}

std::string AdObjectString::hash() {
    return object_type_map[type] + inspect();
}

AdObject *AdObjectString::copy() {
    return nullptr;
}

AdObjectList::AdObjectList() {
    type = OT_LIST;
}

AdObjectList::AdObjectList(std::vector<AdObject*> e) {
    type = OT_LIST;
    elements = e;
}

AdObjectList::~AdObjectList() {
    //...
}

std::string AdObjectList::inspect() {
    std::string out = "[";
    int size = elements.size();
    int i = 0;
    for (auto& it : elements) {
        out += it->inspect();
        if (++i < size) out += ", ";
    }
    out += "]";
    return out;
}

std::string AdObjectList::toString() {
    return "TODO: implement this";
}

std::string AdObjectList::hash() {
    return "TODO: implement this";
}

AdObject* AdObjectList::copy() {
    return nullptr;
}

AdObjectHash::AdObjectHash() {
    type = OT_HASH;
    ref_count = 0;
    marked = false;
}

AdObjectHash::AdObjectHash(std::unordered_map<std::string, HashPair> p) {
    type = OT_HASH;
    ref_count = 0;
    marked = false;
    pairs = p;
}

AdObjectHash::~AdObjectHash() {
    //...
}

std::string AdObjectHash::inspect() {
    std::string out = "{";
    bool displayed_first = false;
    for(std::unordered_map<std::string, HashPair>::iterator it = pairs.begin(); it != pairs.end(); it++) {
        if (displayed_first) out += ", ";
        else displayed_first = true;
        out += it->second.key->inspect() + ": " + it->second.value->inspect();
    }
    out += "}";
    return out;
}

std::string AdObjectHash::toString() {
    return "todo: implement Print() in Ad_Hash_Object\n";
}

std::string AdObjectHash::hash() {
    return "TODO: implement AdObjectHash.hash()";
}

AdObject* AdObjectHash::copy() {
    return nullptr;
}

AdObjectCompiledFunction::AdObjectCompiledFunction() {
    type = OT_COMPILED_FUNCTION;
    num_locals = 0;
    num_parameters = 0;
}

AdObjectCompiledFunction::AdObjectCompiledFunction(Instructions i) {
    type = OT_COMPILED_FUNCTION;
    instructions = i;
    num_locals = 0;
    num_parameters = 0;
}

AdObjectCompiledFunction::AdObjectCompiledFunction(Instructions i, int n_l) {
    type = OT_COMPILED_FUNCTION;
    instructions = i;
    num_locals = n_l;
    num_parameters = 0;
}

AdObjectCompiledFunction::AdObjectCompiledFunction(Instructions i, int n_l, int n_p) {
    type = OT_COMPILED_FUNCTION;
    instructions = i;
    num_locals = n_l;
    num_parameters = n_p;
}

AdObjectCompiledFunction::~AdObjectCompiledFunction() {
    //...
}

std::string AdObjectCompiledFunction::inspect() {
    return "TODO: implement AdObjectCompiledFunction.inspect()";
}

std::string AdObjectCompiledFunction::toString() {
    return "TODO: implement AdObjectCompiledFunction.toString()";
}

std::string AdObjectCompiledFunction::hash() {
    return "TODO: implement AdObjectCompiledFunction.hash()";
}

AdObject* AdObjectCompiledFunction::copy() {
    return nullptr;
}

AdObjectBuiltin::AdObjectBuiltin() {
    type = OT_BUILTIN;
}

AdObjectBuiltin::AdObjectBuiltin(BuiltinFunction bf) {
    type = OT_BUILTIN;
    builtin_function = bf;
}

AdObjectBuiltin::~AdObjectBuiltin() {
    //...
}

AdClosureObject::AdClosureObject() {
    type = OT_CLOSURE;
    fn = nullptr;
}

AdClosureObject::AdClosureObject(AdObjectCompiledFunction *f) {
    type = OT_CLOSURE;
    fn = f;
}

AdClosureObject::AdClosureObject(AdObjectCompiledFunction *f, std::vector<AdObject*> fr) {
    type = OT_CLOSURE;
    fn = f;
    free = fr;
}

AdClosureObject::~AdClosureObject() {
    //...
}

std::string AdClosureObject::inspect() {
    return "TODO: implement AdClosureObject.inspect()";
}

std::string AdClosureObject::toString() {
    return "TODO: implement AdClosureObject.toString()";
}

std::string AdClosureObject::hash() {
    return "TODO: implement AdClosureObject.hash()";
}

AdObject* AdClosureObject::copy() {
    return nullptr;
}

AdCompiledClass::AdCompiledClass() {
    type = OT_COMPILED_CLASS;
    ref_count = 0;
    marked = false;
    attemptASTNodesDeletion = false;
}

AdCompiledClass::AdCompiledClass(std::vector<ASTNode*> m, std::vector<ASTNode*> a) {
    type = OT_COMPILED_CLASS;
    ref_count = 0;
    marked = false;
    attemptASTNodesDeletion = false;
    methods = m;
    for (std::vector<ASTNode*>::iterator it = methods.begin() ; it != methods.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
    attributes = a;
    for (std::vector<ASTNode*>::iterator it = attributes.begin() ; it != attributes.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
}

AdCompiledClass::AdCompiledClass(ASTNode* n, std::vector<ASTNode*> m, std::vector<ASTNode*> a) {
    type = OT_COMPILED_CLASS;
    ref_count = 0;
    marked = false;
    attemptASTNodesDeletion = false;
    name = n;
    Ad_INCREF(name);
    methods = m;
    for (std::vector<ASTNode*>::iterator it = methods.begin(); it != methods.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
    attributes = a;
    for (std::vector<ASTNode*>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
}

AdCompiledClass::AdCompiledClass(ASTNode* n, std::vector<ASTNode*> m, std::vector<ASTNode*>a, ASTNode* c) {
    type = OT_COMPILED_CLASS;
    ref_count = 0;
    marked = false;
    attemptASTNodesDeletion = false;
    class_ast_node = c;
    Ad_INCREF(class_ast_node);

    name = n;
    Ad_INCREF(name);
    methods = m;
    for (std::vector<ASTNode*>::iterator it = methods.begin(); it != methods.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
    attributes = a;
    for (std::vector<ASTNode*>::iterator it = attributes.begin(); it != attributes.end(); ++it) {
        ASTNode *node = *it;
        Ad_INCREF(node);
    }
}

AdCompiledClass::AdCompiledClass(ASTNode* n, SymbolTable* st) {
    type = OT_COMPILED_CLASS;
    ref_count = 0;
    marked = false;
    attemptASTNodesDeletion = false;

    name = n;
    outerSymbolTable = st;
}

AdCompiledClass::~AdCompiledClass() {
    //std::cout << "deleting class" << ((Ad_AST_Identifier*)name)->value << "\n";
    //std::cout << is_console_run << "\n";
    //attemptASTNodesDeletion = true;
    Ad_DECREF(class_ast_node);
    if (attemptASTNodesDeletion) {
        free_memory_ASTNode(class_ast_node);
    }

    // if i deallocate the ast node that references all the methods and attributes ast, do i really need to try and manually free them again?
    for (std::vector<ASTNode*>::iterator it = methods.begin() ; it != methods.end(); ++it) {
        ASTNode *node = *it;
        Ad_DECREF(node); // asta merge si e super cool
        if (attemptASTNodesDeletion) {
            free_memory_ASTNode(node);
        }
    }
    for (std::vector<ASTNode*>::iterator it = attributes.begin() ; it != attributes.end(); ++it) {
        ASTNode *node = *it;
        Ad_DECREF(node); // asta merge si e super cool
        if (attemptASTNodesDeletion) {
            free_memory_ASTNode(node);
        }
    }
}

std::string AdCompiledClass::inspect() {
    std::stringstream ss;
    ss << std::hex << this;
    return "<class object at memory address: " + ss.str() + ">";
}

std::string AdCompiledClass::toString() {
    return "ClassObject";
    //std::cout << methods.size();
    //std::cout << attributes.size();
}

AdObject* AdCompiledClass::copy() {
    AdCompiledClass *obj = new AdCompiledClass();
    obj->attributes = attributes;
    obj->methods = methods;
    // TODO: copy all fields of an AdCompiledClass
    return obj;
}

std::string AdCompiledClass::hash() {
    return object_type_map[type] + inspect();
}

void AD_INCREF(AdObject* obj) {
    if (obj != NULL) {
        obj->ref_count++;
    }
}

void AD_DECREF(AdObject* obj) {
    if (obj != NULL) {
        obj->ref_count--;
    }
}

void free_memory_AdObject(AdObject* obj) {
    if (obj == NULL) return;
    switch(obj->type) {
        case OT_INT: {
            delete (AdObjectInteger*) obj;
            break;
        }
        case OT_BOOL: {
            if (!((AdObjectBoolean*) obj)->permanent) {
                delete (AdObjectBoolean*) obj;
            }
            break;
        }
        case OT_STRING: {
            delete (AdObjectString*) obj;
            break;
        }
        case OT_LIST: {
            delete (AdObjectList*) obj;
            break;
        }
        case OT_HASH: {
            delete (AdObjectHash*) obj;
            break;
        }
        case OT_COMPILED_FUNCTION: {
            delete (AdObjectCompiledFunction*) obj;
            break;
        }
        case OT_CLOSURE: {
            delete (AdClosureObject*) obj;
            break;
        }
        case OT_BUILTIN: {
            delete (AdObjectBuiltin*) obj;
            break;
        }
        default: {
            std::cout << "ERROR: object type not handled\n";
            break;
        }
    }
}