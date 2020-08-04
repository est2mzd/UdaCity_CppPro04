// g++ -pthread -std=c++11 XXX.cpp
#include <iostream>
#include <thread>
#include <string>

void printMessage(std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Thread 1 : " << message << std::endl;
}

int main()
{
    // define message
    std::string message = "My Message";

    // 1 : start thread using variadic templates
    std::thread t1(printMessage, message);

    // 2 : start thread using a Lambda
    std::thread t2(
        [message](){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << "Thread 2 : " << message << std::endl;
    });

    // thread barrier
    t1.join();
    t2.join();

    return 0;
}