#include <QString>
#include <QtTest>
#include "unittest.h"
#include "../dispatcher.h"

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
