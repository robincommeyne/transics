#include "watchdogsubscriberevent.h"
#include "watchdog.h"
#include "dispatcher.h"
#include "controller.h"
#include "manager.h"

namespace cangateway
{
    typedef QList<CanData> CanDataList;

    Manager::Manager(QObject* app): _manager(app), _watchdogThread(nullptr), _dispatcherThread(nullptr), _controllerThread(nullptr)
    {
        qRegisterMetaType<CanDataList>("CanDataList");
    }

    void Manager::Init()
    {
        qDebug() << "starting all threads from main: " << QThread::currentThread();
        CreateWatchdogThread();
        CreateDispatcherThread();
        CreateControllerThread();
    }

    void Manager::SubscribeWatchdog(QObject* object)
    {
        qDebug() << "subscribe watchdog slot is called " << QThread::currentThread();
        WatchdogSubscribeEvent* event = new WatchdogSubscribeEvent();
        event->SetObjectName(object->objectName());

        QCoreApplication::postEvent(_watchdog, event,Qt::QueuedConnection);
    }

    void Manager::CreateWatchdogThread()
    {
        _watchdogThread = new QThread();
        _watchdog = new Watchdog();
        _watchdog->moveToThread(_watchdogThread);

        connect(_watchdogThread, &QThread::started, _watchdog, &Watchdog::WatchdogThread);
        _watchdogThread->start();
    }

    void Manager::CreateDispatcherThread()
    {
        _dispatcherThread = new QThread();
        _dispatcher = new Dispatcher();
        _dispatcher->moveToThread(_dispatcherThread);

        connect(_dispatcherThread, &QThread::started, _dispatcher, &Dispatcher::Thread_Dispatcher);
        connect(_dispatcher, SIGNAL(Subscribe_Watchdog_Dispatcher(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        _dispatcherThread->start();
    }

    void Manager::CreateControllerThread()
    {
        _controllerThread = new QThread();
        _controller = new Controller();
        _controller->moveToThread(_controllerThread);

        connect(_controllerThread, &QThread::started, _controller, &Controller::Thread_Controller);
        connect(_controller, SIGNAL(Subscribe_Watchdog_Controller(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        connect(_controller, SIGNAL(Send_List(CanDataList)),_dispatcher,SLOT(List_Receiver_From_Controller(CanDataList)));
        _controllerThread->start();
    }
}
