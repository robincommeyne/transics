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

            Config CompressedToObject(QByteArray configfile);
            //!< Converts given compressed file to Config object

            Config ToObject(QByteArray configfile);
            //!< Tries to convert QByteArray to QObject of the Config Class

            QJsonDocument ToJsonDocument(QList<CanData> FilteredList);

    };

}
#endif // FORMATTER_H

