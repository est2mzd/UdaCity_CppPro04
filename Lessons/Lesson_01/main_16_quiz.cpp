#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int id = 0;
    auto f0 = [&id](){cout << "ID in f0 = " << id << endl;};

    auto f1 = [id]() mutable  {cout << "ID in f1 = " << ++id << endl;};
    auto f2 = [&id]() mutable {cout << "ID in f2 = " << ++id << endl;};
    auto f3 = [](const int id){cout << "ID in f3 = " << id   << endl;};

    f1();
    cout << "ID in main = " << id << endl;

    f2();
    cout << "ID in main = " << id << endl;

    f3(++id);
    cout << "ID in main = " << id << endl;

    f0();
    return 0;
}
