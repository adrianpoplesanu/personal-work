#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string YELLOW = "\033[1;33m";

void highlightAndPrint(const std::string& line, const std::string& keyword) {
    size_t pos = 0;
    std::string tempLine = line;
    std::string result;

    while ((pos = tempLine.find(keyword, pos)) != std::string::npos) {
        result += tempLine.substr(0, pos) + YELLOW + keyword + RESET;
        tempLine = tempLine.substr(pos + keyword.length()); // Store remaining part
        pos = 0; // Reset position for next search in the new tempLine
    }
    
    result += tempLine; // Append remaining part
    std::cout << result << std::endl;
}

void searchInFile(const fs::path& filePath, const std::string& keyword) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.find(keyword) != std::string::npos) {
            std::cout << filePath << ":" << lineNumber << ": ";
            highlightAndPrint(line, keyword);
        }
    }
}

void traverseAndSearch(const fs::path& directory, const std::string& keyword) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (fs::is_regular_file(entry.path())) {
                searchInFile(entry.path(), keyword);
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <directory_path> <keyword>" << std::endl;
        return 1;
    }

    fs::path rootPath = argv[1];
    std::string keyword = argv[2];

    if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
        std::cerr << "Invalid directory: " << rootPath << std::endl;
        return 1;
    }

    traverseAndSearch(rootPath, keyword);
    return 0;
}

