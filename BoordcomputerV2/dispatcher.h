/*! \file */
/*! Class to handle interfaces, receive and send data */

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QtCore>
#include "config.h"
#include "canData.h"
#include "formatter.h"
#include "compression.h"
#include "bluetooth.h"

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
            Compression _compression;
            QList<CanData> _filteredlist;
            QMap<QString,Config> _listofdevices;
            const int _intervalTimerInMs = 1000;
            const int _unfilteredListSize = 1000;

        public slots:
            void DispatcherThread();
            void DeviceController();
            void ReceiveListFromController(CanDataList candata);
            void DataReceived();

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



            void SendBluetooth(
                    QString _deviceAddress,
                    QByteArray _dataToSend /**< Qfile containing the data to send out */
            );
            //!< Sends Qfile out trough a bluetooth connection

            void DeviceConnected();
            //!< Is called by a connection to a device to fill in the list of connected devices


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

