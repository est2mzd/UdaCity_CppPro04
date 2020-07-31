#include <iostream>
#include <thread>
#include <string>

void printName(std::string &name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    name += " (from Tread)";
    std::cout << name << std::endl;
}

int main()
{
    std::string name("MyThread");

    // starting thread
    std::thread t(printName, std::ref(name), 50);
  //std::thread t2(printName, &name, 50);         // compile error

    // wait for thread before returning
    t.join();
  //t2.join();

    // print name from main
    name += " (from Main)";
    std::cout << name << std::endl;

    return 0;
}