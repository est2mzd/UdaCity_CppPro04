#include <iostream>

template <class T1>
T1 add(T1 a, T1 b){ return a + b;}

template <class T1>
T1 sub(T1 a, T1 b){return a -b;}

int main()
{
    std::cout << add(50.0 , 16.1) << std::endl;
    std::cout << sub(5, 8) << std::endl;
}