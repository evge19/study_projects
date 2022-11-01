#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QMessageBox>
#include <QRgb>
#include <QDebug>
#include <QByteArray>

namespace Ui {
class Steganography;
}

class Steganography : public QMainWindow
{
    Q_OBJECT

public:
    explicit Steganography(QWidget *parent = 0);
    ~Steganography();

private:
    // encoding.cpp
    QImage encodePng(QImage img, const QString& msg);
    QImage encodePng(QImage img, const QByteArray& file);

    // decoging.cpp
    QString decodePng(const QImage& img);
    QByteArray decodePng(const QImage& img, bool);

    // ui_manage.cpp
    void showImage(const QString& path, QLabel* label);

    // file_manag.cpp
    QByteArray readDataFromFile(const QString& path);
    bool writeDataToFile(const QString& path, const QByteArray& data);

private slots:
    // private_slots.cpp
    QImage encode(const QString& path, const QString& msg);
    QImage encode(const QString& path, const QByteArray& file);

    QString decode(const QString& path);
    QByteArray decode(const QString& path, bool);

    // steganography.cpp
    void on_bSelectFile_clicked();
    void on_bEncode_clicked();
    void on_bDecode_clicked();
    void on_bSelectInputImage_clicked();

private:
    Ui::Steganography *ui;
};

#endif // STEGANOGRAPHY_H
