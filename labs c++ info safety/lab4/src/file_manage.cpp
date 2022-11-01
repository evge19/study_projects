#include "steganography.h"
#include "ui_steganography.h"


QByteArray Steganography::readDataFromFile(const QString &path)
{
    QFile file(path);
    if(!file.open(QFile::ReadOnly)) {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл");
        return QByteArray();
    }
    QByteArray fileData = file.readAll();
    file.close();

    return fileData;
}

bool Steganography::writeDataToFile(const QString &path, const QByteArray &data)
{
    QFile file(path);
    if(!file.open(QFile::WriteOnly)) {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл");
        return false;
    }
    file.write(data);
    file.close();

    return true;
}
