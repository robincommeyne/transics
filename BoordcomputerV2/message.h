/*! \file */
#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

namespace cangateway {

    class Message
    {
        public:
            Message(){}
            Message(QString _setType,QString _setContent,int _setTimestamp);

            QString Type(){return _type;}
            QString Content(){return _content;}
            int Timestamp(){return _timestamp;}

        private:
            QString _type;
            QString _content;
            int _timestamp;

    };

}

#endif // MESSAGE_H
