#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()(int i)
    {
        std::cout << "Vehicle < " << i << " > has been created" << std::endl;
    }
};

int main()
{
    //create thread
    std::thread t = std::thread(Vehicle(5)); // use copy initilization

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}