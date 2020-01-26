#include <iostream>
#include <string>
#include <thread>
using namespace std;
void threadCallback()
{
    cout<<"Passed Number = " << endl;
    cout<<"Passed String = " << endl;
}
int main()  
{
    int x = 10;
    string str = "Sample String";
    thread threadObj(threadCallback);
    threadObj.join();
    return 0;
}
