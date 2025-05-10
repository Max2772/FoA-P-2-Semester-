#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEditInput->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxMode_activated(int mode)
{
    switch(mode){
    case 0:
        mode = 0;
    case 1:
        mode = 1;
    case 2:
        mode = 2;
    case 3:
        mode = 3;
    case 4:
        mode = 4;
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

void MainWindow::Task1()
{
    QFile file("БибиковЛаб20.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    QString text = ui->plainTextEditInput->toPlainText().trimmed();
    QTextStream out(&file);

    for (QChar ch: text) {
        out << ch;
        out.flush();
    }

    qDebug() << text << " записано в " << file.fileName();

    file.close();
}

void MainWindow::Task2()
{

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

