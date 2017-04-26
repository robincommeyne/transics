/*! \file */

#include "canData.h"

CanData::CanData(int value,QString description,int id,QString raw,int timestamp)
{
    /*! \todo create class constructor */
    Description = description;
    ID = id;
    RAW = raw;
    Value = value;
    Timestamp = timestamp;

}
CanData::CanData()
{

}
