#include "sortcontroller.h"

#include <QDebug>

SortController::SortController() {
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

void SortController::RandomNumberVectorGenerate(const int &size)
{
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    QVector<int> randomNumbers;

    for(int i = 0; i < size; ++i){
        int randomNum = rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER);
        while(randomNumbers.contains(randomNum)){
            randomNum = rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER);
        }
        randomNumbers.append(randomNum);
    }
    arr_ = randomNumbers;
}

bool SortController::IsSorted()
{
    for (int i = 1; i < arr_.size(); ++i){
        if (arr_[i] < arr_[i - 1]) return false;
    }
    return true;
}

void SortController::CreateNewArr()
{
    size = ui->spinBoxAmount->value();
    RandomNumberVectorGenerate(arr, size);
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

void SortController::OutputArray()
{
    QStringList numbers;
    for(const int num: arr_){
        numbers.append(QString::number(num));
    }
    qDebug() << "Массив: " <<numbers.join(',') << '\n';
}


void SortController::onSortTimerTimeout()
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


void SortController::ShowSort()
{
    sortTimer = new QTimer(this);
    sortTimer->setInterval(30);
    isUpdating = true;

    connect(sortTimer, &QTimer::timeout, this, &MainWindow::onSortTimerTimeout);
    sortTimer->start();
}
