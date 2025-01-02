#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
    std::map<int, std::string> a;
    a.insert(std::make_pair(1, "aaa"));

    std::cout << a[1] << "\n";

    std::string res = a[2];
    std::cout << ":::" << res << ":::\n";

    if (res == "") {
        std::cout << "e empty!!\n";
    }
    return 0;
}
