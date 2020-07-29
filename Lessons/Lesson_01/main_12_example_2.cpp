#include <iostream>
#include <thread>

class Vehicle
{
public:
    // operator + operand + ()
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
};

int main()
{
    // created thread
    // std::tread t0(Vehicle()); --> compile error
    std::thread t1( (Vehicle()) ); // Add an extra pair of parantheses
    std::thread t2 = std::thread( Vehicle() ); // Use copy initialization
    std::thread t3{ Vehicle() }; // Use uniform initialization with braces

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
