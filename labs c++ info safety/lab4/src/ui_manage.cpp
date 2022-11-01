#include "steganography.h"
#include "ui_steganography.h"


void Steganography::showImage(const QString &path, QLabel *label)
{
    QImage img(path);

    qDebug() << label->maximumWidth() << " " << label->maximumHeight();

    if(img.width() > label->maximumWidth() || img.height() > label->maximumHeight()) {
        int deltaW = static_cast<int>(label->maximumWidth() * 100 / img.width());
        int deltaH = static_cast<int>(label->maximumHeight() * 100 / img.height());
        int deltaMax = (deltaW < deltaH) ? deltaW : deltaH;

        qDebug() << deltaW << " " << deltaH;

        int width = static_cast<int>(img.width() * (deltaMax / 100.));
        int height = static_cast<int>(img.height() * (deltaMax / 100.));

        qDebug() << img.width() << " " << img.height();

        qDebug() << width << " " << height;
        label->setMaximumWidth(width);
        label->setMaximumHeight(height);
    }

    label->setPixmap(QPixmap(path));
}
