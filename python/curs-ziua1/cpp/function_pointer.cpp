#include <iostream>

typedef void (*callback)();

void login() {
    std::cout << "<login></login>\n";
}

void price() {
    std::cout << "<price></price>\n";
}

void handle_response(callback c) {
   c();
}

int main(int argc, char *argv[]) {
    void (*fp)();

    //fp = &login;
    //fp();

    //fp = &price;
    //fp();

    handle_response(&login);
    handle_response(&price);

    return 0;
}
