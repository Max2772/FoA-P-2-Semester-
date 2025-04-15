#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetCurrentDate(); // Установка текущей даты
    ui->bDayDaySpinBox->setValue(bDate.getDay());
    ui->bDayMonthSpinBox->setValue(bDate.getMonth());
    ui->bDayYearSpinBox->setValue(bDate.getYear());





    Date date = Date(28, 05, 2026);
    Date Day = date.PreviousDay();
    QString Daystr = Day.DateToStr();
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
            if(!line.isEmpty() && Date::DateIsValid(line)){
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


void MainWindow::on_actionUpdate_triggered()
{
    dateVector.clear();
    int vectorSize = ui->tableWidget->rowCount();

    for(int i = 0; i < vectorSize; ++i){
        QStringList dateParts = dates[i].split(QRegularExpression("[/.]"));
        int day = dateParts[0].toInt();
        int month = dateParts[1].toInt();
        int year = dateParts[2].toInt();
        dateVector.push_back(Date(day, month, year));
    }

    if(dateVector.size() > 0)
        calculateAll();
}


void MainWindow::calculateAll()
{
    Date currentDate = GetCurrentDate();
    for(int i = 0; i < dateVector.size(); ++i){
        Date date = dateVector[i];
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(date.NextDay().DateToStr()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(date.PreviousDay().DateToStr()));

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setCheckState((Date::IsLeapYear(date.getYear()) ? Qt::Checked : Qt::Unchecked));
        ui->tableWidget->setItem(i, 3, item);

        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(date.WeekNumber())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem((QString::number(date.Duration(currentDate)))));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(date.DaysTillYourBirthday(date, bDate))));
    }
}

void MainWindow::SetCurrentDate()
{
    time_t currentTime = time(nullptr);
    struct tm *localTime = localtime(&currentTime);
    Date currentDate((localTime->tm_mday), (localTime->tm_mon + 1), (localTime->tm_year + YEAR_CONST));
    ui->currentDateLabel->setText(currentDate.DateToStr());
}

void MainWindow::SetBirthDate(int day, int month, int year)
{
    QString date = QString("%1/%2/%3").
                   arg(day, 2, 10, QChar('0')).
                   arg(month, 2, 10, QChar('0'))
                       .arg(year);

    if(!Date::DateIsValid(date)){
        qDebug() << "Incorrect date for birthday";
    }

    ui->bDayDaySpinBox->setValue(day);
    ui->bDayMonthSpinBox->setValue(month);
    ui->bDayYearSpinBox->setValue(year);
}


void MainWindow::on_pushButton_clicked()
{
    int day = ui->bDayDaySpinBox->value();
    int month = ui->bDayMonthSpinBox->value();
    int year = ui->bDayYearSpinBox->value();
    bDate.setDate(day, month, year);
    qDebug() << "Birthday changed to " << bDate.DateToStr();
}


void MainWindow::on_bDayMonthSpinBox_valueChanged(int month)
{
    int maxDays = bDate.getMaxDaysInMonth(month);
    int year = ui->bDayYearSpinBox->value();

    if(month == 2 && Date::IsLeapYear(year)){
        ui->bDayDaySpinBox->setMaximum(29);
    }else{
        ui->bDayDaySpinBox->setMaximum(maxDays);
    }
    qDebug() << "Max birthday Days changed to " << maxDays;
}


void MainWindow::on_bDayYearSpinBox_valueChanged(int year)
{
    bool isLeap = Date::IsLeapYear(year);
    int month = ui->bDayMonthSpinBox->value();
    if(isLeap && month == 2){
        ui->bDayDaySpinBox->setMaximum(29);
    }
}

