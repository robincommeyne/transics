#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../dispatcher.h"
#include "../canData.h"


using namespace cangateway;


void UnitTest::testSendFileSystem()
{
    Dispatcher dispatcher;
    QFile testFile("test.txt");


    bool testFileFound = false;
    dispatcher.SendFileSystem(testFile,"testfile.txt");


    QFile FindTestFile("testfile.txt");
    if (FindTestFile.exists())
    {
        testFileFound = true;
    }
    else
    {
        testFileFound = false;
    }

    QCOMPARE(testFileFound,true);

}

void UnitTest::testReadFileSystem()
{
    //Dispatcher dispatcher;
    //bool fileFound = false;

    //QByteArray testArray = dispatcher.ReadFileSystem("testfile.txt").readAll();


//    if (testArray.data() == "test")
//    {
//        fileFound = true;
//    }
//    else
//    {
//        fileFound = false;
//    }



}

void UnitTest::CheckFilteredListForWrightObjects()
{
    QFile testfile("JsonTestFile.json");
    testfile.open(QIODevice::ReadOnly);

    Formatter format;
    Config config;

    config = format.ToObject(testfile);
    testfile.close();

    QList<CanData> candatalist;

    CanData EngineSpeed1 = CanData(200,"VehicleSpeed",225,"12345678",10);
    CanData EngineSpeed2 = CanData(250,"VehicleSpeed",225,"12345678",12);
    CanData EngineRPM = CanData(8000,"EngineRPM",226,"12345678",5);

    candatalist << EngineSpeed1 << EngineSpeed2 << EngineRPM;

    Dispatcher dispatcher;

    QList<CanData> filteredlist =  dispatcher.GetFilteredListItem(config,candatalist);

    QCOMPARE(filteredlist[0].Timestamp(),10);

}

void UnitTest::CheckUnfilteredListSize()
{
    Dispatcher dispatcher;
    bool toobig = false;
    QList<CanData> candatalist;

    CanData EngineSpeed1 = CanData(200,"VehicleSpeed",225,"12345678",10);
    CanData EngineSpeed2 = CanData(250,"VehicleSpeed",225,"12345678",12);
    CanData EngineRPM1 = CanData(12000,"EngineRPM",226,"12345678",5);

    candatalist << EngineSpeed1 << EngineSpeed2 << EngineRPM1;

    for(int i=0; i < 350; ++i)
    {
        dispatcher.ReceiveListFromController(candatalist);
    }

    if(dispatcher._listfromcontroller.length()<=1000)
    {
        toobig = false;
    }
    else
        toobig = true;

    QCOMPARE(toobig,false);


}
