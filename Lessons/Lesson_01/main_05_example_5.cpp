#include <thread>
#include <iostream>

void threadFunction()
{
    // simulate work 1 & 2
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout  << "Finished work 1 in thread\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50));    
    std::cout  << "Finished work 2 in thread\n";
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // wait for thread to finish
    t.join();

    // do something in main()
    // simulate work 1 & 2
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 2 in main\n";

    return 0;    
}