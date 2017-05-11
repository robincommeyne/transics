#ifndef BLUETOOTH_H
#define BLUETOOTH_H


#include <qbluetoothserviceinfo.h>
#include <qbluetoothaddress.h>
#include "dispatcher.h"

#include <QtCore/QObject>
#include <QtCore/QList>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE


namespace cangateway {

    class Bluetooth: public QObject
    {
        Q_OBJECT
        public:

            explicit Bluetooth(QObject *parent = 0);
            ~Bluetooth();
            QList<QBluetoothSocket *> _clientSockets;

            void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
            void stopServer();
            void sendData(QString _deviceAddress, QByteArray _dataToSend);

        public slots:


        signals:

            void clientConnected(const QString &name);
            void clientDisconnected(const QString &name);

        private slots:
            void clientConnected();
            void clientDisconnected();

        private:

            QBluetoothServiceInfo _serviceInfo;
            QBluetoothServer *_rfcommServer;

     };
}
#endif // BLUETOOTH_H
