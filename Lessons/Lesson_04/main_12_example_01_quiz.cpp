#include <iostream>
#include <thread>
#include <vector>
#include<future>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <deque>

template <class T> class MessageQue
{
public:
    T receive()
    {
        // perform vector modification under the lock
        std::unique_lock<std::mutex> uLock(_mutex);

        // pass unique lock to condition variable. wait until "!_messages.empty()" becomes true
        _cond.wait(uLock, [this]{return !_messages.empty();});

        // remove last vector element from queue
        T msg = std::move(_messages.back());
        _messages.pop_back();

        // will not be copied due to return value optimization (RVO) in C++
        return msg;
    }

    void send(T &&msg)
    {
        // simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // preform vector modification under the lock
        std::lock_guard<std::mutex> gLock(_mutex);

        // add vector to queue
        std::cout << "    Message #" << msg << " will be added to the queue" << std::endl;
        _messages.push_back(std::move(msg));

        // nofity client after pushing new Vehicle into vector
        _cond.notify_one();
    }

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    // list of all vehicles waiting to enter this intersection
    std::deque<T> _messages;
};


int main()
{
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<MessageQue<int>> queue(new MessageQue<int>);

    std::cout << "Sapwning thread..." << std::endl;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 10; i++)
    {
        // create a new Vehicle instance and move it into the queue
        int message = i;
        futures.emplace_back(std::async(std::launch::async, &MessageQue<int>::send, queue, std::move(message)));
    }

    std::cout << "Collecting resutls..." << std::endl;

    while(true)
    {
        // popBack wakes up when a new element is available in the queue
        int message = queue->receive();
        std::cout << "      Message #" << message << " has been removed from the queue" << std::endl;
    }

    std::for_each(futures.begin(), futures.end(),
                  [](std::future<void> &ftr){ftr.wait();}
                );
    
    std::cout << "Finished !" << std::endl;
    return 0;
}