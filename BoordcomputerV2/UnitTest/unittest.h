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
    void testDecompression();
};




#endif // UNITTEST1_H
