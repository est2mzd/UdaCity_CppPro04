#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int id = 0;
    auto f = [](const int id){cout << "ID = " << id << endl;};

    // execute function object and pass the parameter
    f(id);
    return 0;
}