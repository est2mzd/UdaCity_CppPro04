#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
public:
    // default constructor
    Vehicle() : _id(0), _name(new std::string("Dafault Name"))
    {
        std::cout << "Vehicle #" << _id << " : Default constructor called" << std::endl;
    }

    // intitilizing constructor
    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
    {
        std::cout << "Vehicle #" << _id << " : Initializing constructor called" << std::endl;
    }

    // copy constructor : this time, we need "deep copy".
    Vehicle(Vehicle const &src)
    {
        // Quiz : start
        _id = src._id;

        if (src._name != nullptr)
        {
            _name = new std::string;
            *_name = *src._name;
        }

        std::cout << "Vehicle #" << _id << " : Copy constructor called" << std::endl;
        std::cout << "   Name : " << *_name <<  std::endl;
        // Quiz : end
    }

    // setter and getter 
    void setID(int id){ _id = id;}
    int  getID() { return _id;}
    void setName(std::string name) { *_name = name;}
    std::string getName() {return *_name;}


private:
    int _id;
    std::string* _name;

};

int main()
{
    // create instances of class Vehicle
    Vehicle v0;                 // default constructor
    Vehicle v1(1, "Vehicle #1"); // initilizaing constructor

    // Launch a thread that modifies the Vehcile name
    // v0 is passed by value, so new Vehicle instance is created.
    std::future<void> ftr = std::async(
        [](Vehicle v){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            v.setName("Vehicle #2"); // there is no effect to v0, because of passing by value.
        },
        v0
    );

    v0.setName("Vehicle #3"); // v0._name = "Vehicle #3"
    ftr.wait();               // local name is "Vehicle #2", but v0 name is "Vehicle #3"
    std::cout << v0.getName() << " : in Main()"<< std::endl;
    return 0;
}