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

    isFileOpened = false;

    timer = new QTimer(this);
    time = QTime(0, 0);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

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
    if(!isFileOpened){
        event->ignore();
        return;
    }

    switch (event->key()) {
    case Qt::Key_Shift:
    case Qt::Key_Alt:
    case Qt::Key_Control:
    case Qt::Key_CapsLock:
    case Qt::Key_Tab:
    case Qt::Key_Escape:
        keyboardWidget->keyPressEvent(event);
        return;
    }

    if(!isRunning){
        isRunning = true;
        timer->start(1000);
        CheckSymbol(event->text());
        updateAccuracy();
    }

    if(isRunning){
        CheckSymbol(event->text());
        updateAccuracy();
        qDebug() << mask;
        if(mask.indexOf('_') == -1){
            timer->stop();
            isRunning = false;
            QString resultMessage = QString("Результат:\nВремя: %1\nТочность: %2\nСкорость: Нихуя")
                .arg(time.toString("mm:ss"))
                .arg(ui->labelAccuracy->text());
            Utils::ShowInformationEvent(resultMessage);
        }
    }

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
    timer->stop();

    QString filePath = QFileDialog::getOpenFileName(nullptr, "Выбрать файл", "", "*.txt");
    QFile file(filePath);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
        currentText = file.readAll();
        ui->textEdit->setText(currentText);
        file.close();
        isFileOpened = true;
        ProgressReset();
    } else {
        Utils::ShowErrorEvent("Файл не открыт или не существует!");
    }
}


void MainWindow::on_comboBoxLanguage_currentIndexChanged(int index)
{
    keyboardWidget->UpdateKeyboard((Language)index);
}

void MainWindow::updateTimer()
{
    time = time.addSecs(1);
    ui->labelTime->setText(time.toString("m:ss"));
}

void MainWindow::updateAccuracy()
{
    int correct = 0;
    int incorrect = 0;
    for(int i = 0; i < mask.size(); ++i){
        if(mask[i] == 'y')
            ++correct;
        if(mask[i] == 'n')
            ++incorrect;
    }
    double result = (correct / (double)(correct + incorrect)) * 100;
    ui->labelAccuracy->setText(QString("%1%").arg(result, 0, 'f', 2));
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

