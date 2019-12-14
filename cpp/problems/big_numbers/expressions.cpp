#include "expressions.h"
#include <iostream>
using namespace std;

bool EvaluateCondition(map<string, BigNumber> variables, string cond) {
    //cout << "evaluating:... " << cond << endl;
    regex check_conditional_keywords("\(*(.*)(and|or)(.*)\)*");
    smatch m;
    regex_search(cond, m, check_conditional_keywords);
    return true;
}