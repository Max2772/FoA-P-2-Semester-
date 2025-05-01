#include "sortcontroller.h"
#include "sort.h"
#include "utils.h"

#include <QDebug>
#include <QElapsedTimer>

SortController::SortController(SortVisualizer *visualizer, QObject* parent) : QObject(parent) {
    sortTimer = new QTimer(this);
    searchTimer = new QTimer(this);
    sortVisualizer = visualizer;

    MAX_HEIGHT = sortVisualizer->height();

    connect(sortTimer, &QTimer::timeout, this, &SortController::onSortTimerTimeout);
    connect(searchTimer, &QTimer::timeout, this, &SortController::onSearchTimerTimeout);
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
    if(size < 1){
        qDebug() << "Размер не может быть < 1";
        Utils::ShowErrorEvent("Размер не может быть < 1!");
        return;
    }

    if (MAX_HEIGHT <= 0) {
        qDebug() << "Размер виджета сортировок не может быть <= 0!";
        Utils::ShowErrorEvent("Размер виджета сортировок не может быть <= 0!");
        return;
    }

    arr_.resize(size);
    rectsVector_.clear();
    motionVector_.clear();
    searchVector_.clear();

    RandomNumberVectorGenerate(size);
    OutputArray();

    rectsVector_ = sortVisualizer->createRects(arr_);

    idx1 = idx2 = -1;
    sortVisualizer->setRects(rectsVector_, idx1, idx2);
}

void SortController::Sort(){
    if (isUpdating || isSearching) {
        qDebug() << "Сортировка невозможна! Идёт другая операция!";
        Utils::ShowErrorEvent("Идёт другая операция!");
        return;
    }

    if(IsSorted()){
        qDebug() << "Массив уже отсортирован!";
        Utils::ShowInformationEvent("Массив уже отсортирован!");
        return;
    }

    QElapsedTimer timer;
    timer.start();
    motionVector_.clear();
    isUpdating = true;
    emit sortingStateChanged(true);

    qDebug() << "Interpolation Sort сортировка";
    Sort::InterpolationSort(arr_, motionVector_);
    int elapsedTime = timer.elapsed();
    emit sortTimeUpdated(elapsedTime);

    ShowSort();
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
    static int step = 0;

    if(step < motionVector_.size()){

        idx1 = motionVector_[step].first;
        idx2 = motionVector_[step].second;

        QRectF rect1(rectsVector_[idx2].x(), MAX_HEIGHT - rectsVector_[idx1].height(), 10, rectsVector_[idx1].height());
        QRectF rect2(rectsVector_[idx1].x(), MAX_HEIGHT - rectsVector_[idx2].height(), 10, rectsVector_[idx2].height());
        rectsVector_[idx1] = rect1;
        rectsVector_[idx2] = rect2;
        std::swap(rectsVector_[idx1], rectsVector_[idx2]);
        ++step;
    } else {
        isUpdating = false;
        sortTimer->stop();
        emit sortingStateChanged(false);
        idx1 = idx2 = -1;
        step = 0;
    }

    sortVisualizer->setRects(rectsVector_, idx1, idx2);
}


void SortController::ShowSort()
{
    if (!sortTimer || motionVector_.isEmpty()) {
        isUpdating = false;
        qDebug() << "SortTimer = null или motionVector пустой!";
        Utils::ShowErrorEvent("SortController.cpp Error:\nSortTimer = null или motionVector пустой!");
        return;
    }

    sortTimer->setInterval(SORT_ANIMATION_SPEED);
    isUpdating = true;
    sortTimer->start();
    emit sortingStateChanged(true);
}

// Binary Search
void SortController::BinarySearch(int value) {
    if (isUpdating || isSearching) {
        Utils::ShowErrorEvent("Идёт другая операция!");
        qDebug() << "Поиск невозможен: идёт сортировка или другой поиск";

        return;
    }
    if (!IsSorted()) {
        qDebug() << "Массив не отсортирован";
        Utils::ShowInformationEvent("Массив не отсортирован!");
        emit searchResult(-1);
        return;
    }

    searchVector_.clear();
    isSearching = true;
    emit searchStateChanged(true);

    int left = 0;
    int right = arr_.size() - 1;
    int foundIndex = -1;

    if (arr_[left] > value || arr_[right] < value) {
        qDebug() << "Число вне диапазона массива!";
        emit searchResult(-1);
        isSearching = false;
        emit searchStateChanged(false);
        return;
    }

    while (left <= right) {
        searchVector_.append({left, right});
        int mid = left + (right - left) / 2;
        if (arr_[mid] == value) {
            foundIndex = mid;
            searchVector_.append({mid, mid});
            break;
        }
        if (arr_[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (foundIndex >= 0) {
        const int MOD = 1000000007; // Стандартный модуль
        int result = Sort::BinaryPow(foundIndex, arr_.size(), MOD);
        emit searchResult(result); // index^n mod MOD
    } else {
        emit searchResult(-1);
    }

    if (!searchVector_.isEmpty()) {
        searchTimer->start(SERACH_ANIMATION_SPEED);
    }else {
        isSearching = false;
        emit searchStateChanged(false);
    }
}

void SortController::onSearchTimerTimeout() {
    static int step = 0;
    if (step < searchVector_.size()) {
        searchLeft = searchVector_[step].first;
        searchRight = searchVector_[step].second;
        searchMid = (searchLeft == searchRight) ? searchLeft : -1;
        step++;
    } else {
        searchLeft = searchRight = searchMid = -1;
        isSearching = false;
        searchTimer->stop();
        emit searchStateChanged(false);
        step = 0;
    }
    sortVisualizer->setSearchIndices(searchLeft, searchRight, searchMid);
}
