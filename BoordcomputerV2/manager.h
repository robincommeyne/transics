#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDateTime>
#include <QString>

class QThread;

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
        public slots:
            void Init();
        private slots:
            void SubscribeWatchdog(QObject* object);
            void SetCanInterval(int interval);

        private:
            QObject* _app;

            Watchdog* watchdog_thread_object;
            Controller* controller_thread_object;
            Dispatcher* dispatcher_thread_object;

            QThread* thread_watchdog;
            QThread* thread_dispatcher;
            QThread* thread_controller;

            void create_watchdog_thread();
            void create_dispatcher_thread();
            void create_controller_thread();
    };
}

#endif // MANAGER_H
