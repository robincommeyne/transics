/*! \file */
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QDateTime>
#include <QObject>
#include <QTimer>
#include <QMap>

namespace cangateway
{
    class Watchdog : public QObject
    {
        Q_OBJECT
        public:
            Watchdog();
            bool event(QEvent *event);

            QMap<QString, qint64> subscribers;
            QTimer *watchdogtimer;
            int WatchdogTimerInMs = 5000;

        public slots:
            void Thread_Watchdog();
            void Check_Timestamps();
            void SoftwareRestart();
    };
}

#endif // WATCHDOG_H

