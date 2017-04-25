/*! \file */
/*! Class for program logging */
#include <QString>

class Logging
{
    private:
        QString Loglevel;
        QString Message;
        int RotationInterval;
        int Filesize;


    public:



        //! Initiates the boost logging library.
        /*!
          Initlogging is called at startup to set the rotation interval and filesize.
         */

        void InitLogging(
                int RotationInterval, /**< Rotation interval in hours */
                int Filesize /**< log file size in bytes */
        );

        //! Log message with set loglevel.
        /*!
          Log can be called with the added parameters to make an entry to the log file
          that is made using the boost library.
         */

        void Log(
                QString Loglevel,/**< specifies the desired log level, accepts trace, debug, info, warning, error, fatal */
                QString message/**< contains logging message */
        );

};

