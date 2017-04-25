/*! \file */ 
#include "controller.h"
#include "watchdog.h"
#include "logging.h"
#include "canData.h"

namespace cangateway {

    void Controller::Thread_Controller()
    {
        qDebug() << "Controller thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Controller");
        while(1)
        {
            QThread::msleep(7000);
            emit Subscribe_Watchdog_Controller(this);
        }

    }

    void Controller::InitCan()
    {
        /*! \todo implement function */
    }

    void Controller::GetCan(int Interval)
    {
        //    Controller controller;
        //    int timestamp = 0;

        //    CanData EngineLoad = CanData("",0,"",0,0);
        //    CanData CoolantTemp = CanData("",0,"",0,0);;
        //    while(true)
        //    {
        //           EngineLoad = CanData("EngineLoad",CanReader.messageRx.id,controller.Int2String(CanReader.messageRx.data),CanReader.getEngineLoad(),timestamp);
        //           CoolantTemp = CanData("EngineCoolantTemp",CanReader.messageRx.id,controller.Int2String(CanReader.messageRx.data),CanReader.getEngineCoolantTemp(),timestamp);
        //       PopulateList(EngineLoad);
        //       PopulateList(CoolantTemp);
        //    }
    }

    void Controller::PopulateList(CanData candata)
    {
        /*! \todo implement function */
    }

    QString Controller::Int2String(uint8_t x[])
    {
        QString returnstring = "";
            for (int i=0; i < 8; i++)
            {
                returnstring.append(QString::number(x[i]));

            }
            return returnstring;
    }
}

