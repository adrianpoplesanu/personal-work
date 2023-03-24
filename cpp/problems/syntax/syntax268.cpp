#include <iostream>
#include <regex>

std::string replaceAll(std::string str, const char* begin, const char* replacement) {
  std::regex expr(begin);

  return std::regex_replace(str, expr, replacement);
}
std::string replaceAll(std::string str, const char* begin, int group) {
  std::regex expr(begin);

  std::smatch sm;
  std::regex_search(str, sm, expr);

  while (sm.size() > 0) {
    std::regex_search(str, sm, expr);

    str = std::regex_replace(str, expr, std::string(sm[group]), std::regex_constants::format_first_only);
  }

  return str;
}

int main(int argc, char *argv[]) {
    std::string text = "aaa\\\"bbb";

    for (int i = 0; i < 8; i++) {
        std::cout << text.at(i) << "\n";
    }

    std::cout << text << "\n";

    text = std::regex_replace(text, std::regex("\\\""), "\""); // asta nu merge

    std::cout << text << "\n";

    std::string test = "aaa bbb ccc bbb";
    test = std::regex_replace(test, std::regex("bbb"), "fff");
    std::cout << test << "\n";

    std::string a = "aaa\\\"bbb";
    a = replaceAll(a, R"(\\([\"\']))", 1);
    std::cout << a << "\n";
}
