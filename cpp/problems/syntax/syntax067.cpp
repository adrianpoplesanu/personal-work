#include <iostream>
#include <string>
#include <stack>
using namespace std;

int precedence (char op) {
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/')
        return 2;
    return 0;
}

int applyOp (int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0; // this is dumb
}

int evaluate (string tokens) {
    int i;
    stack <int> values;
    stack <char> ops;

    for (i = 0; i < tokens.length(); i++) {
        //cout << i << endl;
        if (tokens[i] == ' ')
            continue;
        else if (tokens[i] == '(') {
            ops.push(tokens[i]);
        }
        else if (isdigit(tokens[i])) {
            int val = 0;
            while (i < tokens.length() && isdigit(tokens[i])) {
                val = (val*10) + (tokens[i]-'0');
                i++; // asta e problema cu segmentation fault cand paranteza de inchidere nu are spatiu in fata ei
            }
            values.push(val);
        }

        else if (tokens[i] == ')') {
            //cout << "aaa" << endl;
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            if(!ops.empty())
               ops.pop();
        } else {
            //cout << "bbb" << endl;
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    //cout << evaluate("10 + 2 * 6 + 1 - 23") << "\n";
    //cout << evaluate("100 * 2 + 12") << "\n";
    //cout << evaluate("100 * ( 2 - 12 )") << "\n"; // asta nu merge daca in paranteza pun inca o operatie
    //cout << evaluate("100 * ( 2 + 12 + 14 ) / 14") << endl;
    //cout << evaluate("2 * ( 1 + 1 + 2 ) / 2") << endl;
    //cout << evaluate("1 + 1 + 1 + 1 - 3") << endl;
    cout << evaluate("2 * ( 1     +1+111 )") << endl;
    return 0;
}