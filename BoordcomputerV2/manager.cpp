#include "watchdogsubscriberevent.h"
#include "watchdog.h"
#include "dispatcher.h"
#include "controller.h"
#include "manager.h"

namespace cangateway
{
    typedef QList<CanData> CanDataList;

    Manager::Manager(QObject* app): _manager(app), _watchdogThread(nullptr), _dispatcherThread(nullptr), _controllerThread(nullptr), _bluetoothThread(nullptr)
    {
        qRegisterMetaType<CanDataList>("CanDataList");
    }

    void Manager::Init()
    {
        qDebug() << "starting all threads from main: " << QThread::currentThread();
        CreateWatchdogThread();
        CreateDispatcherThread();
        CreateControllerThread();
        CreateBluetoothThread();

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

        connect(_dispatcherThread, &QThread::started, _dispatcher, &Dispatcher::DispatcherThread);
        connect(_dispatcher, SIGNAL(SubscribeWatchdogDispatcher(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        _dispatcherThread->start();
    }

    void Manager::CreateControllerThread()
    {
        _controllerThread = new QThread();
        _controller = new Controller();
        _controller->moveToThread(_controllerThread);

        connect(_controllerThread, &QThread::started, _controller, &Controller::ControllerThread);
        connect(_controller, SIGNAL(SubscribeWatchdogController(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        connect(_controller, SIGNAL(SendList(CanDataList)),_dispatcher,SLOT(ReceiveListFromController(CanDataList)));
        _controllerThread->start();
    }

    void Manager::CreateBluetoothThread()
    {
        _bluetoothThread = new QThread();
        _bluetooth = new Bluetooth();
        _bluetooth->moveToThread(_bluetoothThread);

        connect(_bluetoothThread, &QThread::started, _bluetooth, &Bluetooth::BluetoothThread);
        connect(_bluetooth, SIGNAL(SubscribeWatchdogBluetooth(QObject*)),this, SLOT(SubscribeWatchdog(QObject*)));
        _bluetoothThread->start();

    }
}
