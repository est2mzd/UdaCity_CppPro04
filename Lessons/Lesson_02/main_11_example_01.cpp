#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divideByNumber(double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if(denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");
    
    return num/denom;
}

int main()
{
    double num = 42.0, denom = 2.0;

    // In case of using "async"   --> 1 line
    std::future<double> ftr = std::async(divideByNumber, num, denom);

    // In case of using "promise" --> 3 lines
    // std::promise<double> prms;
    // std::future<double> ftr = std::prms.get_future(); // <-- in case, we use "promise".
    // std::thread t(divideByNumber, std::move(prms), num, denom);


    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch(std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}