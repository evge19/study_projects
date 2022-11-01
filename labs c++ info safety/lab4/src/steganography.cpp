#include "steganography.h"
#include "ui_steganography.h"

Steganography::Steganography(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steganography)
{
    ui->setupUi(this);
}

Steganography::~Steganography()
{
    delete ui;
}

void Steganography::on_bSelectFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Сhoose the file for encryption", ".", "*.*"
    );
    ui->eFileInput->setText(filePath);
}

void Steganography::on_bSelectInputImage_clicked()
{
    QString imgPath = QFileDialog::getOpenFileName(
        this, "Сhoose and save the image", ".", "*.png"
    );
    ui->eImageInput->setText(imgPath);
}

void Steganography::on_bEncode_clicked()
{
    QString msgText = ui->pteInput->toPlainText();
    QString filePath = ui->eFileInput->text();
    QString imgPath = ui->eImageInput->text();

    if(imgPath == "") {
        QMessageBox::information(this, "Error", "Сhoose the image");
        return;
    }
    else if(msgText == "" && filePath == "") {
        QMessageBox::information(this, "Error", "Сhoose the file");
        return;
    }

    QImage mimg;
    if(msgText != "") {
        mimg = this->encode(imgPath, msgText);
    }
    else if(filePath != "") {
        QByteArray fileData = this->readDataFromFile(filePath);
        if(fileData.size() == 0) {
            return;
        }

        mimg = this->encode(imgPath, fileData);
    }

    QString outputImg = QFileDialog::getSaveFileName(
        this, "Cохранить результат", ".png", "*.*"
    );
    mimg.save(outputImg);
}

void Steganography::on_bDecode_clicked()
{
    QString imgPath = ui->eImageInput->text();

    if(imgPath == "") {
        QMessageBox::information(this, "Error", "Сhoose the image");
        return;
    }

        QString msg = this->decode(imgPath);
        qDebug() << msg;
        ui->teOutput->setPlainText(msg);
}
