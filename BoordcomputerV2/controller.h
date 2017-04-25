/*! \file */
/*! Class to control the arduPiCANBUS library */

#include "canData.h"
#include <QtCore>

namespace cangateway {
    class Controller : public QObject
    {
        Q_OBJECT
        private:
            CanData test;

            void GetCan(
                    int Interval/**< Specifies the time between the data returns in miliseconds with a minimum of 500 and a maximum of 1000 ms*/
            );
            //!< Receives all data from the arduPiCANBUS library and keeps track of the latest value of each parameter


            void PopulateList(
                    CanData test/**< Object of the CanData class */
            );
            //!< Receives an object to place it in a list with added timestamp

        public slots:
            void Thread_Controller();
        signals:
            void Subscribe_Watchdog_Controller(QObject* object);


        public:

            //! InitCan initiates ardiPiCANBUS library.
            /*!
             Initiates arduPiCANBUS library functions, and starts the reading cycle.
            */
            Controller() {}
            void InitCan();
            QString Int2String(uint8_t x[] );
    };

}
