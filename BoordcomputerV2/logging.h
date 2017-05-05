/*! \file */
/*! Class for program logging */
#include <QString>

namespace cangateway {

    class Logging
    {
        public:
            void InitLogging(
                    int _rotationInterval, /**< Rotation interval in hours */
                    int _fileSize /**< log file size in bytes */
            );

            void Log(
                    QString _logLevel,/**< specifies the desired log level, accepts trace, debug, info, warning, error, fatal */
                    QString _message/**< contains logging message */
            );

         private:
            const int _setToMegaByte = 1024*1024; /**< specifies the value to convert to MB */
            const int _maxFolderSize = 10; /**< specifies the max folder size in MB */

    };

}


