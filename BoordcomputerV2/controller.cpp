/*! \file */ 
#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"
#include "getcanintervalevent.h"

namespace cangateway {

    void Controller::Thread_Controller()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
        while(1)
        {
            QThread::msleep(2000);
            emit Subscribe_Watchdog_Controller(this);
        }

    }

    bool Controller::event(QEvent* event)
    {
        if (event->type() == GetCanIntervalEvent::TYPE)
        {
            GetCanIntervalEvent* set_caninterval = static_cast<GetCanIntervalEvent*>(event);

            qDebug() << "Controller received can interval: " << set_caninterval->get_interval()
                     << "in thread: " << QThread::currentThread();

            return true;
        }

        return QObject::event(event);
    }

    void Controller::InitCan()
    {

        can.ON();
        can.begin();
    }

    void Controller::GetCan(int Interval)
    {

            CanData EngineLoad = CanData();
            CanData CoolantTemp = CanData();

            EngineLoad = CanData(can.getEngineLoad(),"EngineLoad",can.getID(),can.getRawMessage(),Timestamp);
            CoolantTemp = CanData(can.getEngineCoolantTemp(),"EngineCoolantTemp",can.getID(),can.getRawMessage(),Timestamp);

            PopulateList(EngineLoad);
            PopulateList(CoolantTemp);

    }

    void Controller::PopulateList(CanData candata)
    {
        QList<CanData> canDataList;
        /*! \todo implement function */

        if (ListItemCounter < MaxListItems)
        {
            canDataList[ListItemCounter] = candata;
            ListItemCounter = ListItemCounter + 1;
        }
        else
        {
            ListItemCounter = 0;
            canDataList[ListItemCounter] = candata;
        }
    }


}

