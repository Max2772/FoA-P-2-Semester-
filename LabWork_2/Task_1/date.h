#ifndef DATE_H
#define DATE_H

#include <QString>
#include <cmath>
#include <QDebug>

class Date{
public:
    int day;
    int month;
    int year;
    bool isLeap;

    Date(int day, int month, int year){
        this->day = day;
        this->month = month;
        this->year = year;
        isLeap = IsLeap();
    }

    QString NextDay();
    QString PreviousDay();
    QString DateToStr();

    bool IsLeap();

    short WeekNumber();

    int DaysTillYourBirthday(Date bDate);
    int DateToDays(QString date, bool noYear);
    int DateToDays(int day, int month, int year);
    int Duration(Date date);
private:
    int daysInMonth[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif // DATE_H
