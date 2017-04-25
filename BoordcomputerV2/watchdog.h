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
            bool watchdogsubscriber(QEvent *event);

            QMap<QString, qint64> subscribers;
            QTimer *watchdogtimer;
            QDateTime timestamp;
            qint64 old_timestamp;
            int WatchdogTimerInMs = 5000;

        public slots:
            void Thread_Watchdog();
            void Check_Timestamps();
            void SoftwareRestart();
    };
}

#endif // WATCHDOG_H

