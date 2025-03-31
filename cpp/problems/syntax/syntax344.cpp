#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void traverseDirectory(const fs::path& directory) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            std::cout << entry.path() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>" << std::endl;
        return 1;
    }

    fs::path rootPath = argv[1];

    if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
        std::cerr << "Invalid directory: " << rootPath << std::endl;
        return 1;
    }

    traverseDirectory(rootPath);
    return 0;
}

