/*! \file */
/*! Class to change file format */

#ifndef FORMATTER_H
#define FORMATTER_H

#include <QFile>
#include "config.h"
#include "canData.h"
#include "message.h"

class Formatter
{
    private:

        QFile configfile;
        CanData candata;
	 
	public:
		QJsonObject ToJsonObject(
                CanData candata /**< Json object as input */
		);
		//!< Converts given object from CanData class to QJsonObject
		
		
        Config ToObject(
                QFile &configfile /**< Qfile to convert to QObject */
		);
		//!< Tries to convert Qfile to QObject of the Config Class

        QJsonDocument ToJsonDocument(QList<CanData> FilteredList);



};

#endif // FORMATTER_H

