#include <iostream>
#include <vector>

void print(std::vector<int> numbers) {
    for (int i : numbers) {
        std::cout << i << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::vector<int> numbers;
    for (int i = 0; i < 10; i++) {
        numbers.push_back(i);
    }

    print(numbers);

    std::vector<int> filtered_numbers;

    for (int i : numbers) {
        if (i % 2 == 0) {
            filtered_numbers.push_back(i);
        }
    }

    numbers = filtered_numbers;

    print(numbers);

    return 0;
}
