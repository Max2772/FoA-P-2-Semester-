#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "date.h"

#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Date date = Date(28, 05, 2026);
    Date bDate = Date(27, 05, 2025);
    Date Day = date.PreviousDay();

    QString Daystr = Day.DateToStr();


    ui->textEdit->setText(Daystr);
    ui->textEdit->append(QString::number(date.DaysTillYourBirthday(date, bDate)));
    ui->textEdit->append(QString::number(date.Duration(bDate)));
    // ui->textEdit->append(QString::number(date.DaysTillYourBirthday(bDate)));
    // ui->textEdit->append(QString::number(date.Duration(durationDate)));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ImportDatesInTable()
{
    ui->tableWidget->setRowCount(dates.size());

    for(int i = 0; i < dates.size(); ++i){
        QTableWidgetItem item(dates[i]);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(item));
    }
}

void MainWindow::on_actionImport_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", QString(), "Текстовые файлы (*.txt)");
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug("Файл не открылся");
        }

        QTextStream in(&file);
        QStringList dates;
        while(!in.atEnd()){
            QString line = in.readLine().trimmed();
            if(!line.isEmpty()){
                dates.append(line);
            }
        }
        if(!dates.empty()){
            this->dates = dates;
            ImportDatesInTable();
        }

        file.close();

    }else{
        qDebug("Файл не выбран");
    }
}

void MainWindow::on_actionClean_triggered()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

