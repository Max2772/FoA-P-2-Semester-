#include "arraymanager.h"

ArrayManager::ArrayManager() {}

void ArrayManager::RandomNumberVectorGenerate(QVector<int>& arr, int size)
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
    arr = randomNumbers;
}

bool ArrayManager::IsSorted(const QVector<int> &arr)
{
    for (int i = 1; i < arr.size(); ++i){
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}
