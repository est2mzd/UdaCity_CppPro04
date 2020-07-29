#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle has been created" << std::endl;
    }
};

int main()
{
    //create thread
    std::thread t = std::thread(Vehicle()); // use copy initilization

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}