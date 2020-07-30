// g++ -std=c++11 xxx.cpp
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    // create lambdas
    int id = 0; // Define an integer variable

    // Error: 'id' cannot be accessed
    // auto f0 = [](){cout << "ID_0 = " << id << endl;}; 
    
    id ++;
    // OK : 'id' is captured by value
    auto f1 = [id](){cout << "ID_1 = " << id << endl;}; 

    id ++;
    // OK : 'id' is captured by reference
    auto f2 = [&id](){cout << "ID_2 = " << id << endl;}; 

    // Error : 'id' may not be mofified
    // auto f3 = [id](){cout << "ID_3 = " << ++id << endl;}; 

    // OK : 'id' may be mofified
    auto f4 = [id]() mutable {cout << "ID_4 = " << ++id << endl;};

    // execute lambdas
    f1();
    f2();
    f4();

    return 0;
}