// copy contructor syntax
#include <iostream>
using namespace std;

class BigNumber {
private:
    int cifre[10];
public:
    BigNumber();
    BigNumber(BigNumber const&);
    void Update();
    void Print();
};

BigNumber::BigNumber() {
    for (int i = 0; i < 10; i++) cifre[i] = 0;
}

BigNumber::BigNumber(BigNumber const &obj) {
    for (int i = 0; i < 10; i++) cifre[i] = obj.cifre[i];
}

void BigNumber::Update() {
    cifre[0]++;
}

void BigNumber::Print() {
    for (int i = 0; i < 10; i++) cout << cifre[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    BigNumber numar;
    numar.Print();
    numar.Update();
    numar.Print();
    BigNumber numar2(numar);
    numar2.Print();
    numar2.Update();
    numar2.Print();
    return 0;
}
