// g++ -std=c++11 xxx.cpp
#include <thread>
#include <vector>
#include <algorithm>
using std::vector;
using std::thread;
using std::for_each;

int main(){
    vector<thread> threads;

    // startup n threads
    int nThreads = 4;
    for (int i=0; i<nThreads; i++){
        // lambda eq : thread( [](){while(true);} );
    }

    // wait for threads to finish before leaving main
    for_each( threads.begin(), threads.end(), [](thread &t){t.join();} );

    return 0;
}
