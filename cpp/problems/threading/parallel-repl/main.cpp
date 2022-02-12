#include <iostream>
#include <thread>
#include <vector>

void worker(int id, std::vector<std::string> *commands) {
    for (int i = 0; i < 100; i++) {
        std::cout << "id: " << id << " step: " << i << "\n";
    }
    /*while(1) {

    }*/
}

void reader(int id, std::vector<std::string> *commands) {
    while(1) {
        std::string command;
        std::cout << ">> ";
        std::cin >> command;
        if (command == "exit()") break;
        else std::cout << command;
    }
}

int main(int argc, char *argv[]) {
    std::cout << "running some parrallel tests...\n";

    std::vector<std::string> *commands = new std::vector<std::string>();
    commands->push_back("");
    commands->push_back("");
    commands->push_back("");
    commands->push_back("");

    std::thread th0(worker, 0, commands);
    std::thread th1(worker, 1, commands);
    std::thread th2(worker, 2, commands);
    std::thread th3(reader, 3, commands);

    th0.join();
    th1.join();
    th2.join();
    th3.join();

    //std::cout << ".....\n";

    return 0;
}
