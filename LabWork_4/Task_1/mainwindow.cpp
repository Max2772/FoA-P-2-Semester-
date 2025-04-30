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
    sortVisualizer->setGeometry(0, 0, width(), height() - ui->groupBox->height());
    qDebug() << ui->groupBox->height() << '/' << height();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        update();
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
    qDebug() << "Массив: " <<numbers.join(',') << '\n';
}

// Здесь пздц -->

void MainWindow::CreateNewArr()
{
    size = ui->spinBoxAmount->value();
    arrayManager.RandomNumberVectorGenerate(arr, size);
    rectsVector.clear();
    motionVector.clear();

    int maxHeight = sortVisualizer->height(); // Используем высоту CanvasWidget

    for (int i = 0; i < size; ++i) {
        QRectF rect(30 + 10 * i, maxHeight - (20 + 4 * arr[i]), 10, 20 + 4 * arr[i]);
        rectsVector.append(rect);
    }

    idx1 = idx2 = -1;
    sortVisualizer->setRects(rectsVector, idx1, idx2);
    OutputArray();
}

void MainWindow::ShowSort()
{
    sortTimer = new QTimer(this);
    sortTimer->setInterval(30);
    isUpdating = true;

    connect(sortTimer, &QTimer::timeout, this, &MainWindow::onSortTimerTimeout);
    sortTimer->start();
}

void MainWindow::onSortTimerTimeout()
{
    static int step = 0; // Сохраняет текущий шаг анимации между вызовами

    if (step < motionVector.size()) {
        // Получаем индексы для обмена
        idx1 = motionVector[step].first;
        idx2 = motionVector[step].second;

        // Меняем местами прямоугольники, сохраняя их высоту
        QRectF rect1(rectsVector[idx2].x(), sortVisualizer->height() - rectsVector[idx1].height(), 10, rectsVector[idx1].height());
        QRectF rect2(rectsVector[idx1].x(), sortVisualizer->height() - rectsVector[idx2].height(), 10, rectsVector[idx2].height());
        rectsVector[idx1] = rect1;
        rectsVector[idx2] = rect2;
        std::swap(rectsVector[idx1], rectsVector[idx2]);
        ++step;
    } else {
        // Завершаем анимацию
        isUpdating = false;
        sortTimer->stop();
        idx1 = idx2 = -1;
        delete sortTimer;
        sortTimer = nullptr;
        step = 0; // Сбрасываем для следующей сортировки
    }

    // Обновляем визуализатор
    sortVisualizer->setRects(rectsVector, idx1, idx2);
}
