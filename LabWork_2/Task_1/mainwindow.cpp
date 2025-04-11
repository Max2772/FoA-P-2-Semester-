#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Date date = Date(28, 05, 2006);
    Date bDate = Date(27, 05, 2025);
    Date Day = date.PreviousDay();

    QString Daystr = Day.DateToStr();


    ui->textEdit->setText(Daystr);
    ui->textEdit->append(QString::number(date.DaysTillYourBirthday(date, bDate)));
    // ui->textEdit->append(QString::number(date.DateToDays("30/12/2026", false) - date.DateToDays("30/12/2025", false)));
    // ui->textEdit->append(QString::number(date.DaysTillYourBirthday(bDate)));
    // ui->textEdit->append(QString::number(date.Duration(durationDate)));

    // QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QString(), "Текстовые файлы (*.txt)");
    // if(!fileName.isEmpty()){
    //     QFile file(fileName);
    //     if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    //         qDebug("Файл не открылся");
    //     }

    //     QTextStream in(&file);
    //     QStringList dates;
    //     while(!in.atEnd()){
    //         QString line = in.readLine().trimmed();
    //         if(!line.isEmpty()){
    //             dates.append(line);
    //         }
    //     }
    //     file.close();

    // }else{
    //     qDebug("Файл не выбран");
    // }

}

MainWindow::~MainWindow()
{
    delete ui;
}
