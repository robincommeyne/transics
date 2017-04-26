#ifndef WATCHDOGSUBSCRIBEREVENT_H
#define WATCHDOGSUBSCRIBEREVENT_H

#include <QEvent>
#include <QString>

namespace cangateway
{
    class WatchdogSubscribeEvent : public QEvent
    {
        public:
            static const QEvent::Type WATCHDOG = static_cast<QEvent::Type>(1001);

            WatchdogSubscribeEvent(): QEvent(WatchdogSubscribeEvent::WATCHDOG) {}

            void set_data(QString objectname){_objectname = objectname;}
            QString get_data() const { return _objectname; }

        private:
            QString _objectname;
    };

    //!< Describes watchdog subscribe event
}

#endif // WATCHDOGSUBSCRIBEREVENT_H
