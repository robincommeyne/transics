#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"
#include "dispatcher.h"

namespace cangateway {

    Controller::Controller()
    {
        _canIntervalTimer = new QTimer(this);
        connect(_canIntervalTimer, SIGNAL(timeout()), this, SLOT(ControllerHandler()));
        _canIntervalTimer->start(1000);
    }

    void Controller::ControllerThread()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
    }

    void Controller::InitCan()
    {
        _can.ON();
        _can.begin();
    }

    void Controller::GetCan()
    {
       qDebug() << "GetCan is called";

       _engineLoad = CanData(_can.getEngineLoad(),"EngineLoad",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       _coolantTemp = CanData(_can.getEngineCoolantTemp(),"EngineCoolantTemp",_can.getID(),_can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       //alle paramaters komen hier

       _listToPopulate << _engineLoad << _coolantTemp;

       emit SendList(_listToPopulate);
    }

    void Controller::ControllerHandler()
    {
       GetCan();
       emit SubscribeWatchdogController(this);
       _canIntervalTimer->start(1000);
    }

}

