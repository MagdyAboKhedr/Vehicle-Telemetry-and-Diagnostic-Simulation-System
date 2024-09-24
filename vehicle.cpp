#include "vehicle.hpp"


 /*<-------vehicle implementation------>*/

vehicle::vehicle() : car_status(CAR_OK){
    Logger::getInstance()->logInfo("Car STARTED");
}


void vehicle::stopCar(){
    if(car_status == LOW_FUEL){
        std::cout << "Stopping car to put fuel" << std::endl;
        while(fuel<=100){
            std::cout << "Current fuel level: " << fuel << std::endl;
            fuel++;
        }

        
    }
    else if(car_status == LOW_BATTERY){
        std::cout << "Stopping car to recharge battery" << std::endl;
        while(batt<=90){
            std::cout << "Current fuel level: " << batt << std::endl;
            batt++;
        }
    }
    else if(car_status == HIGH_ENGINE_TEMP){
        std::cout << "Stopping car to cooldown" << std::endl;
        while(temp>45){
            std::cout << "Cooling, engine temp: " << temp << std::endl;
            temp--;
        }
    }
    
}

void vehicle::moveCar(){
    car_status = diag::checkSYS(&temp, &fuel, &batt);
    if(!car_status){
        ECU::AdaptiveCruiseControl();
    }
    else{
        vehicle::stopCar();
    }
}

/*<-------vehicle implementation------>*/





 /*<-------sensors implementation------>*/


int v_sensors::setSpeed(){
    int speed = (rand() % (250- 60 + 1)) + 60;
    
    return speed;
}

int v_sensors::readDistance(){
    int distance = (rand() % (15- 5 + 1)) + 5;
    return distance;
    
}


int v_sensors::readTemp(){
    int temp = (rand() % (50- 30 + 1)) + 30;
    return temp;
}

int v_sensors::readBatt(){
    static int batt = 90;
    batt--;
    return batt;
}

int v_sensors::readFuel(){
    static int Fuel = 100;
    Fuel-=5;
    return Fuel;
}

/*<-------sensors implementation------>*/






 /*<-------diagnostics implementation------>*/

diag::diag() : sys_flag(1){}

int diag::checkSYS(int *temp, int *fuel, int *battery){
    
    if(*temp <= 45){
        if(*fuel >= 60){
            if(*battery >= 60){
                    return 0;
            }
            else{
                std::cout << "Diagnostics Layer Failure, Check BATTERY LEVEL (LOW LEVEL).." << std::endl;
                return 3;
            }
        }
        else{
            std::cout << "Diagnostics Layer Failure, Check FUEL LEVEL (LOW LEVEL).." << std::endl;
            return 2;
        }
    }
    else{
        std::cout << "Diagnostics Layer Failure, Check ENGINE TEMPERATURE.." << std::endl;
        return 1;
    }
    
}
 /*<-------diagnostics implementation------>*/




  /*<-------ECU implementation------>*/

ECU::ECU() : speed(0), distance(0), temp(45), batt(90), fuel(100){
    std::cout << "Initial Speed: " << speed << std::endl;
    std::cout << "Initial Distance: " << distance << std::endl;
    std::cout << "Initial Temp: " << temp << std::endl;
    std::cout << "Initial Battery: " << batt << "%" << std::endl;
    std::cout << "<-----------CAR STARTED----------->" << std::endl;

}

void ECU::getSpeed(void){
    speed = v_sensors::setSpeed();
    std::cout << "Current Speed: " << speed << std::endl;
    
}

void ECU::getDistance(void){
    distance = v_sensors::readDistance();
    std::cout << "Current distance from object: " << distance << std::endl;
}
void ECU::getTemp(void){
    temp = v_sensors::readTemp();
    std::cout << "Current Temp: " << temp << std::endl;
}
void ECU::getBatt(void){
    batt = v_sensors::readBatt();
    std::cout << "Current Battery: " << batt << "%" << std::endl;
}
void ECU::getFuel(void){
    fuel = v_sensors::readFuel();
    std::cout << "Current fuel level: " << fuel << std::endl;
}

void ECU::AdaptiveCruiseControl(){
    ECU::getSpeed();
    ECU::getDistance();
    ECU::getTemp();
    ECU::getBatt();
    ECU::getFuel();
    if(speed >= 200){
        std::cout << "Speed Exceeded 200, breaking until reaching safety speed (150)" << std::endl;
        while(speed >= 150){
            speed-=10;
            std::cout << "Current Speed: " << speed << std::endl;
        }
    }

    if(distance <= 7){
        std::cout << "Object too near, breaking until distance is safe (10)" << std::endl;
        while(distance <= 10){
            distance++;
            speed-=10;
            std::cout << "Current distance from object: " << distance << std::endl;
            std::cout << "Current Speed: " << speed << std::endl;
        }
    }
}

 /*<-------ECU implementation------>*/


/*<-------------------Logger implementation--------------->*/
std::shared_ptr<Logger> Logger::instance = nullptr;

// Private constructor
Logger::Logger() {
    logFile.open("log.txt", std::ios::out | std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Unable to open log file.");
    }
}

// Destructor
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Static method to get the single instance
std::shared_ptr<Logger> Logger::getInstance() {
    if (instance == nullptr) {
        instance = std::shared_ptr<Logger>(new Logger());
    }
    return instance;
}

// Logging methods
void Logger::logInfo(const std::string& message) {
    logFile << "[INFO]: " << message << std::endl;
}

void Logger::logError(const std::string& message) {
    logFile << "[ERROR]: " << message << std::endl;
}

void Logger::logDebug(const std::string& message) {
    logFile << "[DEBUG]: " << message << std::endl;
}

/*<------------------------Logger implementation----------->*/