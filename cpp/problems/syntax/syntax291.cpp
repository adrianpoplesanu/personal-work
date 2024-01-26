#include <iostream>

int main(int argc, char *argv[]) {
    std::string command_argument = "ls -la";
    std::string result = "";

    FILE *fpipe;
    char *command = (char*) command_argument.c_str();
    char c = 0;

    if (0 == (fpipe = (FILE*)popen(command, "r"))) {
        perror("popen() failed.");
        exit(EXIT_FAILURE);
    }

    while (fread(&c, sizeof c, 1, fpipe)) {
        //printf("%c", c);
        result += c;
    }

    pclose(fpipe);

    if (!result.empty()) {
        result.pop_back();
    }

    std::cout << result << "\n";

    return 0;
}
