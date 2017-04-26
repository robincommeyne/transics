/*! \file */

#include "config.h"

Config::Config(int readinterval,bool engineload,bool enginecoolanttemp,bool fuelpressure,bool intakemappressure,
               bool enginerpm,bool vehiclespeed,bool timingadvance,bool intakeairtemp,
               bool mafairflowrate,bool throttleposition,bool fuellevel,bool barometricpressure,bool enginefuelrate)
{
    /*! \todo create class constructor */

    ReadInterval = readinterval;
    EngineLoad = engineload;
    EngineCoolantTemp = enginecoolanttemp;
    FuelPressure = fuelpressure;
    IntakeMAPPRessure = intakemappressure;
    EngineRPM = enginerpm;
    VehicleSpeed = vehiclespeed ;
    TimingAdvance = timingadvance;
    IntakeAirtemp = intakeairtemp;
    MAFairFlowRate = mafairflowrate;
    ThrottlePosition = throttleposition;
    FuelLevel = fuellevel;
    BarometricPressure = barometricpressure;
    EngineFuelRate = enginefuelrate;

}
Config::Config()
{

}
