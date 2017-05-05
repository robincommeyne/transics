/*! \file */
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QMap>
#include <QTimer>

namespace cangateway
{
    class Watchdog : public QObject
    {
        Q_OBJECT
        public:
            Watchdog();

        private:
            QMap<QString, qint64> _subscriberList;
            QTimer *_watchdogTimer;
            const int _watchdogTimerValueInMs = 5000;
            bool event(QEvent *event);

        public slots:
            void WatchdogThread();
            void CheckTimestamps();
            void SoftwareRestart();
    };
}

#endif // WATCHDOG_H

