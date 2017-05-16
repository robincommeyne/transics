#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "bluetooth.h"



namespace cangateway
{
    class Watchdog;
    class Controller;
    class Dispatcher;
    class Logging;

    class Manager : public QObject
    {
        Q_OBJECT
        public:
            explicit Manager(QObject* app);

        private:
            QObject* _manager;

            Watchdog* _watchdog;
            Controller* _controller;
            Dispatcher* _dispatcher;
            Bluetooth* _bluetooth;
            Logging* _logging;

            QThread* _watchdogThread;
            QThread* _dispatcherThread;
            QThread* _controllerThread;
            QThread* _bluetoothThread;

            void CreateBluetoothThread();
            void CreateWatchdogThread();
            void CreateDispatcherThread();
            void CreateControllerThread();

        public slots:
            void Init();

        private slots:
            void SubscribeWatchdog(QObject* object);
    };
}

#endif // MANAGER_H
