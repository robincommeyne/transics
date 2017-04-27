/*! \file */
/*! Class containing properties for the received config file */

#ifndef CONFIG_H
#define CONFIG_H



class Config
{
    /*! \todo create class header file */




    public:

    int ReadInterval;
    bool EngineLoad;
    bool EngineCoolantTemp;
    bool FuelPressure;
    bool IntakeMAPressure;
    bool EngineRPM;
    bool VehicleSpeed;
    bool TimingAdvance;
    bool IntakeAirtemp;
    bool MAFairFlowRate;
    bool ThrottlePosition;
    bool FuelLevel;
    bool BarometricPressure;
    bool EngineFuelRate;


        Config(int,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool);
        Config();

};

#endif // CONFIG_H
