#include <QObject>
#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QApplication>
#include <QProcess>

#include "watchdog.h"
#include "watchdogsubscriberevent.h"

namespace cangateway {

    Watchdog::Watchdog()
    {
        _watchdogTimer = new QTimer(this);
        connect(_watchdogTimer, SIGNAL(timeout()), this, SLOT(CheckTimestamps()));
        _watchdogTimer->start(_watchdogTimerValueInMs);
    }

    bool Watchdog::event(QEvent* event)
    {
        if (event->type() == WatchdogSubscribeEvent::WATCHDOG)
        {
            WatchdogSubscribeEvent* _subscribeWatchdog = static_cast<WatchdogSubscribeEvent*>(event);
            _subscriberList.insert(_subscribeWatchdog->GetObjectName(),QDateTime::currentMSecsSinceEpoch());

            qDebug() << "Watchdog received event with data: "
                     << _subscribeWatchdog->GetObjectName()
                     << "in thread: " << QThread::currentThread();

            qDebug() << _subscriberList;

            return true;
        }
        return QObject::event(event);
    }

    void Watchdog::WatchdogThread()
    {
        qDebug() << "Watchdog thread started! Ready to process Events / Signals!: " << QThread::currentThread();
    }

    void Watchdog::CheckTimestamps()
    {
        for(auto value: _subscriberList.values())
        {
            if(QDateTime::currentMSecsSinceEpoch()-value > _watchdogTimerValueInMs)
                SoftwareRestart();
            else
                _watchdogTimer->start(_watchdogTimerValueInMs);
        }
    }

    void Watchdog::SoftwareRestart()
    {
        QStringList args = QApplication::arguments();
        args.removeFirst();
        QProcess::startDetached(QApplication::applicationFilePath(), args);
        QCoreApplication::quit();
    }

}

