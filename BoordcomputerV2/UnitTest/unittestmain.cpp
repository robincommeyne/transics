#include <QtTest>

#include "unittest.h"



int main()
{

    UnitTest* test = new UnitTest();
    QTest::qExec(test);



}

