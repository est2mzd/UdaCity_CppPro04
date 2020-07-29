#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) 
    {
        std::cout << "call constructor \n";
    }
    void operator()(int j)
    {
        std::cout << "Vehicle #" << j << " has been created" << std::endl;
    }

private:
    int _id;    
};

int main()
{
    //create thread
    std::thread t = std::thread(Vehicle(1)); // use copy initilization

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t.join();

    return 0;
}