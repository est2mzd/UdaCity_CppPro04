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
    int _id;    
};


class WaitingVehicles
{
public:
    WaitingVehicles() {}

    bool dataIsAvailable()
    {
        std::lock_guard<std::mutex> myLock(_mutex);
        return !_vehicles.empty();
    }

    Vehicle popBack()
    {
        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // remove last vector element from queue
        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back(); // delete the last element
        --_numVehicles; // quiz answer

        // will not be copied due to return value optimization (RVO) in C++
        return v;
    }

    void pushBack(Vehicle &&v)
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // perform vector modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);

        // add vector to queue
        std::cout << "    Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
        _vehicles.emplace_back(std::move(v));
        ++_numVehicles; // quiz answer
    }

    int getNumVehicle()
    {
        std::lock_guard<std::mutex> uLock(_mutex);
        return _numVehicles;
    }

private:
    // list of all vehicles waiting to enter this intersection
    std::vector<Vehicle> _vehicles; 
    std::mutex _mutex;
    int _numVehicles; // quiz answer
};


int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 10; i++)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
    }

    std::cout << "Collecting results..." << std::endl;

    while (true)
    {
        if (queue->dataIsAvailable())
        {
            Vehicle v = queue->popBack();
            std::cout << "      Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;

            if (queue->getNumVehicle() <= 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                break;
            }
        }
    }

    std::for_each( futures.begin(), futures.end(), [](std::future<void> &ftr){ftr.wait();} );
    std::cout << "Finished processing queue" << std::endl;
    std::cout << "  " << queue->getNumVehicle() << " vehicles left in the queue." << std::endl;
    return 0;
}