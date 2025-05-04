#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "keyboardwidget.h"

#include "utils.h"
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    KeyboardWidget *keyboardWidget = new KeyboardWidget(this);
    keyboardWidget->setGeometry(20, 510, keyboardWidget->width(), keyboardWidget->height());
    keyboardWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOpenFile_clicked()
{
    isRunning = false;
    timer.stop();

    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выбрать файл", "", "*.txt");
    QFile file(filePath);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
        currentText = file.readAll();
        ui->textEdit->setText(currentText);
        file.close();

    } else {
        Utils::ShowErrorEvent("Файл не открыт или не существует!");
    }
}

