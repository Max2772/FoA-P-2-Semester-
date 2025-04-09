#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Date* date = new Date(30, 5, 2026);
    Date* bDate = new Date(27, 5, 2006);
    Date* durationDate = new Date(11, 9, 2001);

    QString dateStr = date->DateToStr();
    /*
    ui->textEdit->setText(dateStr);
    ui->textEdit->append(QString::number(date->WeekNumber()));
    ui->textEdit->append(QString::number(date->DateToDays("30/12/2026", false) - date->DateToDays("30/12/2025", false)));
    ui->textEdit->append(QString::number(date->DaysTillYourBirthday(*bDate)));
    ui->textEdit->append(QString::number(date->Duration(*durationDate)));
*/
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Выберите файл сука", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if(!fileName.isEmpty()){

    }else{
        qDebug("Файл не выбран");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
