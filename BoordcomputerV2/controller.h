/*! \file */
/*! Class to control the arduPiCANBUS library */

#include "canData.h"
#include <QtCore>
#include "canlibrary.h"

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
            bool event(QEvent *event);
            QTimer *canintervaltimer;

            int _timervalue = 0;
            void set_timer(int interval){_timervalue = interval;}
            int get_timer() const { return _timervalue; }

        private:
            QList<CanData> ListToPopulate;
            CanData *test = new CanData();
            CanLibrary can;
            int ListItemCounter = 0;
            int MaxListItems = 1000;

            void GetCan();
            //!< Receives all data from the arduPiCANBUS library and keeps track of the latest value of each parameter

            void PopulateList(
                CanData test/**< Object of the CanData class */
            );
            //!< Receives an object to place it in a list with added timestamp

        public slots:
            void Thread_Controller();
            void PopulateCanData();
        signals:
            void Subscribe_Watchdog_Controller(QObject* object);

    };

}
