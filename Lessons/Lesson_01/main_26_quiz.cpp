#include <iostream>
#include <thread>
#include <string>

class Vehicle
{
public:
    Vehicle() : _id(0){}
    void addID(int id){_id = id;}
    void printID()
    {
        std::cout << "Vehicle ID = " << _id << std::endl;
    }
    // Todo: Modify the Vehicle class as indicated in the instructions
    void setName(std::string name){_name = name;}
    void printName()
    {
        std::cout << "Vehicle Name = " << _name << std::endl;
    }


private:
    int _id;
    std::string _name;
};

int main()
{
    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t1 = std::thread(&Vehicle::addID, v, 1);
    
    // Todo : Modify the main to start setName as a thread
    std::thread t2 = std::thread(&Vehicle::setName, v, "Moco");

    // wait for thread to finish
    t1.join();
    t2.join();

    // print 
    v->printID();
    v->printName();

    return 0;
}