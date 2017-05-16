#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../canData.h"

using namespace cangateway;


void UnitTest::testCanDataClass()
{
    CanData candata(5000,"EngineRpm",200,"12345678",50);

    QCOMPARE(5000,candata.Value());
    QVERIFY("EngineRpm" == candata.Description());
    QCOMPARE(200,candata.ID());
    QVERIFY("12345678" == candata.RAW());
    QCOMPARE(50,candata.Timestamp());

}
