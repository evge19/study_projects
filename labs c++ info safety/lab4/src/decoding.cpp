#include "steganography.h"
#include "ui_steganography.h"


QString Steganography::decodePng(const QImage &img)
{
    bool reading = true;
    QString msg = "";
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);


            int B = pixel.blue();

            if(B == 0) {
                reading = false;
            }
            else if(reading) {
                qDebug() << x << " " << y << ") " << B << " " << char(B);
                msg += QChar(char(B));
            }
        }
    }

    qDebug() << msg;
    return msg;
}

QByteArray Steganography::decodePng(const QImage &img, bool)
{
    bool reading = true;
    QByteArray file;
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);


            int B = pixel.blue();

            if(B == 0) {
                reading = false;
            }
            else if(reading) {
                file.append(char(B));
            }
        }
    }
    return file;
}
