#ifndef UNITTEST1_H
#define UNITTEST1_H

#include <QtTest>


class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();

private Q_SLOTS:

    void testWatchdog();

    void testCompression();
    void testCompression_error();
    void testCompression_error2();

    void testDecompression();
    void testDecompression_error();
    void testDecompression_error2();

    void testControllerInit();

    void testLoggingInit();
    void testLoggingSize();

    void testCompressedToObject();
    void testToObject();

    void testSendFileSystem();
    void testReadFileSystem();
    void TestGetFilteredListItem();





};




#endif // UNITTEST1_H
