#ifndef __DRIVER_H
#define __DRIVER_H

class Driver {
public:
    Driver();
    ~Driver();

    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();
};

class DriverManager {
public:
    DriverManager();
    ~DriverManager() = default;

    void AddDriver(Driver* driver);
    void ActivateAll();
private:
    Driver* drivers[256];
    int numDrivers;
};

#endif