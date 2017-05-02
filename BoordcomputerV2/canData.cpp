#include "canData.h"

namespace cangateway {

    CanData::CanData()
    {

    }

    CanData::CanData(int setValue,QString setDescription,int setId,QString setRaw,int setTimeStamp)
    {
        value = setValue;
        description = setDescription;
        id = setId;
        raw = setRaw;
        timestamp = setTimeStamp;
    }

}

