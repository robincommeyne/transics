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
        connect(updatelisttimer, SIGNAL(timeout()), this, SLOT(UpdateList()));
        updatelisttimer->start(1000);
    }

    void Dispatcher::Thread_Dispatcher()
    {
        qDebug() << "Dispatcher thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Dispatcher");
    }

    void Dispatcher::UpdateList()
    {
        emit Subscribe_Watchdog_Dispatcher(this);
        updatelisttimer->start(1000);
    }

    void Dispatcher::List_Receiver_From_Controller(CanDataList candata)
    {
        qDebug() << "List Receiver From Controller is called";
        //hier wordt lijst ontvangen van controller

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

//    }

//    QFile Dispatcher::DeviceController(Config config)
//    {
//        /*! \todo implement function */
//    }
}

