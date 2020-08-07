#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
public:
    // default constructor
    Vehicle() : _id(0)
    {
        std::cout << "Vehicle #" << _id << " Default constructor called" << std::endl;
    }

    // initializing constructor
    Vehicle(int id) : _id(id)
    {
        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
    }

    // setter and getter
    void setID(int id) { _id = id;}
    int  getID() {return _id;}

private:
    int _id;
};

int main()
{
    // create instances of class Vehicle
    Vehicle v0;    // default constructor
    Vehicle v1(1); // initilizing constructor

    // read and write name in different threads (which one of the above creates a data race?)
    std::future<void> ftr = std::async(
        // Lambda func
        [](Vehicle v){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            v.setID(2);
        },
        // argument
        v0
    );

    // 
    v0.setID(3);
    ftr.wait();  // wait until procedure is done
    std::cout << "Vehicle #" << v0.getID() << " in Main()" << std::endl;
    return 0;
}