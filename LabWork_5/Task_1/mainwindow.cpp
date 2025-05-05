#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    keyboardWidget = new KeyboardWidget(this);
    keyboardWidget->setGeometry(20, 510, keyboardWidget->width(), keyboardWidget->height());
    keyboardWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    keyboardWidget->keyPressEvent(event);
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    keyboardWidget->keyReleaseEvent(event);
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::on_pushButtonOpenFile_clicked()
{
    isRunning = false;
    timer.stop();

    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выбрать файл", "", "*.txt");
    QFile file(filePath);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
        currentText = file.readAll();
        mask.fill('_', currentText.size());
        ui->textEdit->setText(currentText);
        file.close();

    } else {
        Utils::ShowErrorEvent("Файл не открыт или не существует!");
    }
}


void MainWindow::on_comboBoxLanguage_currentIndexChanged(int index)
{
    keyboardWidget->UpdateKeyboard((Language)index);
}

