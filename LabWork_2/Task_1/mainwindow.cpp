#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Date* date = new Date(31, 12, 2025);
    QString dateStr = date->DateToStr();
    ui->textEdit->setText(dateStr);
    ui->textEdit->append(QString::number(date->WeekNumber()));
    ui->textEdit->append(QString::number(date->DateToDays("30/12/2025")));
    ui->textEdit->append(QString::number(date->DaysTillYourBirthday("31, 12, 2026")));
}

MainWindow::~MainWindow()
{
    delete ui;
}
