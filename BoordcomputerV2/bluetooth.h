#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <qbluetoothserviceinfo.h>
#include <qbluetoothaddress.h>
#include "dispatcher.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QBluetoothLocalDevice>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

namespace cangateway {

    class Dispatcher;

    class Bluetooth: public QObject
    {
        Q_OBJECT
        public:

            explicit Bluetooth(QObject *parent = 0);
            ~Bluetooth();
            QList<QBluetoothSocket *> _clientSockets;

            void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
            void stopServer();

        public slots:
            void BluetoothThread();

        signals:
            void SubscribeWatchdogBluetooth(QObject* object);
            void clientConnected(const QString &name);
            void clientDisconnected(const QString &name);
            void SendReceivedData(QString,QByteArray);

        private slots:
            void BluetoothHandler();
            void clientConnected();
            void clientDisconnected();
            void DataReceived();
            void sendData(QString _deviceAddress, QByteArray _dataToSend);

        private:
            QBluetoothServiceInfo _serviceInfo;
            QBluetoothServer *_rfcommServer;
            QTimer *_bluetoothTimer;
            Dispatcher* _dispatcher;
            QBluetoothLocalDevice _localDevice;
            const int _intervalTimerInMs = 1000;

     };
}
#endif // BLUETOOTH_H
