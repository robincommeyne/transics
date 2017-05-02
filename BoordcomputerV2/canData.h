#ifndef CANDATA_H
#define CANDATA_H

#include <QString>

namespace cangateway {

    class CanData
    {
        private:

            QString description;
            int id;
            QString raw;
            int value;
            int timestamp;

        public:

             QString Description(){return description;}
             int ID(){return id;}
             QString RAW(){return raw;}
             int Value(){return value;}
             int Timestamp(){return timestamp;}

             //void SetDescription(QString setDescription){description = setDescription;}
             //void SetID(int setId){id = setId;}
             //void SetRAW(QString setRaw){raw = setRaw;}
             //void SetValue(int setValue){value = setValue;}
             //void SetTimeStamp(int setTimeStamp){timestamp = setTimeStamp;}

             CanData(int setValue,QString setDescription,int setId,QString setRaw,int setTimeStamp);
             CanData();
    };

}


#endif // CANDATA_H
