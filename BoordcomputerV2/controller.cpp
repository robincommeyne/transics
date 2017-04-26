/*! \file */ 
#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"
#include "getcanintervalevent.h"

namespace cangateway {

    Controller::Controller()
    {
        canintervaltimer = new QTimer(this);
        connect(canintervaltimer, SIGNAL(timeout()), this, SLOT(PopulateCanData()));
        canintervaltimer->start(1000);
        //canintervaltimer->start(get_timer);
    }

    void Controller::Thread_Controller()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
//        while(1)
//        {
//            //QThread::msleep(2000);
//            GetCan();
//            emit Subscribe_Watchdog_Controller(this);
//        }
        QThread::msleep(2000);
        GetCan();
    }

    bool Controller::event(QEvent* event)
    {
        if (event->type() == GetCanIntervalEvent::TYPE)
        {
            GetCanIntervalEvent* set_caninterval = static_cast<GetCanIntervalEvent*>(event);

            qDebug() << "Controller received can interval: " << set_caninterval->get_interval()
                     << "in thread: " << QThread::currentThread();

            set_timer(set_caninterval->get_interval());
            return true;
        }

        return QObject::event(event);
    }

    void Controller::InitCan()
    {
        can.ON();
        can.begin();
    }

    void Controller::GetCan()
    {
       qDebug() << "GetCan is called";
       CanData EngineLoad = CanData();
       CanData CoolantTemp = CanData();

       EngineLoad = CanData(can.getEngineLoad(),"EngineLoad",can.getID(),can.getRawMessage(),QDateTime::currentSecsSinceEpoch());
       CoolantTemp = CanData(can.getEngineCoolantTemp(),"EngineCoolantTemp",can.getID(),can.getRawMessage(),QDateTime::currentSecsSinceEpoch());

       ListToPopulate << EngineLoad << CoolantTemp;
    }

    void Controller::PopulateList(CanData candata)
    {
        QList<CanData> canDataList;
        //lijst moet globaal worden doorsturen met event ?

        if (ListItemCounter < MaxListItems)
        {
            canDataList.append(candata);
            ListItemCounter = ListItemCounter + 1;
        }
        else
        {
            ListItemCounter = 0;
            canDataList[ListItemCounter] = candata;
        }
    }

    void Controller::PopulateCanData()
    {
        qDebug() << "PopulateCanData is called";
        for(int i=0; i<ListToPopulate.length(); i++)
        {
            PopulateList(ListToPopulate[i]);
        }
    }


}

