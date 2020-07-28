#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

int main(){
    unsigned int nCores = thread::hardware_concurrency();
    cout << "This machine supports concurrency with " << nCores;
    cout << " cores avialable" << endl;
    return 0;
}