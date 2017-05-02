#include "config.h"

namespace cangateway {

    Config::Config()
    {
        Configmap.insert("EngineLoad",false);
        Configmap.insert("EngineCoolantTemp",false);
        Configmap.insert("FuelPressure",false);
        Configmap.insert("IntakeMAPressure",false);
        Configmap.insert("EngineRPM",false);
        Configmap.insert("VehicleSpeed",false);
        Configmap.insert("TimingAdvance",false);
        Configmap.insert("IntakeAirtemp",false);
        Configmap.insert("MAFairFlowRate",false);
        Configmap.insert("ThrottlePosition",false);
        Configmap.insert("FuelLevel",false);
        Configmap.insert("BarometricPressure",false);
        Configmap.insert("EngineFuelRate",false);
    }
}

