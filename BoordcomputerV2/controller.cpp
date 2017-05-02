#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"
#include "dispatcher.h"

namespace cangateway {

    Controller::Controller()
    {
        canintervaltimer = new QTimer(this);
        connect(canintervaltimer, SIGNAL(timeout()), this, SLOT(TimerElapsed()));
        canintervaltimer->start(1000);
    }

    void Controller::Thread_Controller()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
    }

    void Controller::InitCan()
    {
        can.ON();
        can.begin();
    }

    void Controller::GetCan()
    {
       qDebug() << "GetCan is called";
       CanData EngineLoad;
       CanData CoolantTemp;

       EngineLoad = CanData(can.getEngineLoad(),"EngineLoad",can.getID(),can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       CoolantTemp = CanData(can.getEngineCoolantTemp(),"EngineCoolantTemp",can.getID(),can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       //alle paramaters komen hier

       ListToPopulate << EngineLoad << CoolantTemp;

       emit Send_List(ListToPopulate);
    }

    void Controller::TimerElapsed()
    {
       GetCan();
       emit Subscribe_Watchdog_Controller(this);
       canintervaltimer->start(1000);
    }

}

