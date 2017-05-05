/*! \file */
#ifndef FORMATTER_H
#define FORMATTER_H

#include <QFile>
#include "config.h"
#include "canData.h"
#include "message.h"

namespace cangateway {

    class Formatter
    {
        public:
            QJsonObject ToJsonObject(CanData canData);
            //!< Converts given object from CanData class to QJsonObject

            Config CompressedToObject(QFile &configfile);
            //!< Converts given compressed file to Config object

            Config ToObject(QFile &configfile);
            //!< Tries to convert Qfile to QObject of the Config Class

            QJsonDocument ToJsonDocument(QList<CanData> FilteredList);

    };

}
#endif // FORMATTER_H

