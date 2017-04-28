/*! \file */
/*! Class to handle interfaces, receive and send data */
#include <QString>
#include <QObject>
#include <QFile>
#include <QtCore>
#include <QList>
#include "config.h"
#include "canData.h"

typedef QList<CanData> CanDataList;

namespace cangateway
{
    class Dispatcher : public QObject
    {
        Q_OBJECT
        private:
            QFile DataToSend;
            QFile ReceivedData;
            QString SendFilepath;
            QString ReadFilePath;
            Config config;
            QTimer *updatelisttimer;

        public slots:
            void Thread_Dispatcher();
            void UpdateList();
            void List_Receiver_From_Controller(CanDataList candata);
        signals:
            void Subscribe_Watchdog_Dispatcher(QObject* object);

        public:
            Dispatcher();
            QList<CanData> grotelijst;
            void DataReceived(
                    QFile ReceivedData /**< Qfile containing the received data */
            );

            void SendBluetooth(
                    QFile DataToSend /**< Qfile containing the data to send out */
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

            QObject GetFilteredListItem(
                    Config config /**< Object from the Config class */
            );
            //!< Filters the list according to the filters contained in the object and sends back CanData class object


            QFile DeviceController(
                    Config config /**< Object from the Config class */
            );
            //!< Receives Objects of the Config class and keeps track of number of devices, limiting them to a maximum of 2 and returns compressed file to send.
    };
}

