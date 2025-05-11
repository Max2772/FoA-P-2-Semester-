#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CheckElementsUI(false);
    CheckIOUI(true);

    ui->plainTextEditInput->installEventFilter(this);

    connect(ui->pushButtonExit, &QPushButton::clicked, qApp, &QApplication::quit);

    mode = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxMode_activated(int mode)
{

    if(mode == 1){
        CheckElementsUI(true);
        CheckIOUI(true);
    }else if(mode == 2){
        CheckIOUI(false);
        CheckElementsUI(false);
    }else{
        CheckIOUI(true);
        CheckElementsUI(false);
    }


    switch(mode){
    case 0:
        this->mode = 0;
        break;
    case 1:
        this->mode = 1;
        break;
    case 2:
        this->mode = 2;
        break;
    case 3:
        this->mode = 3;
        break;
    case 4:
        this->mode = 4;
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(mode){
    case 0:
        Task1();
        break;
    case 1:
        Task2();
        break;
    case 2:
        Task3();
        break;
    case 3:
        Task4();
        break;
    case 4:
        Task5();
        break;
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->plainTextEditInput && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
            keyPressEvent(keyEvent);
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}

void MainWindow::CheckElementsUI(bool on)
{
    ui->labelElementsInfo->setVisible(on);
    ui->spinBoxElements->setVisible(on);
}

void MainWindow::CheckIOUI(bool on)
{
    if(on){
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::Task1()
{
    QFile file("БибиковЛаб20.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для записи!");
        return;
    }

    QString text = ui->plainTextEditInput->toPlainText().trimmed();
    QTextStream out(&file);

    for (QChar ch: text) {
        out << ch;
    }

    file.close();
    qDebug() << text << " записано в " << file.fileName();

    Task1Print();
}

void MainWindow::Task1Print()
{
    QFile file("БибиковЛаб20.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    ui->plainTextEditOutput->clear();
    for(QChar ch: text){
        ui->plainTextEditOutput->setPlainText(ui->plainTextEditOutput->toPlainText() + ch);
    }

    file.close();
}

void MainWindow::Task2()
{
    QFile file("БибиковЛаб20_0.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для записи!");
        return;
    }

    QStringList arr = ui->plainTextEditInput->toPlainText().trimmed().split(' ');
    int size = ui->spinBoxElements->value();
    QString text;

    for (int i = 0; i < size && i < arr.size(); ++i) {
        bool ok;
        int num = arr[i].toInt(&ok);
        ok ? text += QString::number(num) + SPLITTER : text += QString("0") + SPLITTER;
    }

    file.write(text.toUtf8());
    file.close();
    qDebug() << text << " записано в " << file.fileName();

    Task2Print();
}

void MainWindow::Task2Print()
{
    QFile file("БибиковЛаб20_0.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    QTextStream in(&file);
    QString text;
    in >> text;

    QStringList arr = text.split(SPLITTER);

    ui->plainTextEditOutput->clear();
    for(QString num : arr){
        ui->plainTextEditOutput->setPlainText(ui->plainTextEditOutput->toPlainText() + " " + num);
    }

    file.close();
}

void MainWindow::Task3()
{

}

void MainWindow::Task4()
{

}

void MainWindow::Task5()
{

}

