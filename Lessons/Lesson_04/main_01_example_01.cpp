#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id) : _id(id) {}
    int getID(){return _id;}

private:
    int _id    ;
};


class WaitingVehicles
{
public:
    WaitingVehicles(){}

    void printIDs()
    {
        std::lock_guard<std::mutex> myLock(_mutex); // lock is released when myLock goes out of scope
        for(auto &v : _vehicles)
            std::cout << "    Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
    }

    void pushBack(Vehicle &&v)
    {
        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);
        std::cout << "    Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
        _vehicles.emplace_back(std::move(v));

        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

private:
    std::vector<Vehicle> _vehicles;
    std::mutex _mutex;
};


int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawing thread..." << std::endl;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 10; i++)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack , queue, std::move(v)));
    }

    // wait until pushBack is done.
    std::for_each( futures.begin(), futures.end(),
                   [](std::future<void> &ftr){ftr.wait();}
                  );
    
    std::cout << "Collecting resuls..." << std::endl;
    queue->printIDs();
    return 0;
}