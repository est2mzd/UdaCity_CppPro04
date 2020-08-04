#include <iostream>
#include <thread>
#include <future>
#include <string>

// &  : Lvalue reference  /  && : Rvalue reference
void modifyMessage(std::promise<std::string>&& prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    std::string modifiedMessage = message + " has been modified.";
    prms.set_value(modifiedMessage);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future
    std::promise<std::string> my_promise;
    std::future<std::string>  my_future = my_promise.get_future();

    // start thread and pass promise as argument
    std::thread my_thread(modifyMessage, std::move(my_promise), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    std::string messageFromThread = my_future.get();
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    my_thread.join();

    return 0;
}