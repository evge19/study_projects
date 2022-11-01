#include "steganography.h"
#include "ui_steganography.h"


QImage Steganography::encodePng(QImage img, const QString &msg)
{
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);

            int R = pixel.red();
            int G = pixel.green();
            int B = pixel.blue();
            int A = pixel.alpha();

            if((x * img.height() + y) < msg.size()) {
                B = int(msg.at(x * img.height() + y).toLatin1());
                img.setPixel(x, y, qRgba(R, G, B, A));
            }
            else if((x * img.height() + y) == msg.size()) {
                img.setPixel(x, y, qRgba(R, G, 0, A));
            }
            else {
                img.setPixel(x, y, qRgba(R, G, B, A));
            }
        }
    }

    return img;
}

QImage Steganography::encodePng(QImage img, const QByteArray &file)
{
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);

            int R = pixel.red();
            int G = pixel.green();
            int B = pixel.blue();
            int A = pixel.alpha();

            if((x * img.height() + y) < file.size()) {
                B = int(file.at(x * img.height() + y));
                img.setPixel(x, y, qRgba(R, G, B, A));
            }
            else if((x * img.height() + y) == file.size()) {
                img.setPixel(x, y, qRgba(R, G, 0, A));
            }
            else {
                img.setPixel(x, y, qRgba(R, G, B, A));
            }
        }
    }
    return img;
}


