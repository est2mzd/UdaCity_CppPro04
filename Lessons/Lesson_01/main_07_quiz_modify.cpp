#include <iostream>
#include <thread>

void threadFunctionEven(int i)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "I = " << i << ": Even thread \n";
}

void threadFunctionOdd(int j)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "J = " << j << ": Odd thread \n";
}

int main()
{
    for(int i=0; i<6; i++)
    {
        if(i%2 == 0)
        {
            std::thread t(threadFunctionEven, i);
            t.detach();
        }else
        {
            std::thread t(threadFunctionOdd, i);
            t.detach();
        }
        
    }

    // ensure that main does not return before the threads are finished
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    std::cout << "End of main is reached \n";
    return 0;
}