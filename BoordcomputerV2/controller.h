/*! \file */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "canData.h"
#include <QtCore>
#include "canlibrary.h"


namespace cangateway {

    typedef QList<CanData> CanDataList;

    class Controller : public QObject
    {
        Q_OBJECT
        public:
            Controller();
            QTimer *_canIntervalTimer;
            void InitCan();

        private:
            QList<CanData> _listToPopulate;
            CanLibrary _can;

            CanData _engineLoad;
            CanData _coolantTemp;

            void GetCan();
            //!< Receives all data from the arduPiCANBUS library and keeps track of the latest value of each parameter */

        public slots:
            void ControllerThread();
            void ControllerHandler();

        signals:
            void SubscribeWatchdogController(QObject* object);
            void SendList(CanDataList);

    };

}

#endif // CONTROLLER_H
