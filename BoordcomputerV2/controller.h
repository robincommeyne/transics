#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "canData.h"
#include <QtCore>
#include "canlibrary.h"

typedef QList<CanData> CanDataList;

namespace cangateway {

    class Controller : public QObject
    {

        Q_OBJECT

        public:
            //! InitCan initiates ardiPiCANBUS library.
            /*!
             Initiates arduPiCANBUS library functions, and starts the reading cycle.
            */
            Controller();
            void InitCan();
            QTimer *canintervaltimer;

        private:
            QList<CanData> ListToPopulate;
            CanData *test = new CanData();
            CanLibrary can;

            void GetCan();
            //!< Receives all data from the arduPiCANBUS library and keeps track of the latest value of each parameter

            CanData EngineLoad;
            CanData CoolantTemp;


        public slots:
            void Thread_Controller();
            void TimerElapsed();
        signals:
            void Subscribe_Watchdog_Controller(QObject* object);
            void Send_List(CanDataList);

    };

}

#endif // CONTROLLER_H
