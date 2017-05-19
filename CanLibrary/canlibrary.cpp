#ifdef __arm__

#include "arduPiCANBUS/arduPiCAN.h"
#include "arduPiCANBUS/arduPi.h"
#include "arduPiCANBUS/arduPiClasses.h"
#include "arduPiCANBUS/arduPiMultiprotocol.h"
#include "arduPiCANBUS/arduPiUART.h"
#include "arduPiCANBUS/arduPiUtils.h"

#else

#include "candummy.h"

#endif

#include "canlibrary.h"
#include <QObject>
#include <QDebug>
#include <QString>


CanLibrary::CanLibrary()
{

}

unsigned int CanLibrary::getEngineLoad()
{
    return can.getEngineLoad();
}

unsigned int CanLibrary::getEngineCoolantTemp()
{
    return can.getEngineCoolantTemp();
}
unsigned int CanLibrary::getFuelPressure()
{
    return can.getFuelPressure();
}

unsigned int CanLibrary::getIntakeMAPressure()
{
    return can.getIntakeMAPressure();
}
unsigned int CanLibrary::getEngineRPM()
{
    return can.getEngineRPM();
}
unsigned int CanLibrary::getVehicleSpeed()
{
    return can.getVehicleSpeed();
}
unsigned int CanLibrary::getTimingAdvance()
{
    return can.getTimingAdvance();
}
unsigned int CanLibrary::getIntakeAirTemp()
{
    return can.getIntankeAirTemp();
}
unsigned int CanLibrary::getMAFairFlowRate()
{
    return can.getMAFairFlowRate();
}
unsigned int CanLibrary::getThrottlePosition()
{
    return can.getThrottlePosition();
}
unsigned int CanLibrary::getFuelLevel()
{
    return can.getFuelLevel();
}
unsigned int CanLibrary::getBarometricPressure()
{
    return can.getBarometricPressure();
}
unsigned int CanLibrary::getEngineFuelRate()
{
    return can.getEngineFuelRate();
}
void CanLibrary::ON(void)
{
    can.ON();
}

bool CanLibrary::begin()
{
    CanLibrary canlibrary;
    can.begin(canspeed);
    if (canlibrary.messageAvailable() == 0)
    {
         can.begin(500);

        if (canlibrary.messageAvailable() == 0)
        {
            can.begin(250);

            if (canlibrary.messageAvailable() == 0)
            {
               qDebug() << "Can not initiate CAN reading";
            }
            else
            {
               qDebug() << "CAN reading initiated";


        }
    }
}
    return true;
}

uint8_t CanLibrary::messageAvailable(void)
{
    return can.messageAvailable();
}

QString CanLibrary::getRawMessage()
{
    QString returnstring = "";
        for (int i=0; i < 8; i++)
        {

            returnstring.append(QString::number(can.messageRx.data[i]));

        }
    return returnstring;
}
int CanLibrary::getID()
{
    return can.messageRx.id;
}


