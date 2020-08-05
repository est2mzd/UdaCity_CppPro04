#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> &&prms, double input, int sleep_time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    double output = sqrt(input);
    prms.set_value(output);
}

void checkResult(std::future<double> &&frt)
{
    auto status = frt.wait_for(std::chrono::milliseconds(1000));
    if (status == std::future_status::ready)
    {
        std::cout << "Result_1 = " << frt.get() << std::endl;
    }
    else if (status == std::future_status::timeout || status == std::future_status::deferred)
    {
        std::cout << "Result_1 unavailable" << std::endl;
    }
}

int main()
{
    double input = 64.0; // define input
    int sleep_time;      // define thread sleep time

    //**********************************************************
    // Sucess test pattern    
    std::promise<double> prms_1; // create promise
    std::future<double> ftr_1 = prms_1.get_future(); // cretate future
    sleep_time = 500;
    std::thread t_1(computeSqrt, std::move(prms_1), input, sleep_time);
    checkResult(std::move(ftr_1));

    //**********************************************************
    // Failure test pattern
    std::promise<double> prms_2; // create promise
    std::future<double> ftr_2 = prms_2.get_future(); // cretate future
    sleep_time = 2000;
    std::thread t_2(computeSqrt, std::move(prms_2), input, sleep_time);
    checkResult(std::move(ftr_2));

    // thread barrire
    t_1.join();
    t_2.join();

    return 0;    
}