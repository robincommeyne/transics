#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


class Message
{


private:

    QString type;
    QString content;
    int timestamp;

public:
    Message();
    Message(QString SetType,QString SetContent,int SetTimestamp);

    QString Type(){return type;}
    QString Content(){return content;}
    QString Timestamp(){return timestamp;}





};

#endif // MESSAGE_H
