#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}
*/


template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lock_g(_mutex); // PF.4a
    _queue.push_back(std::move(msg));           // PF.4a
    _condition.notify_one();                    // PF.4a
}

// template void MessageQueue<TrafficLightPhase>(T &&msg);


/* Implementation of class "TrafficLight" */

/* 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}
*/

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread 
    // when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    // launch drive function in a thread
    threads.emplace_back(std::thread( &TrafficLight::cycleThroughPhases, this));
}


// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
    std::chrono::high_resolution_clock::time_point t_changed = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t_updated = std::chrono::high_resolution_clock::now();
    int t_duration = 0;

    // random engine
    std::random_device seed;
    std::mt19937 engine{seed()};
    std::uniform_int_distribution<int> rand_dist(4000, 6000);

    while(true)
    {
        // wait 1 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // calc time duration
        t_updated  = std::chrono::high_resolution_clock::now();
        t_duration = std::chrono::duration_cast<std::chrono::milliseconds> (t_updated - t_changed).count();

        if (t_duration < rand_dist(engine))
            continue;

        // guard the thread in oreder to modify the traffic light correctly
        std::lock_guard<std::mutex> lock_g(_mutex);

        // toggle the traffic light status
        if(_currentPhase == TrafficLightPhase::red)
        {
            _currentPhase = TrafficLightPhase::green;
            std::cout << "   Traffic Light ----> Green " << std::endl;
            t_changed = std::chrono::high_resolution_clock::now();
        }
        else
        {
            _currentPhase = TrafficLightPhase::red;
            std::cout << "   Traffic Light ----> Red " << std::endl;
            t_changed = std::chrono::high_resolution_clock::now();
        }

        // send message
        _messageQueue.send(std::move(_currentPhase)); // FP.2a & FP.4b
        
    }
}

