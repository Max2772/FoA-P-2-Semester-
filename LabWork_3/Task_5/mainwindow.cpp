#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowErrorEvent(const QString &info) {
    QMessageBox box;
    box.setWindowTitle("Ошибка");
    box.setText(info);
    box.setIcon(QMessageBox::Critical);
    box.exec();
}

// void MainWindow::on_pushButton_clicked()

// {
// QString selectedDirectory = QFileDialog::getExistingDirectory(
//     this, "Выберите папку", QDir::homePath());

// QFile file(selectedDirectory);

// ui->label_2->setText(selectedDirectory);

// ui->label_4->setText(
//     QString::number(solution->getNumberFoldersAndFiles(selectedDirectory)));

// ui->label_5->setText(
//     QString::number(solution->getNumberFolders(selectedDirectory)));

void MainWindow::on_pushButtonCalculate_clicked()
{
    QString selectedDirectory = QFileDialog::getExistingDirectory(
        this, "Выберите хуй", QDir::homePath());

    if(selectedDirectory.isEmpty()){
        ShowErrorEvent("Не выбрана валидная папка!");
        return;
    }

    ui->labelCurrentDirectory->setText("Текущий путь: " + selectedDirectory);

    SetNameFiltersForSolution();

    QStringList nameFilters = solution.getNameFilters();
    if(nameFilters.isEmpty()){
        ui->labelInputFiles->setText("Количество файлов в данной директории:  " +
                                     QString::number(solution.GetNumberOfFoldersAndFiles(selectedDirectory)));
    }

    ui->labelInputFiles->setText("Количество " + nameFilters.join(',') +  " файлов в данной директории: " +
                                 QString::number(solution.GetNumberOfFoldersAndFiles(selectedDirectory)));
    ui->labelInputSubFolders->setText("Количество папок в данной директории: " +
                                      QString::number(solution.GetNumberOfFolders(selectedDirectory)));
}

void MainWindow::SetNameFiltersForSolution(){
    QString text = ui->lineEditInput->text();
    QStringList nameFilters = text.trimmed().toLower().split(",", Qt::SkipEmptyParts);

    for(int i = 0; i < nameFilters.size(); ++i){
        nameFilters[i] = QString('*') + nameFilters[i].trimmed();
    }

    QStringList CheckedNameFilters;
    for(const QString &filter : nameFilters){
        if(solution.IsValidFilter(filter)){
            CheckedNameFilters.append(filter);
        }
    }

    if(CheckedNameFilters.isEmpty()){
        qDebug() << "Поиск всех файлов без фильтров";
    }else{
        qDebug() << "Фильтры для файлов: " << CheckedNameFilters;
    }
    solution.setNameFilters(CheckedNameFilters);;
}


