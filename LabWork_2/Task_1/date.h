#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QDebug>
#include <QRegularExpression>

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

    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    int getMaxDaysInMonth(int month) const{
        return daysInMonth[month];
    }

    void setDate(int d, int m, int y){
        day = d;
        month = m;
        year = y;
    }

    Date NextDay() const;
    Date PreviousDay() const;
    QString DateToStr();

    short WeekNumber();

    int DaysTillYourBirthday(const Date& date, const Date& bDate);
    int DateToDays(const Date& date);
    int Duration(const Date& givenDate);

    static bool DateIsValid(const QString& date)
    {
        QStringList parts = date.split(QRegularExpression("[/.]"));
        if (parts.size() != 3) return false;

        int day = parts[0].toInt();
        if (parts[0].length() != 2 || day < 1 || day > 31) return false;

        int month = parts[1].toInt();
        if (parts[1].length() != 2 || month < 1 || month > 12) return false;

        int year = parts[2].toInt();
        if (parts[2].length() != 4 || year < 0) return false;

        return true;
    }

private:
    int day;
    int month;
    int year;
    const int daysInMonth[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif // DATE_H
