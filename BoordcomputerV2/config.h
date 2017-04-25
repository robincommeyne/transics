/*! \file */
/*! Class containing properties for the received config file */

#ifndef CONFIG_H
#define CONFIG_H



class Config
{
    /*! \todo create class header file */


    int ReadInterval;
    bool Speed;
    bool RPM;
    bool Temperature;
    bool FuelLevel;
    bool BarometricPressure;
    bool Voltage;
    bool Distance;
    bool Oxygen;
    bool IntakeAirTemp;
    bool IntakeMapPressure;
    bool ThrottlePosition;
    bool MAFAirFlowrate;
    bool Runtime;

    public:
        Config(int,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool);
        Config();

};

#endif // CONFIG_H
