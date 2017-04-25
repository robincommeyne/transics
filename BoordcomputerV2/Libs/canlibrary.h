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
    CanLibrary();

    unsigned int getEngineLoad();
    unsigned int getEngineCoolantTemp();
    unsigned int getFuelPressure();
    unsigned int getIntakeMAPressure();
    unsigned int getEngineRPM();
    unsigned int getVehicleSpeed();
    unsigned int getTimingAdvance();
    unsigned int getIntankeAirTemp();
    unsigned int getMAFairFlowRate();
    unsigned int getThrottlePosition();
    unsigned int getFuelLevel();
    unsigned int getBarometricPressure();
    unsigned int getEngineFuelRate();

    void ON(void);
    bool begin();
    uint8_t messageAvailable(void);

};

#endif // CANLIBRARY_H
