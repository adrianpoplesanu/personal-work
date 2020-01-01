// overriding ++ prefix and postfix operators
#include <iostream>
using namespace std;

class Elev {
private:
    int age;
public:
    Elev();
    int GetAge();
    void SetAge(int);
    Elev& operator ++();
    Elev operator ++(int);
};

Elev::Elev() : age(18) {
};

int Elev::GetAge() {
    return age;
}

void Elev::SetAge(int val) {
    age = val;
}

Elev& Elev::operator ++() {
    age++;
    return *this;
}

Elev Elev::operator ++(int) {
    Elev temp;
    temp.SetAge(age);
    ++(*this);
    return temp;
}

int main(int argc, char *argv[]) {
    Elev elev;
    cout << elev.GetAge() << endl;
    ++elev;
    cout << elev.GetAge() << endl;
    elev++;
    cout << elev.GetAge() << endl;
    return 0;
}
