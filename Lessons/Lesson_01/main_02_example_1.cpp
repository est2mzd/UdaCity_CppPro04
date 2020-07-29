// g++ -std=c++11 xxx.cpp
#include <iostream>
#include <thread>

int main(){
    std::cout << "Hello concurrent world from main ! Thread id = ";
    std::cout << std::this_thread::get_id() << std::endl; // id = non-executing thread

    std::cout << "Hello concurrent world from main ! Thread id = ";
    std::cout << pthread_self() << std::endl;             // id = 0
}

