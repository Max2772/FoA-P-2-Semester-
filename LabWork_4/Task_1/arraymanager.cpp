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
