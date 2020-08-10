#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}

private:
    int _id;
};


class WaitingVehicles
{
public:
    WaitingVehicles() : _tmpVehicles(0){}

    // getter and setter
    void printSize()
    {
        std::cout << "#vehicles = " << _tmpVehicles << std::endl;
    }

    // typical behavior methods
    void pushBack(Vehicle &&v)
    {
        // _vehicles.push_back(std::move(v)); // data race would cause on exception
        int oldNum = _tmpVehicles;
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // wait deliberately to expose the data race
        _tmpVehicles = oldNum + 1;
    }

private:
    std::vector<Vehicle> _vehicles;// list of all vehicles waiting to enter this intersection
    int _tmpVehicles;
};

int main()
{
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    std::vector<std::future<void>> futures;

    // create 1000 threads
    for (int i = 0; i < 1000; i++)
    {
        Vehicle v(i); // create instance with (_id = i;)
        // format-1 : std::async( option, function, arguments )
        // format-2 : std::async( option, class_method, class_instance, arguments )
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    // wait all threads
    // format : for_each( iterator first, iterator last, function )
    std::for_each( futures.begin(), 
                   futures.end(), 
                   [](std::future<void> &ftr){ftr.wait();} 
                 );

    // print the size of thread                  
    queue->printSize();
    return 0;
}