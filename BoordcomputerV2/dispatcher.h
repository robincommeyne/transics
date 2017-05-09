/*! \file */
/*! Class to handle interfaces, receive and send data */

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include "config.h"
#include "canData.h"
#include "formatter.h"
#include "compression.h"

namespace cangateway
{

    typedef QList<CanData> CanDataList;

    class Dispatcher : public QObject
    {
        Q_OBJECT
        private:
            QTimer *_updatelisttimer;
            Formatter _formatter;
            QJsonDocument _jsondocument;
            QByteArray _bytearray;
            Compression _compression;
            QList<CanData> _filteredlist;
            QMap<QString,Config> _listofdevices;

        public slots:
            void DispatcherThread();
            void DeviceController();
            void ReceiveListFromController(CanDataList candata);

        signals:
            void SubscribeWatchdogDispatcher(QObject* object);

        public:
            Dispatcher();
            QList<CanData> _listfromcontroller;
            enum Receivers {bluetooth, filesystem, tcp};

            void SendData(
                    QString _deviceAddress, /**< QString containing address from device*/
                    Config _deviceConfig, /**< Config containing config linked with device address*/
                    Receivers _deviceReceiver /**< containing the receiver */
            );

            void DataReceived(
                    QFile ReceivedData /**< Qfile containing the received data */
            );

            void SendBluetooth(
                    QString _deviceAddress,
                    QByteArray _dataToSend /**< Qfile containing the data to send out */
            );
            //!< Sends Qfile out trough a bluetooth connection

            void ReceiveBluetooth();
            //!< Handles the incomming bluetooth files and triggers DataReceived event


            void SendFileSystem(
                    QFile &DataToStore, /**< File that needs to be stored */
                    QString SendFilePath /**< string specifying the local filepath to store the file */
            );
            //!< Stores the given file on the specified placed of the filesystem


            QFile& ReadFileSystem(
                    QString ReadFilePath /**< Filepath that needs to be read */

            );
            //!< reads a file from the specified filepath

            QList<CanData> GetFilteredListItem(
                    Config config,
                    QList<CanData> listtofilter
            );
            //!< Filters the list according to the filters contained in the object and sends back QList of CanData objects

    };
}

#endif // DISPATCHER_H

