/*! \file */
/*! Class containing all properties that can be read from the Can library */
#ifndef CANDATA_H
#define CANDATA_H

#include <QString>




class CanData
{
    /*! \todo create class header file */

    QString Description;
    int ID;
    QString RAW;
    int Value;
    int Timestamp;



    public:
        CanData(QString,int,QString,int,int);
        CanData();

};

#endif // CANDATA_H
