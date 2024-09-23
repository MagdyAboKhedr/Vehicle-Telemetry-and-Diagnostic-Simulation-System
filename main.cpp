#include "vehicle.cpp"
#include "vehicle.hpp"
#include <chrono>
#include <thread>

int	main(int argc, char **argv)
{
    
    vehicle myCar;

    while(1)
    {
       
        myCar.moveCar();
        std::cout << "<----------------------------------------------------->" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }
    

}
