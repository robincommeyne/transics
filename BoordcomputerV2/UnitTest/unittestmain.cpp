
#include <QtTest>


#include "unittest.h"

UnitTest::UnitTest()
{

}


int main()
{

    UnitTest* test = new UnitTest();
    QTest::qExec(test);


}

