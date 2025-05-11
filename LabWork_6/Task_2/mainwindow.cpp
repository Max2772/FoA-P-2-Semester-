#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utils.h"
#include <QString>
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
    }else if(mode == 2 || mode == 3){
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
    switch(mode){ // Cases 2,3 from QPushButton
    case 0:
        Task1();
        break;
    case 1:
        Task2();
        break;
    case 4:
        Task5();
        break;
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->plainTextEditInput && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Shift:
        case Qt::Key_Alt:
        case Qt::Key_Control:
        case Qt::Key_CapsLock:
        case Qt::Key_Escape:
            return true;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (keyEvent->modifiers() == Qt::NoModifier) {
                keyPressEvent(keyEvent);
                return true;
            }
            return true;
        default:
            return false;
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

    QString modelName = ui->plainTextEditModel->toPlainText().left(MAX_MODEL_NAME_CHARACTERS);
    if(modelName.isEmpty()){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    Motorcycle motorcycle = {mileage, maxSpeed, type, isDamaged, {}};
    strncpy(motorcycle.modelName, modelName.toUtf8().constData(), MAX_MODEL_NAME_CHARACTERS);
    motorcycle.modelName[MAX_MODEL_NAME_CHARACTERS - 1] = '\0';

    if(mode == 2){
        Task3(motorcycle);
    }else if(mode == 3){
        Task4(motorcycle);
    }
}

void MainWindow::Task3(const Motorcycle &motorcycle)
{
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

    qDebug() << "";
    file.close();
}

void MainWindow::Task4(const Motorcycle &motorcycle)
{
    QFile file("БибиковЛаб20_2.bin");
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для записи!");
        return;
    }

    file.write((char*)&motorcycle, sizeof(Motorcycle));
    file.close();

    Task4Print();
}

void MainWindow::Task4Print()
{
    QFile file("БибиковЛаб20_2.bin");
    if (!file.open(QIODevice::ReadOnly)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    Motorcycle motorcycle;

    int cnt = 1;
    while (file.read((char*)&motorcycle, sizeof(Motorcycle)) == sizeof(Motorcycle)) {
        QString result = QString("%1) %2;%3;%4;%5;%6\n")
                      .arg(cnt)
                      .arg(motorcycle.mileage)
                      .arg(motorcycle.maxSpeed)
                      .arg(motorcycle.type)
                      .arg(motorcycle.damaged ? "true" : "false")
                      .arg(QString::fromUtf8(motorcycle.modelName));
        qDebug().noquote() << result;
        ++cnt;
    }

    qDebug() << "";
    file.close();
}

void MainWindow::Task5()
{
    QFile file("БибиковЛаб20_3.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для записи!");
        return;
    }

    QString text = ui->plainTextEditInput->toPlainText().trimmed();
    QTextStream out(&file);

    out << text << '\n';

    file.close();
    qDebug() << text << " записано в " << file.fileName();

    Task5Print();
}

void MainWindow::Task5Print()
{
    QFile file("БибиковЛаб20_3.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utils::ShowErrorEvent("Невозможно открыть файл для чтения!");
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(text);

    file.close();
}
