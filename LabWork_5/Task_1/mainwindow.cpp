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
    if(event->key() == Qt::Key_Shift) keyboardWidget->keyPressEvent(event);

    CheckSymbol(event->text());

    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift) keyboardWidget->keyReleaseEvent(event);

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
        ui->textEdit->setText(currentText);
        file.close();
        ProgressReset();
    } else {
        Utils::ShowErrorEvent("Файл не открыт или не существует!");
    }
}


void MainWindow::on_comboBoxLanguage_currentIndexChanged(int index)
{
    keyboardWidget->UpdateKeyboard((Language)index);
}

void MainWindow::CheckSymbol(QString symbol)
{
    if(symbol == currentText[currentIdx]){
        mask[currentIdx] = 'y';
        HighlightLetter(currentIdx, Qt::green);
    }else{
        mask[currentIdx] = 'n';
        HighlightLetter(currentIdx, Qt::red);
    }
    ++currentIdx;
}

void MainWindow::HighlightLetter(int position, const QColor &color)
{
    QTextCursor cursor(ui->textEdit->document());
    cursor.setPosition(position);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor); // Выделяем 1 символ

    QTextCharFormat format;
    format.setForeground(color);
    cursor.mergeCharFormat(format);
}

void MainWindow::ProgressReset()
{
    mask.fill('_', currentText.size());
    currentIdx = 0;
}

