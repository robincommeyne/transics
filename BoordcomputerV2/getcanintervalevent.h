#ifndef GETCANINTERVALEVENT_H
#define GETCANINTERVALEVENT_H

#include <QEvent>

namespace cangateway
{
    class GetCanIntervalEvent : public QEvent
    {
        public:
            static const QEvent::Type TYPE = static_cast<QEvent::Type>(1001);

            GetCanIntervalEvent(): QEvent(GetCanIntervalEvent::TYPE) {}

            void set_interval(int interval){_interval = interval;}
            int get_interval() const { return _interval; }

        private:
            int _interval;
    };

    //!< Describes getcan interval event
}
#endif // GETCANINTERVALEVENT_H
