#include <iostream>
#include <vector>

std::vector<int> int_to_bytes(int param_int) {
    std::vector<int> bytes(4, 0);
    bytes[0] = (param_int >> 24) & 0xFF;
    bytes[1] = (param_int >> 16) & 0xFF;
    bytes[2] = (param_int >> 8) & 0xFF;
    bytes[3] = param_int & 0xFF;
    return bytes;
}

int main(int argc, char *argv[]) {
    std::vector<int> bytes = int_to_bytes(120112);

    for (int i = 0; i < 4; i++) {
        std::cout << bytes[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
