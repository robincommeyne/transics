#include <QString>
#include <QtTest>
#include <QFile>
#include "unittest.h"
#include "../compression.h"


using namespace cangateway;

void UnitTest::testCompression()
{
    /**< Test compression for pass */

    Compression compress;
    QByteArray uncompressed("test");
    QByteArray compressed;

    QCOMPARE(compress.Zip(uncompressed,compressed),0);
    QVERIFY(compressed.size()>0);

}

void UnitTest::testCompression_error()
{
    /**< Test error reporting on empty file error */

    Compression compress;
    QByteArray uncompressed;
    QByteArray compressed;

    QCOMPARE(compress.Zip(uncompressed,compressed),1);
}

void UnitTest::testCompression_error2()
{
   /**< Test compressed file integrity */

   Compression compress;
   QByteArray uncompressed;
   QByteArray compressed;
   QByteArray expecteddata;

   uncompressed.append("1");
   QCOMPARE(compress.Zip(uncompressed,compressed),0);

   char mydata[] = { 0x00,0x00,0x00,0x01,0x78,0xda,0x33,0x04,0x00,0x00,0x32,0x00,0x32};
   //char mydata[1];

   expecteddata = QByteArray::fromRawData(mydata,sizeof(mydata));



   qDebug() << "the compressed data is:" << compressed;

   QCOMPARE(compressed,expecteddata);
}

void UnitTest::testDecompression()
{
    /**< Test decompression for pass */

    Compression decompress;
    QByteArray uncompressed;
    QByteArray compressed;

    char mydata[] = { 0x00,0x00,0x00,0x01,0x78,0xda,0x33,0x04,0x00,0x00,0x32,0x00,0x32};
    //char mydata[1];
    compressed = QByteArray::fromRawData(mydata,sizeof(mydata));


    QCOMPARE(decompress.UnZip(compressed,uncompressed),0);


}

void UnitTest::testDecompression_error()
{
    /**< Test error reporting on empty file error */

    Compression compress;
    QByteArray uncompressed;
    QByteArray compressed;

    QCOMPARE(compress.UnZip(compressed,uncompressed),1);
}

void UnitTest::testDecompression_error2()
{
   /**< Test decompressed file integrity */

   Compression compress;
   QByteArray uncompressed;
   QByteArray compressed;
   QByteArray expecteddata;

   expecteddata.append("1");

   char mydata[] = { 0x00,0x00,0x00,0x01,0x78,0xda,0x33,0x04,0x00,0x00,0x32,0x00,0x32};
   //char mydata[1];
   compressed = QByteArray::fromRawData(mydata,sizeof(mydata));


   QCOMPARE(compress.UnZip(compressed,uncompressed),0);

   qDebug() << "the uncompressed data is:" << uncompressed.data();

   QCOMPARE(uncompressed,expecteddata);
}


//#include "tst_unittesttest.moc"
