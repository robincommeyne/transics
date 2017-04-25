#include <QString>
#include <QtTest>
#include <QFile>
#include "unittest.h"
#include "../compression.h"
#include "../canData.h"



void UnitTest::testCompression()
{

    QVERIFY2(true, "Failure");


}
void UnitTest::testDecompression()
{
  Compression* compression = new Compression();
  QFile* unzippedFile = new QFile("test.json");
  QFile* zippedFile = new QFile("test.zip");
  QFile* testfile = NULL;
  testfile =  compression->UnZip(zippedFile);
  QString name = unzippedFile->fileName();
  QString returnedName;


  //returnedName = testfile->fileName();


  QVERIFY(name == returnedName);
}


//#include "tst_unittesttest.moc"
