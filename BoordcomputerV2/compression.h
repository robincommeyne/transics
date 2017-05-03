#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <QJsonObject>
#include <QString>
#include <QFile>


class Compression
{

    private:

        QString OutFileName;
        QFile ZippedFile;

    public:
        //! Zip compresses a given bytearray.
        /*!
         Receives a QByteArray and compresses it using Qt with Zlib implementation
         returning '1' if succesfull, '0' for error.
        */

        int Zip(
                QByteArray in, /**< Input bytearray to compress */
                QByteArray &out /**< compressed bytearray output*/
        );


        //! UnZip decompresses a given bytearray.
        /*!
         Receives a QByteArray and decompresses it using Qt with Zlib implementation
         returning '0' if succesfull, '1' for error.
        */
        int UnZip(
                QByteArray in, /**< Input bytearray to decompress */
                QByteArray &out /**< decompressed bytearray output */
        );

};

#endif // COMPRESSION_H
