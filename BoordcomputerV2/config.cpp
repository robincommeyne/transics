#include "config.h"

namespace cangateway {

    Config::Config()
    {
        _configmap.insert("EngineLoad",false);
        _configmap.insert("EngineCoolantTemp",false);
        _configmap.insert("FuelPressure",false);
        _configmap.insert("IntakeMAPressure",false);
        _configmap.insert("EngineRPM",false);
        _configmap.insert("VehicleSpeed",false);
        _configmap.insert("TimingAdvance",false);
        _configmap.insert("IntakeAirtemp",false);
        _configmap.insert("MAFairFlowRate",false);
        _configmap.insert("ThrottlePosition",false);
        _configmap.insert("FuelLevel",false);
        _configmap.insert("BarometricPressure",false);
        _configmap.insert("EngineFuelRate",false);

        set_readinterval(1);
    }
}

