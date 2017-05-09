/*! \file */
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <QJsonObject>

namespace cangateway {
    class Compression
    {

        public:
            int Zip(
                    QByteArray in, /**< Input bytearray to compress */
                    QByteArray &out /**< compressed bytearray output*/
            );

            int UnZip(
                    QByteArray in, /**< Input bytearray to decompress */
                    QByteArray &out /**< decompressed bytearray output */
            );

    };
}

#endif // COMPRESSION_H
