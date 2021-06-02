#include <iostream>

template<typename T>
class ArrayList {
private:
    T elem[10];
    int size;
public:
    ArrayList() {
        size = 0;
    }
    void Add(T e) {
        elem[size++] = e;
    }
    T GetAt(int i) {
        return elem[i];
    }
    void Print() {
        for (int i = 0; i < size; i++) std::cout << elem[i] << " ";
        std::cout << "\n";
    }
};

int main(int argc, char *argv[]) {
    ArrayList<int> numbers;

    numbers.Add(1);
    numbers.Add(2);
    numbers.Add(3);
    numbers.Print();

    ArrayList<std::string> countries;
    countries.Add("Italia");
    countries.Add("Belgia");
    countries.Add("Franta");
    countries.Print();

    return 0;
}
