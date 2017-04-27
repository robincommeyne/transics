/*! \file */
#include "compression.h"
#include "watchdog.h"
#include "logging.h"



int Compression::Zip(QByteArray in, QByteArray &out)
{
  if(in.isEmpty())
  {
    return 1;
  }
  else
  {
    out = qCompress(in,9);
    return 0;
  }

}
int Compression::UnZip(QByteArray in, QByteArray &out)
{

    if(in.isEmpty())
    {
      return 1;
    }
    else
    {
      out = qUncompress(in);
      return 0;
    }
}
