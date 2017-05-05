#include "message.h"

namespace cangateway {

    Message::Message(QString _setType,QString _setContent,int _setTimestamp)
    {
        _type = _setType;
        _content = _setContent;
        _timestamp = _setTimestamp;
    }

}

