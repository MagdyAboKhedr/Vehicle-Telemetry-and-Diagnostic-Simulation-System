#ifndef __VEHICLE__H__
#define __VEHICLE__H__
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>
#include <memory>


//Car STATUS MACROS
#define CAR_OK              0
#define HIGH_ENGINE_TEMP    1
#define LOW_FUEL            2
#define LOW_BATTERY         3





/*---------------------------Classes Definitions------------------------------*/

/*Sensors class - no inheritns */
class v_sensors{
    protected:
    

    public:
    int setSpeed(void);

    int readDistance(void);

    int readTemp(void);

    int readBatt(void);

    int readFuel(void);

   
};
/*Sensors class - no inheritns */



/*---------------------------------------------------------*/

/*ECU class - Inherits from sensors Class */
class ECU : public v_sensors{
    public:
    ECU();
    void getSpeed(void);
    void getDistance(void);
    void getTemp(void);
    void getBatt(void);
    void getFuel(void);
    void AdaptiveCruiseControl(void);

    protected:
    int speed;
    int distance;

    int temp;
    int batt;
    int fuel;
};
/*ECU class - Inherits from sensors Class */


/*---------------------------------------------------------*/



/*Vehicle class - Inherits from ECU Class */
class vehicle: public ECU{
    public:
    vehicle();
    void moveCar(void);
    void stopCar(void);

    protected:
    int car_status;
};
/*Vehicle class - Inherits from ECU Class */



/*---------------------------------------------------------*/



/*Diagnostics class - no inheritens */
class diag{
    public:
    diag();
    static int checkSYS(int *temp, int *fuel, int *battery);

    protected:
    bool sys_flag;
};
/*Diagnostics class - no inheritens */

/*---------------------------------------------------------*/


/*Logger Class */

class Logger {
private:
    static std::shared_ptr<Logger> instance;
    std::ofstream logFile;

    // Private constructor
    Logger();

    // Private copy constructor and assignment operator to prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    // Destructor
    ~Logger();

    // Static method to get the single instance
    static std::shared_ptr<Logger> getInstance();

    // Logging methods
    void logInfo(const std::string& message);
    void logError(const std::string& message);
    void logDebug(const std::string& message);
};


/*Logger Class */

/*---------------------------------------------------------*/

















#endif  //!__VEHICLE__H__