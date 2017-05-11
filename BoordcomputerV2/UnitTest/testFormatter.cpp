#include <QString>
#include <QtTest>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "unittest.h"
#include "../formatter.h"
#include "../compression.h"
#include "../config.h"


using namespace cangateway;

void UnitTest::testCompressedToObject()
{
    QFile testfile("JsonTestFile.json");
    testfile.open(QIODevice::ReadOnly);
    QByteArray uncompressed = testfile.readAll();
    testfile.close();
    QByteArray compressed;

    Compression compress;

    compress.Zip(uncompressed,compressed);

    Formatter format;

    Config config;

    config = format.CompressedToObject(compressed);

    QMap<QString,bool> map = config.get_configmap();



    QCOMPARE(map.value("EngineRPM"),false);
    QCOMPARE(map.value("VehicleSpeed"),true);


}

void UnitTest::testToObject()
{
    QFile testfile("JsonTestFile.json");
    testfile.open(QIODevice::ReadOnly);

    QByteArray testfileArray = testfile.readAll();


    Formatter format;

    Config config;

    config = format.ToObject(testfileArray);
    testfile.close();

    QMap<QString,bool> map = config.get_configmap();




    QCOMPARE(map.value("EngineRPM"),false);
    QCOMPARE(map.value("VehicleSpeed"),true);



}
