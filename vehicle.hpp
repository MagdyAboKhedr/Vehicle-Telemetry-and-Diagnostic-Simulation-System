#ifndef __VEHICLE__H__
#define __VEHICLE__H__

class diag;








class v_sensors{
    protected:
    

    public:
    int setSpeed(void);

    int readDistance(void);

    int readTemp(void);

    int readBatt(void);

    int readFuel(void);

   
};

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

class vehicle: public ECU{
    public:
    void moveCar(void);
};


class diag{
    public:
    diag();
    static bool checkSYS(int *temp, int *fuel, int *battery);

    protected:
    bool sys_flag;
};
















#endif  //!__VEHICLE__H__