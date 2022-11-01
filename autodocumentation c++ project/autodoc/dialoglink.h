#ifndef DIALOGLINK_H
#define DIALOGLINK_H

#include <QDialog>

namespace Ui {
class DialogLink;
}

class DialogLink : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLink(QWidget *parent = nullptr);
    ~DialogLink();
    QString getlink();

private:
    Ui::DialogLink *ui;
};

#endif // DIALOGLINK_H
