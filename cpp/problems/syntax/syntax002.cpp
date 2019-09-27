// This proves that even though the loop gets executed only 4 times
// the condition is however evaluated 5 times
// Kinda makes sense
// true true true true false = 5 time
// so if one of the expresions in the condition modifies another variable
// then the variable will be modified 5 times
#include <iostream>
using namespace std;

bool test_condition(int i, int n) {
    cout << i;
    return i < n;
}

int main(int argc, char *argv[]) {
    for(int i = 0; cout << i++ << " ", cout << i << " ", test_condition(i, 5); ) {
        cout << endl;
        //if (i == 5) break;
    }
    return 0;
}
