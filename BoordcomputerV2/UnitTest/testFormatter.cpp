#include <QString>
#include <QtTest>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "unittest.h"
#include "../formatter.h"
#include "../compression.h"
#include "../config.h"



void UnitTest::testToObject()
{
    QFile testfile("JsonTestFile.json");
    testfile.open(QIODevice::ReadOnly);
    QByteArray uncompressed = testfile.readAll();
    QByteArray compressed;

    Compression compress;

    compress.Zip(uncompressed,compressed);
    QFile compressedTestFile("JsonTestFile.zip");
    compressedTestFile.open(QIODevice::ReadWrite);
    compressedTestFile.write(compressed);
    compressedTestFile.close();

    Formatter format;

    Config config;
    config = format.ToObject(compressedTestFile);


    QCOMPARE(config.EngineRPM,false);
    QCOMPARE(config.VehicleSpeed,true);

//    CanData can = CanData(70,"EngineCoolantTemp",220,"1080ffff80200080",500);

//    QJsonObject jsonObj = format.ToJsonObject(can);
//    QJsonDocument doc(jsonObj);
//    qDebug() << doc.toJson(QJsonDocument::Indented);







}
