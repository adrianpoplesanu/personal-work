#include "evaluator.h"
#include "objects.h"
#include "objects.cpp"

#include <iostream>
#include <vector>

Evaluator::Evaluator() {

};

Evaluator::~Evaluator() {

};

void Evaluator::Eval() {
    std::vector<objects::Object*> object_list;
    objects::IntObject *io = new objects::IntObject(45);
    objects::StringObject *so = new objects::StringObject("neatza!");
    object_list.push_back(io);
    object_list.push_back(so);

    std::cout << "[";
    for (std::vector<objects::Object*>::iterator it = object_list.begin(); it != object_list.end(); ++it) {
        //std::cout << (*it)->type << '\n';
        switch((*it)->type) {
            case objects::NULL_OBJ:
            break;
            case objects::INT_OBJ:
                std::cout << ((objects::IntObject *)(*it))->val;
                //std::cout << "nu stiu de ce nu merge\n";
            break;
            case objects::STRING_OBJ:
                std::cout << ((objects::StringObject *)(*it))->val;
                //std::cout << "nu stiu de ce nu merge\n";
            break;
            case objects::FUNCTION_OBJ:
            break;
        }
        if (it + 1 != object_list.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
};
