/*! \file */
#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

namespace cangateway
{
    class Watchdog;
    class Controller;
    class Dispatcher;

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

            QThread* _watchdogThread;
            QThread* _dispatcherThread;
            QThread* _controllerThread;

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
