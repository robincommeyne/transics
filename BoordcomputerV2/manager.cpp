#include "manager.h"

#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include <QObject>

#include "watchdogsubscriberevent.h"
#include "getcanintervalevent.h"
#include "watchdog.h"
#include "dispatcher.h"
#include "controller.h"

namespace cangateway
{
    Manager::Manager(QObject* app)
        : _app(app)
        , thread_watchdog(nullptr)
        , thread_dispatcher(nullptr)
        , thread_controller(nullptr)
    {
    }

    void Manager::Init()
    {
        qDebug() << "Starting new threads from main: " << QThread::currentThread();
        create_watchdog_thread();
        create_dispatcher_thread();
        create_controller_thread();
        SetCanInterval(1000);
    }

    void Manager::SetCanInterval(int interval)
    {
        qDebug() << "SetCanInterval slot is called " << QThread::currentThread();
        GetCanIntervalEvent* event = new GetCanIntervalEvent();
        event->set_interval(interval);

        QCoreApplication::postEvent(controller_thread_object, event,Qt::QueuedConnection);
    }

    void Manager::SubscribeWatchdog(QObject* object)
    {
        qDebug() << "SubscribeWatchdog slot is called " << QThread::currentThread();
        WatchdogSubscribeEvent* event = new WatchdogSubscribeEvent();
        event->set_data(object->objectName());

        QCoreApplication::postEvent(watchdog_thread_object, event,Qt::QueuedConnection);
    }

    void Manager::create_watchdog_thread()
    {
        thread_watchdog = new QThread();
        watchdog_thread_object = new Watchdog();
        watchdog_thread_object->moveToThread(thread_watchdog);

        connect(thread_watchdog, &QThread::started, watchdog_thread_object, &Watchdog::Thread_Watchdog);
        thread_watchdog->start();
    }

    void Manager::create_dispatcher_thread()
    {
        thread_dispatcher = new QThread();
        dispatcher_thread_object = new Dispatcher();
        dispatcher_thread_object->moveToThread(thread_dispatcher);

        connect(thread_dispatcher, &QThread::started, dispatcher_thread_object, &Dispatcher::Thread_Dispatcher);
        connect(dispatcher_thread_object, SIGNAL(Subscribe_Watchdog_Dispatcher(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        thread_dispatcher->start();

    }

    void Manager::create_controller_thread()
    {
        thread_controller = new QThread();
        controller_thread_object = new Controller();
        controller_thread_object->moveToThread(thread_controller);

        connect(thread_controller, &QThread::started, controller_thread_object, &Controller::Thread_Controller);
        connect(controller_thread_object, SIGNAL(Subscribe_Watchdog_Controller(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        thread_controller->start();

    }
}
