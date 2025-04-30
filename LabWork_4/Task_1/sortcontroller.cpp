#include "sortcontroller.h"
#include "sort.h"

#include <QDebug>

SortController::SortController(QObject* parent) : QObject(parent) {
    sortTimer = new QTimer(this); // Инициализируем таймер
    sortVisualizer = new SortVisualizer; // Инициализируем визуализатор

    connect(sortTimer, &QTimer::timeout, this, &SortController::onSortTimerTimeout);

    QTimer* updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, [=]() {
        qDebug() << "Update timer ticked";
    });
    updateTimer->start(30);
}

SortController::~SortController()
{
    delete sortTimer;
    delete sortVisualizer;
}

void SortController::RandomNumberVectorGenerate(int size)
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

void SortController::CreateNewArr(int size)
{
    RandomNumberVectorGenerate(size);
    rectsVector_.clear();
    motionVector_.clear();

    int maxHeight = sortVisualizer->height(); // Используем высоту CanvasWidget

    for (int i = 0; i < size; ++i) {
        QRectF rect(30 + 10 * i, maxHeight - (20 + 4 * arr_[i]), 10, 20 + 4 * arr_[i]);
        rectsVector_.append(rect);
    }

    idx1 = idx2 = -1;
    sortVisualizer->setRects(rectsVector_, idx1, idx2);

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

    if (step < motionVector_.size()) {
        // Получаем индексы для обмена
        idx1 = motionVector_[step].first;
        idx2 = motionVector_[step].second;

        // Меняем местами прямоугольники, сохраняя их высоту
        QRectF rect1(rectsVector_[idx2].x(), sortVisualizer->height() - rectsVector_[idx1].height(), 10, rectsVector_[idx1].height());
        QRectF rect2(rectsVector_[idx1].x(), sortVisualizer->height() - rectsVector_[idx2].height(), 10, rectsVector_[idx2].height());
        rectsVector_[idx1] = rect1;
        rectsVector_[idx2] = rect2;
        std::swap(rectsVector_[idx1], rectsVector_[idx2]);
        ++step;
    } else {
        // Завершаем анимацию
        isUpdating = false;
        sortTimer->stop();
        idx1 = idx2 = -1;
        step = 0; // Сбрасываем для следующей сортировки
    }

    // Обновляем визуализатор
    sortVisualizer->setRects(rectsVector_, idx1, idx2);
}


void SortController::ShowSort()
{
    if (!sortTimer || motionVector_.isEmpty()) {
        isUpdating = false;
        return; // Проверка на валидность таймера и движений
    }

    sortTimer->setInterval(30);
    isUpdating = true;
    sortTimer->start();
}

void SortController::QuickSort(){
    Sort::QuickSort(arr_, 0, arr_.size() - 1, motionVector_);
    ShowSort();
}
