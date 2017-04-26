#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QDateTime>
#include <QApplication>
#include <QProcess>
#include "watchdog.h"
#include "watchdogsubscriberevent.h"

namespace cangateway {

    Watchdog::Watchdog()
    {
        timestamp = QDateTime::currentDateTime();

        watchdogtimer = new QTimer(this);
        connect(watchdogtimer, SIGNAL(timeout()), this, SLOT(Check_Timestamps()));
        watchdogtimer->start(WatchdogTimerInMs);
    }

    bool Watchdog::event(QEvent* event)
    {
        if (event->type() == WatchdogSubscribeEvent::WATCHDOG)
        {
            WatchdogSubscribeEvent* subscribe_watchdog = static_cast<WatchdogSubscribeEvent*>(event);

            qDebug() << "Watchdog received event with data: " << subscribe_watchdog->get_data()
                     << "in thread: " << QThread::currentThread();

            subscribers.insert(subscribe_watchdog->get_data(),QDateTime::currentMSecsSinceEpoch());

            qDebug() << subscribers;

            return true;
        }

        return QObject::event(event);
    }

    void Watchdog::Thread_Watchdog()
    {
        qDebug() << "Watchdog thread started! Ready to process Events / Signals!: " << QThread::currentThread();

    }

    void Watchdog::Check_Timestamps()
    {
        for(auto value: subscribers.values())
        {
            if(QDateTime::currentMSecsSinceEpoch()-value > WatchdogTimerInMs)
                SoftwareRestart();
            else
                watchdogtimer->start(WatchdogTimerInMs);
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

