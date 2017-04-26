#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../controller.h"

using namespace cangateway;

void UnitTest::testControllerInit()
{

    Controller control;
    control.InitCan();
    QVERIFY2(false, "Failure");

}

