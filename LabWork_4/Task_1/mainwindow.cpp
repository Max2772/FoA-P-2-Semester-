#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QPainter>

#include "sort.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);

    sortVisualizer = new SortVisualizer(this);
    sortVisualizer->setGeometry(0, 0, width(), height() - 200); // Оставляем место для UI
    sortVisualizer->lower(); // Позади centralWidget
    ui->centralwidget->lower(); // Поднимаем centralWidget

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        update(); // Перерисовка окна
        ui->pushButtonSort->setEnabled(!isUpdating);
        ui->spinBoxAmount->setEnabled(!isUpdating);
        if (size != ui->spinBoxAmount->value() && !isUpdating) {
            size = ui->spinBoxAmount->value();
            CreateNewArr();
        }
    });
    timer->start(30);

}

MainWindow::~MainWindow()
{
    for(QRectF *rect : rectsVector) delete rect;
    delete ui;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    arrayManager.RandomNumberVectorGenerate(arr, num);
    OutputArray();
}


void MainWindow::on_pushButtonSort_clicked(){
    motionVector.clear();
    Sort::QuickSort(arr, 0, arr.size() - 1, motionVector);
    ShowSort();
    OutputArray();
}

void MainWindow::OutputArray()
{
    QStringList numbers;
    for(const int num: arr){
        numbers.append(QString::number(num));
    }
    qDebug() << numbers.join(',');
}

// Здесь пздц -->

void MainWindow::CreateNewArr()
{
    size = ui->spinBoxAmount->value();
    arrayManager.RandomNumberVectorGenerate(arr, size);
    for (QRectF *rect : rectsVector) delete rect;
    rectsVector.clear();
    motionVector.clear();

    int maxHeight = sortVisualizer->height(); // Используем высоту CanvasWidget

    for (int i = 0; i < size; ++i) {
        QRectF *rect = new QRectF(30 + 10 * i, maxHeight - (20 + 4 * arr[i]), 10, 20 + 4 * arr[i]);
        rectsVector.append(rect);
    }

    ind1 = ind2 = -1;
    sortVisualizer->setRects(rectsVector, ind1, ind2);
    OutputArray();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.drawRect(50, 50, 50, 50);
    int vertical_offset = height() - ui->groupBox->height() + 1; // Смещение вниз

    QPen pen(Qt::white, 1); // Чёрная обводка толщиной 1 пиксель
    painter.setPen(pen);

    for (int i = 0; i < rectsVector.size(); ++i) {
        QRectF rect = *rectsVector[i];
        rect.moveBottom(vertical_offset); // Смещение столбца вниз
        // Подсветка активных элементов
        if (i == ind1 || i == ind2) {
            painter.setBrush(Qt::green);
        } else {
            painter.setBrush(Qt::white);
        }
        painter.drawRect(rect);
    }
}

void MainWindow::ShowSort()
{
    int *i = new int(0);
    sortTimer = new QTimer(this);
    sortTimer->setInterval(30);
    isUpdating = true;

    connect(sortTimer, &QTimer::timeout, [=]() {
        if (*i < motionVector.size()) {
            ind1 = motionVector[*i].first;
            ind2 = motionVector[*i].second;

            QRectF *rect1 = new QRectF(rectsVector[ind2]->x(), sortVisualizer->height() - rectsVector[ind1]->height(), 10, rectsVector[ind1]->height());
            QRectF *rect2 = new QRectF(rectsVector[ind1]->x(), sortVisualizer->height() - rectsVector[ind2]->height(), 10, rectsVector[ind2]->height());
            delete rectsVector[ind1];
            delete rectsVector[ind2];
            rectsVector[ind1] = rect1;
            rectsVector[ind2] = rect2;
            std::swap(rectsVector[ind1], rectsVector[ind2]);
            (*i)++;
        } else {
            isUpdating = false;
            sortTimer->stop();
            ind1 = ind2 = -1;
            delete i;
            delete sortTimer;
        }
        sortVisualizer->setRects(rectsVector, ind1, ind2);
    });
    sortTimer->start();
}
