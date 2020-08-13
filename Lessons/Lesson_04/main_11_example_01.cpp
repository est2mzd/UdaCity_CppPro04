#include <iostream>
#include <thread>
#include <vector>
#include<future>
#include <mutex>
#include <condition_variable>
#include <algorithm>

class Vehicle
{
public:
    Vehicle(int id): _id(id) {}
    int getID(){return _id;}

private:
    int _id;
};

class WaitingVehicles
{
public:
    WaitingVehicles(){}

    Vehicle popBack()
    {
        // perform vector modification under the lock
        std::unique_lock<std::mutex> uLock(_mutex);

        // pass unique lock to condition variable. wait until "!_vehicles.empty()" becomes true
        _cond.wait(uLock, [this]{return !_vehicles.empty();});

        // remove last vector element from queue
        Vehicle v = std::move(_vehicles.back());
        _vehicles.pop_back();

        // will not be copied due to return value optimization (RVO) in C++
        return v;
    }

    void puchBack(Vehicle &&v)
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // preform vector modification under the lock
        std::lock_guard<std::mutex> gLock(_mutex);

        // add vector to queue
        std::cout << "    Vehicle #" << v.getID() << " will be added to the queue" << std::endl;
        _vehicles.push_back(std::move(v));

        // nofity client after pushing new Vehicle into vector
        _cond.notify_one();
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    // list of all vehicles waiting to enter this intersection
    std::vector<Vehicle>_vehicles;
};


int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Sapwning thread..." << std::endl;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 10; i++)
    {
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::puchBack, queue, std::move(v)));
    }

    std::cout << "Collecting resutls..." << std::endl;

    while(true)
    {
        // popBack wakes up when a new element is available in the queue
        Vehicle v = queue->popBack();
        std::cout << "      Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;
    }

    std::for_each(futures.begin(), futures.end(),
                  [](std::future<void> &ftr){ftr.wait();}
                );
    
    std::cout << "Finished !" << std::endl;
    return 0;
}