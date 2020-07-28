// g++ -std=c++11 -pthread xxx.cpp
#include <iostream>
#include <thread>

void threadFunction()
{
    // simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread \n";
}

int main()
{
    // create thread
    std::thread t(threadFunction);
    std::cout << "Thread id = " << t.get_id() << "\n";

    // do something in main()
    // simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work in main \n";

    // wati for thraed to finish
    t.join();

    return 0;
}