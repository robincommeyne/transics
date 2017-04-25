/*! \file */

#include "canData.h"

CanData::CanData(QString description,int id,QString raw,int value,int timestamp)
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
