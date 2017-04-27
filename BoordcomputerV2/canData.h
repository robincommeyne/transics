/*! \file */
/*! Class containing all properties that can be read from the Can library */
#ifndef CANDATA_H
#define CANDATA_H

#include <QString>




class CanData
{


    public:
    QString Description;
    int ID;
    QString RAW;
    int Value;
    int Timestamp;

        CanData(int,QString,int,QString,int);
        CanData();

};

#endif // CANDATA_H
