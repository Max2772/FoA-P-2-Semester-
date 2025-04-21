#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetCurrentDate(); // Установка текущей даты
    ui->bDayDaySpinBox->setValue(bDate.getDay());
    ui->bDayMonthSpinBox->setValue(bDate.getMonth());
    ui->bDayYearSpinBox->setValue(bDate.getYear());

    Date currentDate = GetCurrentDate();
    ui->addDateDaySpinBox->setValue(currentDate.getDay());
    ui->addDateMonthSpinBox->setValue(currentDate.getMonth());
    ui->addDateYearSpinBox->setValue(currentDate.getYear());

    // Dont touch this BS
    // Birthday methods
    connect(ui->bDayMonthSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=]() {
        MonthSpinBox_valueChanged(ui->bDayDaySpinBox, ui->bDayMonthSpinBox, ui->bDayYearSpinBox);
    });

    connect(ui->bDayYearSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=]() {
        YearSpinBox_valueChanged(ui->bDayDaySpinBox, ui->bDayMonthSpinBox, ui->bDayYearSpinBox);
    });

    // Add new date methods
    connect(ui->addDateMonthSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=]() {
        MonthSpinBox_valueChanged(ui->addDateDaySpinBox, ui->addDateMonthSpinBox, ui->addDateYearSpinBox);
    });

    connect(ui->addDateYearSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=]() {
        YearSpinBox_valueChanged(ui->addDateDaySpinBox, ui->addDateMonthSpinBox, ui->addDateYearSpinBox);
    });

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

        filePath = fileName;
        qDebug() << "Table in file: " << filePath;

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
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
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

void MainWindow::on_bDayPushButton_clicked()
{
    int day = ui->bDayDaySpinBox->value();
    int month = ui->bDayMonthSpinBox->value();
    int year = ui->bDayYearSpinBox->value();
    bDate.setDate(day, month, year);
    qDebug() << "Birthday changed to " << bDate.DateToStr();
}

void MainWindow::MonthSpinBox_valueChanged(QSpinBox* spinBoxDay, QSpinBox* spinBoxMonth, QSpinBox* spinBoxYear)
{
    int month = spinBoxMonth->value();
    int maxDays = bDate.getMaxDaysInMonth(spinBoxMonth->value());
    int year = spinBoxYear->value();

    if(month == 2 && Date::IsLeapYear(year)){
        spinBoxDay->setMaximum(29);
    }else{
        spinBoxDay->setMaximum(maxDays);
    }
    qDebug() << "Max birthday Days changed to " << maxDays;
}


void MainWindow::YearSpinBox_valueChanged(QSpinBox* spinBoxDay, QSpinBox* spinBoxMonth, QSpinBox* spinBoxYear)
{
    int year = spinBoxYear->value();
    bool isLeap = Date::IsLeapYear(year);
    int month = spinBoxMonth->value();
    if(isLeap && month == 2){
        spinBoxDay->setMaximum(29);
    }else if(month == 2){
        spinBoxDay->setMaximum(28);
    }
}

vector<Date> MainWindow::erase(vector<Date> dateVector, int idx)
{
    vector<Date> newDateVector;
    for(int i = 0; i < dateVector.size(); ++i){
        if(i == idx){
            continue;
        }
        newDateVector.push_back(dateVector[i]);
    }
    return newDateVector;
}

void MainWindow::on_actionDeleteElement_triggered()
{
    bool ok;
    int index = QInputDialog::getInt(
        this,
        "Удаление элемента",
        "Введите индекс элемента для удаления:",
        1,
        1,
        ui->tableWidget->rowCount(),
        1,
        &ok
        );

    int tableSize = ui->tableWidget->rowCount();
    if(ok && tableSize > 0){
        if(rewriteMode){
            deleteDateFromFile(filePath, index - 1);
        }
        dates.removeAt(index - 1);
        dateVector = erase(dateVector, index - 1);
        ui->tableWidget->removeRow(index - 1);
        qDebug() << "Row " << index << " has been deleted";
        qDebug() << "QStringList size: " << dates.size();
        qDebug() << "vector<Date> dateVector size: " << dateVector.size();
    }else if(!deleteDateFromFile(filePath, index - 1)){
        QMessageBox::critical(this, "Ошибка", "Ошибка при удалении даты в файле!");
    }else{
        QMessageBox::critical(this, "Ошибка", "Невозможно удалить элемент из пустой таблицы!");
    }

}

bool MainWindow::deleteDateFromFile(const QString &filePath, int lineNumber)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        qDebug() << "Невозможно создать временный файл!";
        file.close();
        return false;
    }

    QTextStream in(&file);
    QTextStream out(&tempFile);
    int currentLine = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (currentLine != lineNumber) {
            out << line << "\n";
        }
        currentLine++;
    }

    file.close();
    tempFile.close();

    if(!file.remove()){
        qDebug() << "Невозможно удалить оригинальный файл!";
        return false;
    }

    if(!tempFile.copy(filePath)){
        qDebug() << "Невозможно копировать во временный файл!";
        return false;
    }

    return true;
}


void MainWindow::on_addDatePushButton_clicked()
{
    int day = ui->addDateDaySpinBox->value();
    int month = ui->addDateMonthSpinBox->value();
    int year = ui->addDateYearSpinBox->value();
    Date newDate(day, month, year);
    int idx = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(idx + 1);
    ui->tableWidget->setItem(idx, 0, new QTableWidgetItem(newDate.DateToStr()));

    dates.append(newDate.DateToStr());
    dateVector.push_back(newDate);

    if(rewriteMode){
        if(!addDateToFile(filePath, newDate)){
            qDebug() << "Ошибка при открытии файла при добавлении даты";
        }
    }

    qDebug() << "Добавлена дата: " << newDate.DateToStr();
}

bool MainWindow::addDateToFile(const QString &filePath, Date &date)
{
    QFile file(filePath);
    if(!file.open(QIODevice::Append | QIODevice::Text)){
        return false;
    }

    QTextStream out(&file);
    out << date.DateToStr() << '\n';
    file.close();
    return true;
}

void MainWindow::on_actionSave_triggered()
{
    if(rewriteMode){
        QMessageBox::warning(this, "Предупреждение", "Нечего сохранять т.к. включен Режим Перезаписи!");
        return;
    }

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Ошибка открытия файла!";
        return;
    }

    int tableSize = ui->tableWidget->rowCount();
    QTextStream out(&file);
    for(int i = 0; i < tableSize; ++i){
        out << dates[i] << '\n';
    }

    file.close();
    qDebug() << "Успешное сохранение!";
}



void MainWindow::on_actionRewriteFile_toggled(bool checked)
{
    rewriteMode = checked;
    qDebug() << "Rewrite enabled to " << rewriteMode;
}

