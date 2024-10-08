#include <iostream>
#include <thread>
#include <vector>

// trebuie facute clase de workeri cu status si alte chestii in ele, si facut spool-ing de threaduri si verificat totul cu valgrind


void worker(int id, std::vector<std::string> *commands) {
    /*for (int i = 0; i < 100; i++) {
        std::cout << "id: " << id << " step: " << i << "\n";
    }*/
    while((*commands)[id] != "kill") {
        //... do nothing
        if (id == 5) {
            //... actually works
        }
    }
    //std::cout << "shutting down worker " << id << "\n";
    // https://stackoverflow.com/questions/15033827/multiple-threads-writing-to-stdcout-or-stdcerr
    std::cout << "\rkilled\n>> ";
    (*commands)[id] = "killed";
}

void reader(int id, std::vector<std::string> *commands) {
    while(1) {
        /*for (int i = 0; i < 3; i++) {
            if ((*commands)[i] == "killed") {
                (*commands)[i] = "terminated";
                std::cout << "worker " << i << " shutdown\n";
            }
        }*/
        std::string command;
        std::cout << ">> ";
        std::getline(std::cin, command);
        if (command == "exit()") {
            (*commands)[3] = "exit";
            break;
        } else {
            //if (command != "") std::cout << command << "\n";
        }
        if (command == "kill 0") {
            (*commands)[0] = "kill";
        }
        if (command == "kill 1") {
            (*commands)[1] = "kill";
        }
        if (command == "kill 2") {
            (*commands)[2] = "kill";
        }
        if (command == "start 1") {
            (*commands)[0] = "start 1";

        }
    }
    (*commands)[0] = "kill";
    (*commands)[1] = "kill";
    (*commands)[2] = "kill";
}

void batchd(int id, std::vector<std::string> *commands, std::thread *threads[10]) {
    while((*commands)[3] != "exit") {
        if ((*commands)[0] == "start 1") {
            //...
            std::thread th5(worker, 5, commands);
            threads[5] = &th5;
            th5.join();
        }
    }

    // exit command was issued, deal with it now
    for (int i = 0; i < 6; i++) {
        // kill all the threads either via a threads[i].stop() like command or with (*commands)[i] = "kill" or "stop"
    }
}

int main(int argc, char *argv[]) {
    std::cout << "running some parrallel tests...\n";

    std::vector<std::string> *commands = new std::vector<std::string>();
    commands->push_back("");
    commands->push_back("");
    commands->push_back("");
    commands->push_back("");
    commands->push_back("");


    std::thread *threads[10];

    std::thread th0(worker, 0, commands);
    threads[0] = &th0;
    std::thread th1(worker, 1, commands);
    threads[1] = &th1;
    std::thread th2(worker, 2, commands);
    threads[2] = &th2;
    std::thread th3(reader, 3, commands);
    threads[3] = &th3;
    std::thread th4(batchd, 4, commands, threads);
    threads[4] = &th4;

    th0.join();
    th1.join();
    th2.join();
    th3.join();
    th4.join();

    //std::cout << ".....\n";

    return 0;
}
