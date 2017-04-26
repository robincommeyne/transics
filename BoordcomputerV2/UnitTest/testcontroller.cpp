#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../controller.h"



void UnitTest::testControllerInit()
{
    Controller control;
    control.InitCan();
    QVERIFY2(false, "Failure");
}

