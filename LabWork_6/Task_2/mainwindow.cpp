#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"
#include <QDebug>
#include "motorcycle.h"

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
        // From QPushButton
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
        long int num = arr[i].toLong(&ok);
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

void MainWindow::on_pushButtonAddElement_clicked()
{
    int mileage = ui->spinBoxMileageInfo->value();
    if(mileage == 0){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    double maxSpeed = ui->doubleSpinBoxMaxSpeed->value();
    if(maxSpeed == 0){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    char type;
    if (ui->radioButtonTypeS->isChecked()) {
        type = 'S';
    } else if (ui->radioButtonTypeC->isChecked()){
        type = 'C';
    } else if (ui->radioButtonTypeT->isChecked()) {
        type = 'T';
    } else if (ui->radioButtonTypeA->isChecked()) {
        type = 'A';
    } else if (ui->radioButtonTypeD->isChecked()) {
        type = 'D';
    }else{
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    bool isDamaged = ui->checkBoxIsDamaged->isChecked() ? true : false;

    QString modelName = ui->plainTextEditModel->toPlainText().left(MAX_MODEL_NAME_CHARACTES);
    if(modelName.isEmpty()){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    Motorcycle motorcycle = {mileage, maxSpeed, type, isDamaged, modelName};

    QFile file("БибиковЛаб20_1.txt");
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для записи!");
        return;
    }

    QTextStream out(&file);
    out << motorcycle.mileage << SPLITTER << motorcycle.maxSpeed << SPLITTER
        << motorcycle.type << SPLITTER << motorcycle.damaged << SPLITTER
        << motorcycle.modelName << '\n';

    file.close();
    Task3Print();
}

void MainWindow::Task3Print()
{
    QFile file("БибиковЛаб20_1.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    QTextStream in(&file);

    int cnt = 1;
    while (!in.atEnd()) {
        QStringList parts = in.readLine().trimmed().split(SPLITTER);
        QString result;
        for(int i = 0 ; i < parts.size(); ++i){
            if(i == parts.size() - 1){
                result += parts[i];
            }else{
                result += parts[i] + SPLITTER_STRUCT;
            }
        }

        result = QString::number(cnt) + QString(") ") + result;
        qDebug().noquote() << result;
        ++cnt;
    }
}

void MainWindow::Task4()
{

}

void MainWindow::Task5()
{

}
