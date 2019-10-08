#include "Util.h"

namespace Util
{
    /*
    * Taken from:
    * https://www.qtcentre.org/threads/50535-Random-hex-number-of-given-length-in-QT
    */
    QString GetRandomHex(int length)
    {
        QString randomHex;

        for(int i = 0; i < length; i++) {
            int n = qrand() % 16;
            randomHex.append(QString::number(n, 16));
        }

        return randomHex;
    }
}
