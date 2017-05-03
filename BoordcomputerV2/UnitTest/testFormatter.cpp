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
    QFile compressedTestFile("JsonTestFile.zip");
    compressedTestFile.open(QIODevice::ReadWrite);
    compressedTestFile.write(compressed);
    compressedTestFile.close();

    Formatter format;

    Config config;

    config = format.CompressedToObject(compressedTestFile);

    QMap<QString,bool> map = config.get_configmap();



    QCOMPARE(map.value("EngineRPM"),false);
    QCOMPARE(map.value("VehicleSpeed"),true);


}

void UnitTest::testToObject()
{
    QFile testfile("JsonTestFile.json");
    testfile.open(QIODevice::ReadOnly);


    Formatter format;

    Config config;

    config = format.ToObject(testfile);
    testfile.close();

    QMap<QString,bool> map = config.get_configmap();




    QCOMPARE(map.value("EngineRPM"),false);
    QCOMPARE(map.value("VehicleSpeed"),true);



}
