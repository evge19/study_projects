#include "widget.h"
#include "ui_widget.h"

/* Функция для получения рандомного числа
 * в диапазоне от минимального до максимального
 * */
//static int randomBetween(int low, int high)
//{
//    return (qrand() % ((high + 1) - low) + low);
//}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) //создание сцены
{
    ui->setupUi(this);

    // Косметическая подготовка приложения
    //this->resize(640,640);          // Устанавливаем размеры окна приложения
    //this->setFixedSize(640,640);

    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    //ui->graphicsView->resize(600,600);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    m_topLeftButton = new QPushButton("Top Left", ui->graphicsView);
    //scene->setSceneRect(0,0,500,500); // Устанавливаем размер сцены

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked() // создать класс на сцене
{
    MoveItem *item = new MoveItem();  // Создаём графический элемент

    item->setPos(-100,-100);
    scene->addItem(item);   // Добавляем элемент на графическую сцену

}

void Widget::on_pushButton_2_clicked() // создать проект с файлами
{

    QString filePath = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения");
    QStringList dirlist=filePath.split('/',QString::SkipEmptyParts);
    QString name, brief, dirf;
    for(int i=0;i<dirlist.size();i++)
    {
        dirf.append(dirlist[i]);
        dirf.append("\\");
    }
    QString namePRO=ui->lineEdit->text();
    QString cppPRO="", hPRO="";
    QTextStream fout(stdout);
    QFile filePRO(dirf+namePRO + "_project.pro");
    for(int i=0;i<MoveItem::allclasses.size();i++)
    {
        name=MoveItem::allclasses[i];
        brief="\n/*!\n\\class "+MoveItem::allbriefs[i]+"\n"+MoveItem::alldescrs[i]+"\n*/\n";

        cppPRO.append("\n\t"+name.toLower()+".cpp \\");
        hPRO.append("\n\t"+name.toLower()+".h \\");
        QFile fileCPP(dirf+name.toLower() + ".cpp");
        QFile fileH(dirf+name.toLower() + ".h");


        if(fileCPP.open(QIODevice::WriteOnly)){

            QTextStream fout(&fileCPP);
            fout<<"#include \""<<name.toLower()<<".h\""<<endl<<brief<<name<<"::"<<name<<"()\n{\n\n}";
            for(int j=0; j<MoveItem::file_met[i].size();j++)
            {
                fout<<"\n/*!\n\\brief "<<MoveItem::file_met_descr[i][j]<<"\n*/\n";
                razdel=MoveItem::file_met[i][j].split(' ');
//                qDebug()<<"razdel"<<razdel.size();
                fout<<razdel[0]<<" "<<name<<"::"<<razdel[1]<<"\n{\n\n}";
            }
        }
        fileCPP.close();
        if(fileH.open(QIODevice::WriteOnly))
        {

            QTextStream fout(&fileH);

            if(name!=MoveItem::nasled[1])
            {
                fout<< "#ifndef "<<name.toUpper()<<"_H\n#define "<<name.toUpper()<<"_H\n\n\nclass "<<name<<"\n{\npublic:\n\t"<<name<<"();";
                for(int j=0; j<MoveItem::file_atr[i].size();j++)
                {
                    razdelatr=MoveItem::file_atr[i][j].split(':');
                    fout<<"\n\t"<<razdelatr[1]<<" "<<razdelatr[0]<<";";
                }


                for(int j=0; j<MoveItem::file_met[i].size();j++)
                {
                    fout<<"\n\t"<<MoveItem::file_met[i][j]<<";";
                }
                fout<<"\n};\n\n\n#endif // "<<name.toUpper()<<"_H";
            }
            else
            {
                fout<< "#ifndef "<<name.toUpper()<<"_H\n#define "<<name.toUpper()<<"_H\n\n#include \""<<MoveItem::nasled[0].toLower()<<".h\"\n\n\nclass "<<name<<" : public "<<MoveItem::nasled[0]<<"\n{\npublic:\n\t"<<name<<"();";
                for(int j=0; j<MoveItem::file_atr[i].size();j++)
                {
                    razdelatr=MoveItem::file_atr[i][j].split(':');
                    fout<<"\n\t"<<razdelatr[1]<<" "<<razdelatr[0]<<";";
                }
                for(int j=0; j<MoveItem::file_met[i].size();j++)
                {
                    fout<<"\n\t"<<MoveItem::file_met[i][j]<<";";
                }
                fout<<"\n};\n\n\n#endif // "<<name.toUpper()<<"_H";
            }

        }
        fileH.close();
    }
    if(filePRO.open(QIODevice::WriteOnly)){

        QTextStream fout(&filePRO);
        fout<<"TEMPLATE = app\nCONFIG += console c++11\nCONFIG -= app_bundle\nCONFIG -= qt\nSOURCES += \\"<<"\n\tmain.cpp \\"<<cppPRO<<endl<<endl<<"HEADERS += \\"<<hPRO<<endl;
    }
    filePRO.close();
    QFile fileMAIN(dirf + "main.cpp");
    if(fileMAIN.open(QIODevice::WriteOnly)){

        QTextStream fout(&fileMAIN);
        fout<<"#include <iostream>\n\nusing namespace std;\nint main()\n{\n\tcout << \"PROJECT IS OPENED!\" << endl;\n\treturn 0;\n}"<<endl;
    }
    fileMAIN.close();
    if(filePath!=NULL)
        QMessageBox::information(this, "Оповещение", "Файлы успешно созданы" );
}

void Widget::on_pushButton_3_clicked() // отношение
{
    MoveItem::linkpressed=true;
    DialogLink diallink;
    if(diallink.exec() == QDialog::Accepted)
    {
        QString classlink=diallink.getlink();
                if(classlink=="Ассоциация")
                    LinkItem::typerelat=0;
                else if(classlink=="Наследование")
                    LinkItem::typerelat=1;

    }


}


void Widget::on_pushButton_5_clicked() // выбрать проект
{
    QString filedir = QFileDialog::getExistingDirectory(this, "Выберите папку проекта");
    QStringList dirprlist=filedir.split('/',QString::SkipEmptyParts);

    for(int i=0;i<dirprlist.size();i++)
    {
        dirpr.append(dirprlist[i]);
        dirpr.append("\\");
    }
}

void Widget::on_pushButton_6_clicked() // редактировать
{
    //dirpr
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    if (key==Qt::Key_Enter)
    {
        LinkItem *arrow = new LinkItem();
    //    scene->addLine(MoveItem::linepos[0+MoveItem::checharrow*4]-20, MoveItem::linepos[1+MoveItem::checharrow*4], MoveItem::linepos[2+MoveItem::checharrow*4], MoveItem::linepos[3+MoveItem::checharrow*4],QPen(Qt::black));
        arrow->setPos(0,0);
        scene->addItem(arrow);
        MoveItem::linkpressed=false;
     }

}


