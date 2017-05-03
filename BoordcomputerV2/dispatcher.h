/*! \file */
/*! Class to handle interfaces, receive and send data */
#include <QString>
#include <QObject>
#include <QFile>
#include <QtCore>
#include <QList>
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
            QFile DataToSend;
            QFile ReceivedData;
            QString SendFilepath;
            QString ReadFilePath;
            Config configfrombluetooth;
            QTimer *updatelisttimer;
            Formatter formatter;
            QJsonDocument jsondocument;
            QByteArray bytearray;
            Compression compression;
            QList<CanData> filteredlist;


        public slots:
            void Thread_Dispatcher();
            void TimerThread();
            void List_Receiver_From_Controller(CanDataList candata);
        signals:
            void Subscribe_Watchdog_Dispatcher(QObject* object);

        public:
            Dispatcher();
            QList<CanData> listfromcontroller;
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

            QList<CanData> GetFilteredListItem(
                    Config config,
                    QList<CanData> listtofilter
            );
            //!< Filters the list according to the filters contained in the object and sends back QList of CanData objects


            QFile DeviceController(
                    Config config /**< Object from the Config class */
            );
            //!< Receives Objects of the Config class and keeps track of number of devices, limiting them to a maximum of 2 and returns compressed file to send.
    };
}

