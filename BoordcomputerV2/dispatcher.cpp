/*! \file */
#include <QtConcurrent/QtConcurrent>
#include "dispatcher.h"

namespace cangateway {

    Dispatcher::Dispatcher()
    {
        _updatelisttimer = new QTimer(this);
        connect(_updatelisttimer, SIGNAL(timeout()), this, SLOT(DeviceController()));
        _updatelisttimer->start(1000);
    }

    void Dispatcher::DispatcherThread()
    {
        qDebug() << "Dispatcher thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Dispatcher");
    }

    void Dispatcher::DeviceController()
    {
        //qmap overlopen waar devices samen met hun configs inzitten
        //deze qmap moet opgemaakt worden via de ontvangen bluetooth
        for(auto key : _listofdevices.keys())
        {
            QFuture<void> future = QtConcurrent::run(this,&Dispatcher::SendData,key,_listofdevices.value(key),bluetooth);
            future.waitForFinished();
        }

        emit SubscribeWatchdogDispatcher(this);
        _updatelisttimer->start(1000);
    }

    void Dispatcher::SendData(QString _deviceAddress, Config _deviceConfig, Receivers _deviceReceiver)
    {
        switch(_deviceReceiver)
        {
            case bluetooth:
                _jsondocument = _formatter.ToJsonDocument(GetFilteredListItem(_deviceConfig,_listfromcontroller));
                _compression.Zip(_jsondocument.toBinaryData(),_bytearray);
                SendBluetooth(_deviceAddress,_bytearray);
                break;
            case filesystem:
                //SendFileSystem();
                break;
            case tcp:
                //SendTCP();
                break;
        }
    }

    void Dispatcher::ReceiveListFromController(CanDataList candata)
    {
        qDebug() << "List Receiver From Controller is called";
        if(_listfromcontroller.length()+candata.length()>1000)
        {
            int difference = _listfromcontroller.length()+candata.length()-1000;
            for(int i=0; i<difference; ++i)
            {
                _listfromcontroller.removeFirst();
            }
        }
        else
        {
            _listfromcontroller.append(candata);
        }
    }

//    void Dispatcher::DataReceived(QFile ReceivedData)
//    {
//        /*! \todo implement function */
//    }

    void Dispatcher::SendBluetooth(QString _deviceAddress, QByteArray _dataToSend)
    {
        /*! \todo implement function */
    }

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
                        if(listtofilter[i].Timestamp() % config.get_readinterval() == 0)
                        {
                            _filteredlist.append(listtofilter[i]);
                        }
                    }

                }
            }
        }

        return _filteredlist;
    }

}

