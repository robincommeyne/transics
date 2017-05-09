#include "canData.h"

namespace cangateway {

    CanData::CanData(int setValue,QString setDescription,int setId,QString setRaw,int setTimeStamp)
    {
        _value = setValue;
        _description = setDescription;
        _id = setId;
        _raw = setRaw;
        _timestamp = setTimeStamp;
    }

}

