#include "unittest.h"
#include "../logging.h"


void UnitTest::testLoggingInit()
{
    /**< Test creation of log file trough initialisation */

    Logging log;
    bool fileExists;
    QFileInfo file("system.log");

    log.InitLogging(1,1);
    log.Log("info","dit is een test");


    // check if file exists
    if (file.exists() && file.isFile()) {
        fileExists = true;
    } else {
        fileExists = false;
    }

    QCOMPARE(fileExists,true);


}
void UnitTest::testLoggingSize()
{
    /**< Test set log file size */

    Logging log;
    int megabytes = 1;
    bool toobig;
    int size;
    QFile myFile("Logs/system.log");



    for (int i = 0; i<25000;i++)
    {
        log.Log("info","dit is een test");
    }


    if (myFile.open(QIODevice::ReadOnly)){
        size = myFile.size();
        myFile.close();
    }


    if (size>megabytes*1024*1024+50000)
    {
        toobig = true;
    }
    else
    {
        toobig = false;
    }
    QCOMPARE(toobig,false);


}

