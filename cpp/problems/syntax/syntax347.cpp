#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <deque>

namespace fs = std::filesystem;

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string YELLOW = "\033[1;33m";

const int CONTEXT_LINES = 5; // Number of lines before/after match

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

    std::deque<std::string> prevLines; // Stores last 5 lines before a match
    std::string line;
    int lineNumber = 0;
    bool matchFound = false;
    std::deque<std::string> nextLines; // Stores 5 lines after match

    while (std::getline(file, line)) {
        lineNumber++;

        // Store previous lines in a deque (FIFO buffer)
        if (prevLines.size() == CONTEXT_LINES) {
            prevLines.pop_front();
        }
        prevLines.push_back(line);

        if (line.find(keyword) != std::string::npos) {
            // Print filename and line number
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Match in " << filePath << " (line " << lineNumber << "):" << std::endl;

            // Print previous lines
            for (const auto& prev : prevLines) {
                std::cout << prev << std::endl;
            }

            // Print matched line with highlighting
            std::cout << YELLOW << ">" << RESET << " ";
            highlightAndPrint(line, keyword);

            // Read 5 more lines after match
            for (int i = 0; i < CONTEXT_LINES && std::getline(file, line); i++) {
                std::cout << line << std::endl;
            }

            std::cout << "-----------------------------------" << std::endl;
            matchFound = true;
            prevLines.clear(); // Clear buffer to avoid duplicate context in next matches
        }
    }

    if (!matchFound) {
        std::cout << "No matches found in " << filePath << std::endl;
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

