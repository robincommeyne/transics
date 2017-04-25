/*! \file */

#include "config.h"

Config::Config(int readinterval,bool speed,bool rpm,bool temperature,bool fuellevel,
               bool barometricpressure,bool voltage,bool distance,bool oxygen,
               bool intakeairtemp,bool intakemappressure,bool throttleposition,bool mafairflowrate,bool runtime)
{
    /*! \todo create class constructor */

       ReadInterval = readinterval;
       Speed = speed;
       RPM = rpm;
       Temperature = temperature;
       FuelLevel = fuellevel;
       BarometricPressure = barometricpressure;
       Voltage = voltage;
       Distance = distance;
       Oxygen = oxygen;
       IntakeAirTemp = intakeairtemp;
       IntakeMapPressure = intakemappressure;
       ThrottlePosition = throttleposition;
       MAFAirFlowrate = mafairflowrate;
       Runtime = runtime;

}
Config::Config()
{

}
