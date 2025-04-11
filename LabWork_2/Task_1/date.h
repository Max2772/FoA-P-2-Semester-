#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QDebug>

class Date{
public:
    Date(int day, int month, int year){
        this->day = day;
        this->month = month;
        this->year = year;
    }

    static bool IsLeapYear(int year)
    {
        return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    }


    Date NextDay() const;
    Date PreviousDay() const;
    QString DateToStr();


    bool StringDateIsCorrect(QString line);

    short WeekNumber();

    int DaysTillYourBirthday(const Date& date, const Date& bDate);
    int DateToDays(Date& date) const;
    int DateToDays(int day, int month, int year);
    int Duration(Date& date);
private:
    int day;
    int month;
    int year;
    const int daysInMonth[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif // DATE_H
