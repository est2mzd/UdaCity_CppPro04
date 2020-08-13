#include <iostream>
#include <random>

int main()
{
    std::random_device seed;
    std::mt19937 engine{seed()};

    for (int i = 0; i < 10; i++)
    {
        std::cout << engine() << std::endl;
    }

    std::cout << "-----------------------" << std::endl;

    std::uniform_int_distribution<int> rand_dist(4000, 6000);

    for (int i = 0; i < 10; i++)
    {
        std::cout << rand_dist(engine) << std::endl;
    }    
}