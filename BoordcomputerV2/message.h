#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


class Message
{


public:

    QString Type;
    QString Content;
    int Timestamp;
    Message(QString,QString,int);

};

#endif // MESSAGE_H
