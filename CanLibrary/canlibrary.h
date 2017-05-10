#ifndef CANLIBRARY_H
#define CANLIBRARY_H

#ifdef linux

#include "arduPiCANBUS/arduPiCAN.h"


#elif _WIN32

#include "canwindows.h"

#endif

#include <QObject>

class CanLibrary
{
private:
    CAN can;
    int canspeed = 1000;
public:


    typedef struct{
            unsigned int id;
            struct
            {
              char rtr : 1;
              char length : 4;
            }header;

            uint8_t data[8];
    }messageCAN;

    CanLibrary();

    unsigned int getEngineLoad();
    unsigned int getEngineCoolantTemp();
    unsigned int getFuelPressure();
    unsigned int getIntakeMAPressure();
    unsigned int getEngineRPM();
    unsigned int getVehicleSpeed();
    unsigned int getTimingAdvance();
    unsigned int getIntakeAirTemp();
    unsigned int getMAFairFlowRate();
    unsigned int getThrottlePosition();
    unsigned int getFuelLevel();
    unsigned int getBarometricPressure();
    unsigned int getEngineFuelRate();
    QString getRawMessage();
    int getID();

    void ON(void);
    bool begin();
    uint8_t messageAvailable(void);



    messageCAN messageRx;
    messageCAN messageTx;

};

#endif // CANLIBRARY_H
