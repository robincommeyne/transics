#ifndef CANDATA_H
#define CANDATA_H

#include <QString>

namespace cangateway {

    class CanData
    {
        private:

            QString _description;
            QString _raw;
            int _id;
            int _value;
            int _timestamp;

        public:

             QString Description(){return _description;}
             int ID(){return _id;}
             QString RAW(){return _raw;}
             int Value(){return _value;}
             int Timestamp(){return _timestamp;}

             //void SetDescription(QString setDescription){description = setDescription;}
             //void SetID(int setId){id = setId;}
             //void SetRAW(QString setRaw){raw = setRaw;}
             //void SetValue(int setValue){value = setValue;}
             //void SetTimeStamp(int setTimeStamp){timestamp = setTimeStamp;}

             CanData(int setValue,QString setDescription,int setId,QString setRaw,int setTimeStamp);
             CanData(){}
    };

}


#endif // CANDATA_H
