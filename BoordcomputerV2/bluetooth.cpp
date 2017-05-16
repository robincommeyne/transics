#include "bluetooth.h"

#include <qbluetoothserver.h>
#include <qbluetoothsocket.h>
#include <qbluetoothlocaldevice.h>
#include <QBluetoothDeviceInfo>

namespace cangateway {

    static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

    Bluetooth::Bluetooth(QObject *parent):QObject(parent), _rfcommServer(0)
    {
        _bluetoothTimer = new QTimer(this);
        connect(_bluetoothTimer, SIGNAL(timeout()), this, SLOT(BluetoothHandler()));
        _bluetoothTimer->start(_intervalTimerInMs);
        //_dispatcher = new Dispatcher();
    }

    Bluetooth::~Bluetooth()
    {
        stopServer();
    }

    void Bluetooth::BluetoothThread()
    {
        qDebug() << "Bluetooth thread started! Ready to process Events / Signals!: " << QThread::currentThread();
        this->setObjectName("Bluetooth");

        if(_localDevice.isValid()){
            _localDevice.powerOn();
            qDebug() << "bluetooth powered on";

            _localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

            startServer(_localDevice.address());
        }
        else
            qDebug() << "no bluetooth controller";


    }

    void Bluetooth::BluetoothHandler()
    {
        //hier alles afhandelen om de 1s

        emit SubscribeWatchdogBluetooth(this);
        _bluetoothTimer->start(_intervalTimerInMs);
    }

    void Bluetooth::startServer(const QBluetoothAddress& localAdapter)
    {
        if (_rfcommServer)
            return;

        _rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
        connect(_rfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

        bool result = _rfcommServer->listen(localAdapter);
        if (!result) {
            qWarning() << "Cannot bind server to" << localAdapter.toString();
            return;
        }

        //serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceRecordHandle, (uint)0x00010010);

        QBluetoothServiceInfo::Sequence classId;

        classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
        _serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
                                 classId);

        classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

        _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
        _serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,classId);

        _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("CAN data server"));
        _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                                 tr("Provide CAN data to mobile device"));
        _serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("Transics"));

        _serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));



        QBluetoothServiceInfo::Sequence publicBrowse;
        publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
        _serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                                 publicBrowse);

        QBluetoothServiceInfo::Sequence protocolDescriptorList;
        QBluetoothServiceInfo::Sequence protocol;
        protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
        protocolDescriptorList.append(QVariant::fromValue(protocol));
        protocol.clear();
        protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
                 << QVariant::fromValue(quint8(_rfcommServer->serverPort()));
        protocolDescriptorList.append(QVariant::fromValue(protocol));
        _serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                                 protocolDescriptorList);

        _serviceInfo.registerService(localAdapter);

        qDebug() << "Dervice created on"
                 << _serviceInfo.device().name() << _serviceInfo.device().address().toString();
        qDebug() << "\tService name:" << _serviceInfo.serviceName();
        qDebug() << "\tDescription:"
                 << _serviceInfo.attribute(QBluetoothServiceInfo::ServiceDescription).toString();
        qDebug() << "\tProvider:"
                 << _serviceInfo.attribute(QBluetoothServiceInfo::ServiceProvider).toString();
        qDebug() << "\tL2CAP protocol service multiplexer:"
                 << _serviceInfo.protocolServiceMultiplexer();
        qDebug() << "\tRFCOMM server channel:" << _serviceInfo.serverChannel();

        qDebug() << "server started";
    }

    void Bluetooth::stopServer()
    {
        // Unregister service
        _serviceInfo.unregisterService();

        // Close sockets
        qDeleteAll(_clientSockets);

        // Close server
        delete _rfcommServer;
        _rfcommServer = 0;
    }

    void Bluetooth::sendData(QString _deviceAddress, QByteArray _dataToSend)
        {
            QBluetoothAddress address(_deviceAddress);

            for( int i=0;i<_clientSockets.length();i++)
            {
                if (_clientSockets[i]->peerAddress() == address)
                {
                    _clientSockets[i]->write(_dataToSend);
                }
                if (!_clientSockets[i]->bytesToWrite() == 0)
                {
                    qDebug() << "not all bytes written";
                }
            }


        }

    void Bluetooth::clientConnected()
    {
        qDebug() << "client connected";
        QBluetoothSocket *socket = _rfcommServer->nextPendingConnection();
        if (!socket)
            return;

        connect(socket, SIGNAL(readyRead()), this, SLOT(DataReceived()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
        _clientSockets.append(socket);
        emit clientConnected(socket->peerName());
        qDebug() << "Adress: " << socket->peerAddress();
        qDebug() << "Name: " << socket->peerName();
    }

    void Bluetooth::clientDisconnected()
    {
        QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
        if (!socket)
            return;

        emit clientDisconnected(socket->peerName());

        _clientSockets.removeOne(socket);

        socket->deleteLater();
        qDebug() <<"client disconnected";
    }
    void Bluetooth::DataReceived()
    {
        qDebug() << "Reading Socket...";
        QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
        if (!socket)
            return;

        //while (socket->canReadLine()) {
            QByteArray line = socket->readLine().trimmed();

            qDebug() << socket->peerAddress() << QString::fromUtf8(line.constData(), line.length());

         emit SendReceivedData(socket->peerAddress().toString(),line);



    }


}

