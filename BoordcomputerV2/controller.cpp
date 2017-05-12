#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"
#include "dispatcher.h"

namespace cangateway {

    Controller::Controller()
    {
        _can.ON();
        _can.begin();
        _canIntervalTimer = new QTimer(this);
        connect(_canIntervalTimer, SIGNAL(timeout()), this, SLOT(ControllerHandler()));
        _canIntervalTimer->start(_intervalTimerInMs);
    }

    void Controller::ControllerThread()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
    }

    void Controller::GetCan()
    {
       qDebug() << "GetCan is called";


       _engineLoad = CanData(_can.getEngineLoad(),"EngineLoad",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _engineCoolantTemp = CanData(_can.getEngineCoolantTemp(),"EngineCoolantTemp",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _fuelPressure = CanData(_can.getFuelPressure(),"FuelPressure",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _intakeMAPressure = CanData(_can.getIntakeMAPressure(),"IntakeMAPressure",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _engineRPM = CanData(_can.getEngineRPM(),"EngineRPM",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _vehicleSpeed = CanData(_can.getVehicleSpeed(),"VehicleSpeed",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _timingAdvance = CanData(_can.getTimingAdvance(),"TimingAdvance",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _intakeAirTemp = CanData(_can.getIntakeAirTemp(),"IntakeAirTemp",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _mafAirFlowRate = CanData(_can.getMAFairFlowRate(),"MAFairFlowRate",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _throttlePosition = CanData(_can.getThrottlePosition(),"ThrottlePosition",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _fuelLevel = CanData(_can.getFuelLevel(),"FuelLevel",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _barometricPressure = CanData(_can.getBarometricPressure(),"BarometricPressurre",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _engineFuelRate = CanData(_can.getEngineFuelRate(),"EngineFuelRate",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());

       _listToPopulate.clear();
       _listToPopulate << _engineLoad << _engineCoolantTemp << _fuelPressure << _intakeMAPressure << _engineRPM
                       << _vehicleSpeed << _timingAdvance << _intakeAirTemp << _mafAirFlowRate << _throttlePosition
                       << _fuelLevel << _barometricPressure << _engineFuelRate;

       emit SendList(_listToPopulate);
    }

    void Controller::ControllerHandler()
    {
       GetCan();
       emit SubscribeWatchdogController(this);
       _canIntervalTimer->start(_intervalTimerInMs);
    }

}

