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

        private:
            QList<CanData> _listToPopulate;
            CanLibrary _can;
            const int _intervalTimerInMs = 1000;

            CanData _engineLoad, _engineCoolantTemp, _fuelPressure, _intakeMAPressure, _engineRPM,
                    _vehicleSpeed, _timingAdvance, _intakeAirTemp, _mafAirFlowRate, _throttlePosition,
                    _fuelLevel, _barometricPressure, _engineFuelRate;

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
