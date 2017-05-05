#ifndef WATCHDOGSUBSCRIBEREVENT_H
#define WATCHDOGSUBSCRIBEREVENT_H

#include <QEvent>
#include <QString>

namespace cangateway
{
    class WatchdogSubscribeEvent : public QEvent
    {
        public:
            WatchdogSubscribeEvent(): QEvent(WatchdogSubscribeEvent::WATCHDOG) {}
            static const QEvent::Type WATCHDOG = static_cast<QEvent::Type>(1001);

            void SetObjectName(QString objectname){_objectname = objectname;}
            QString GetObjectName() const { return _objectname;}

        private:
            QString _objectname;
    };

    //!< Describes watchdog subscribe event
}

#endif // WATCHDOGSUBSCRIBEREVENT_H
