#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../watchdog.h"

UnitTest::UnitTest()
{

}

void UnitTest::testWatchdog()
{
    //Watchdog* watchdog = new Watchdog();

    QVERIFY2(true, "Failure");
    //QCOMPARE(watchdog->TriggerWatchdog("Manager"), true);

}


//#include "tst_unittesttest.moc"
