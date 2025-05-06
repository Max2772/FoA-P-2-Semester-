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

    isTextOpened = false;
    isRunning = false;

    timer = new QTimer(this);
    time = QTime(0, 0);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    keyboardWidget = new KeyboardWidget(this);
    keyboardWidget->setGeometry(20, 510, keyboardWidget->width(), keyboardWidget->height());
    keyboardWidget->show();

    connect(keyboardWidget, &KeyboardWidget::keyPressed, this, &MainWindow::onKeyPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!isTextOpened) {
        event->ignore();
        return;
    }

    switch (event->key()) {
    case Qt::Key_Shift:
    case Qt::Key_Alt:
    case Qt::Key_Control:
    case Qt::Key_CapsLock:
    case Qt::Key_Escape:
        keyboardWidget->keyPressEvent(event);
        return;
    }

    if(event->key() == Qt::Key_Backspace && isRunning){
        if(currentIdx != 0){
            --currentIdx;
            mask[currentIdx] = '_';
            HighlightLetter(currentIdx, Qt::gray);
            keyboardWidget->keyPressEvent(event);
            return;
        }
        event->ignore();
        return;
    }

    if(!isRunning && currentIdx == 0) {
        isRunning = true;
        timer->start(1000);
        CheckSymbol(event->text());
        updateAccuracy();
        updateSpeed();
        keyboardWidget->keyPressEvent(event);
        return;
    }

    if(isRunning){
        CheckSymbol(event->text());
        updateAccuracy();
        updateSpeed();
        keyboardWidget->keyPressEvent(event);
        if(mask.indexOf('_') == -1){
            timer->stop();
            isRunning = false;
            QString resultMessage = QString("Результат:\nВремя: %1\nТочность: %2\nСкорость: %3")
                                                .arg(ui->labelTime->text())
                                                .arg(ui->labelAccuracy->text())
                                                .arg(ui->labelSpeed->text());
            Utils::ShowInformationEvent(resultMessage);
        }
        return;
    }

    QMainWindow::keyPressEvent(event);
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
        isTextOpened = true;
        ProgressReset();
    } else {
        Utils::ShowErrorEvent("Файл не открыт или не существует!");
    }
}


void MainWindow::on_comboBoxLanguage_currentIndexChanged(int index)
{
    keyboardWidget->UpdateKeyboard((Language)index);
    currentText = ExampleTexts[index];
    ui->textEdit->setText(currentText);

    timer->stop();
    isTextOpened = true;
    ProgressReset();
}

void MainWindow::updateTimer()
{
    time = time.addSecs(1);
    ++seconds;
    ui->labelTime->setText(time.toString("m:ss"));
}


void MainWindow::updateAccuracy()
{
    int correct = 0;
    int incorrect = 0;
    for(int i = 0; i < mask.size(); ++i){
        if(mask[i] == 'y') ++correct;
        if(mask[i] == 'n') ++incorrect;
    }
    double result = (correct / (double)(correct + incorrect)) * 100;
    ui->labelAccuracy->setText(QString("%1%").arg(result, 0, 'f', 2));
}

void MainWindow::updateSpeed()
{
    int correct = 0;
    for(int i = 0; i < mask.size(); ++i){
        if(mask[i] == 'y') ++correct;
    }

    int result;
    if(seconds == 0)
        result = 0;
    else{
        result = correct * 6 / seconds;
    }

    ui->labelSpeed->setText(QString("%1 сл/мин").arg(result));
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
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    QTextCharFormat format;
    format.setForeground(color);
    cursor.mergeCharFormat(format);
}

void MainWindow::ProgressReset()
{
    mask.fill('_', currentText.size());
    currentIdx = 0;
    seconds = 0;
    isRunning = false;
    time = QTime(0, 0);

    keyboardWidget->ResetKeyboard();
    ui->textEdit->setPlainText(ui->textEdit->toPlainText());
    ui->labelTime->setText("00:00");
    ui->labelAccuracy->setText("0%");
    ui->labelSpeed->setText("0 сл/мин");
}


void MainWindow::on_pushButtonPause_clicked(bool checked)
{
    isRunning = !checked;
    if(!isRunning)
        timer->stop();
    else
        timer->start(1000);
}


void MainWindow::on_pushButtonRestart_clicked()
{
    timer->stop();
    ProgressReset();
}

void MainWindow::onKeyPressed(const QString &text)
{
    if (!isTextOpened) {
        return;
    }

    if (!isRunning && currentIdx == 0) {
        isRunning = true;
        timer->start(1000);
        CheckSymbol(text);
        updateAccuracy();
        updateSpeed();
        return;
    }

    if (isRunning) {
        if(text == "⌫" || text == "⇧" || text == "Caps"){
            if(text == "⌫" && currentIdx != 0){
                    --currentIdx;
                    mask[currentIdx] = '_';
                    HighlightLetter(currentIdx, Qt::gray);
            }else if (text == "⇧"){
                keyboardWidget->SetShiftButtonFromMain();
            }else{
                keyboardWidget->SetCapsButtonFromMain();
            }
            return;
        }

        CheckSymbol(text);
        updateAccuracy();
        updateSpeed();
        if (mask.indexOf('_') == -1) {
            timer->stop();
            isRunning = false;
            QString resultMessage = QString("Результат:\nВремя: %1\nТочность: %2\nСкорость: %3")
                                        .arg(ui->labelTime->text())
                                        .arg(ui->labelAccuracy->text())
                                        .arg(ui->labelSpeed->text());
            Utils::ShowInformationEvent(resultMessage);
        }
    }
    return;
}

