#include <iostream>
#include <thread>
#include <mutex>
#include <string>

class my_mutex : public std::mutex
{
public:
    my_mutex(std::string name) : _name(name){}
    void lock()
    {
        std::cout << _name << " locks." << std::endl;
        std::mutex::lock();
    }

    void unlock()
    {
        std::cout << _name << " unlocks." << std::endl;
        std::mutex::unlock();
    }    

private:
    std::string _name;
};

my_mutex mtx_1("mtx_1");
my_mutex mtx_2("mtx_2");

void Thread_A()
{
    // create deadlock problem
    mtx_2.lock();
    std::cout << "Thread A" << std::endl;
    mtx_1.lock();
    mtx_2.unlock();
    mtx_1.unlock();
}

void Thread_B()
{
    // create deadlock problem
    mtx_1.lock();
    std::cout << "Thread B" << std::endl;
    mtx_2.lock();
    mtx_1.unlock();
    mtx_2.unlock();
}

void ExecuteThreads()
{
    std::thread t1( Thread_A );
    std::thread t2( Thread_B );
    t1.join();
    t2.join();

    std::cout << "Finished" << std::endl;
}

int main()
{
    ExecuteThreads();
    return 0;
}