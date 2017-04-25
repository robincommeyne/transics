#ifndef CANWINDOWS_H
#define CANWINDOWS_H

#include <QObject>

class CAN
{
public:
    CAN();
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
    bool begin(uint16_t speed);
    uint8_t messageAvailable(void);

    typedef struct{
            unsigned int id;
            struct
            {
              char rtr : 1;
              char length : 4;
            }header;

            uint8_t data[8];
    }messageCAN;

    messageCAN messageRx;
    messageCAN messageTx;
};

#endif // CANWINDOWS_H
