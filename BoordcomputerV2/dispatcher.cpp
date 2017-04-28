/*! \file */
#include "dispatcher.h"
#include "watchdog.h"
#include "controller.h"
#include "compression.h"
#include "formatter.h"
#include "logging.h"
#include "config.h"
#include "watchdogsubscriberevent.h"

#include <QFile>
#include <QCoreApplication>
#include <QTimer>
#include <QObject>
#include "controller.h"



namespace cangateway {

    void Dispatcher::Thread_Dispatcher()
    {
        qDebug() << "Dispatcher thread started! Ready to process Events / Signals!: " << QThread::currentThread();

        this->setObjectName("Dispatcher");
        while(1)
        {
            QThread::msleep(1000);
            emit Subscribe_Watchdog_Dispatcher(this);
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

//    QObject Dispatcher::GetFilteredListItem(Config config)
//    {

//        /*! \todo implement function */
//    }

//    QFile Dispatcher::DeviceController(Config config)
//    {
//        /*! \todo implement function */
//    }
}

