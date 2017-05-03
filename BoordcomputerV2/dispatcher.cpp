/*! \file */
#include "dispatcher.h"
#include "watchdog.h"
#include "controller.h"
#include "compression.h"
#include "formatter.h"
#include "logging.h"
#include "config.h"

#include <QFile>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>
#include "controller.h"

namespace cangateway {

    Dispatcher::Dispatcher()
    {
        updatelisttimer = new QTimer(this);
        connect(updatelisttimer, SIGNAL(timeout()), this, SLOT(TimerThread()));
        updatelisttimer->start(1000);
    }

    void Dispatcher::Thread_Dispatcher()
    {
        qDebug() << "Dispatcher thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Dispatcher");
    }

    void Dispatcher::TimerThread()
    {
        jsondocument = formatter.ToJsonDocument(GetFilteredListItem(configfrombluetooth,listfromcontroller));
        compression.Zip(jsondocument.toBinaryData(),bytearray);
        //1* bytearray meegeven naar bluetooth of naar filesystem
        emit Subscribe_Watchdog_Dispatcher(this);
        updatelisttimer->start(1000);
    }

    void Dispatcher::List_Receiver_From_Controller(CanDataList candata)
    {
        qDebug() << "List Receiver From Controller is called";
        if(listfromcontroller.length()<1000)
        {
            listfromcontroller.append(candata);
        }
        else
        {
            for(int i=0; i<candata.length(); ++i)
            {
                listfromcontroller.removeFirst();
            }

            listfromcontroller.append(candata);
        }
    }

//    void Dispatcher::DataReceived(QFile ReceivedData)
//    {
//        /*! \todo implement function */
//    }

//    void Dispatcher::SendBluetooth(QFile DataToSend)
//    {
//        /*! \todo implement function */
//    }

//    void Dispatcher::ReceiveBluetooth()
//    {
//        /*! \todo implement function */
//    }

    void Dispatcher::SendFileSystem(QFile &DataToStore,QString SendFilePath)
    {
        QFile hulpfile(SendFilePath);
        DataToStore.open(QIODevice::ReadOnly);
        QByteArray dataArray = DataToStore.readAll();
        hulpfile.open(QIODevice::WriteOnly);
        hulpfile.write(dataArray);
        hulpfile.close();
    }

    QFile& Dispatcher::ReadFileSystem(QString ReadFilePath)
    {
        QFile readfile(ReadFilePath);
        return readfile;
    }

    QList<CanData> Dispatcher::GetFilteredListItem(Config config,QList<CanData> listtofilter)
    {
        for(auto e : config.get_configmap().keys())
        {
            if(config.get_configmap().value(e))
            {
                for(int i=0; i<listtofilter.length(); ++i)
                {
                    if(listtofilter[i].Description() == e)
                    {
                        if(listtofilter[i].Timestamp()/1000 % config.get_readinterval() == 0)
                        {
                            filteredlist.append(listtofilter[i]);
                        }
                    }

                }
            }
        }

        return filteredlist;
    }

//    QFile Dispatcher::DeviceController(Config config)
//    {
//        /*! \todo implement function */
//    }
}

