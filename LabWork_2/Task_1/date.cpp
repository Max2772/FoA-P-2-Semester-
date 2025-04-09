#include "date.h"

QString Date::NextDay()
{
    QString str = QString::number(day + 1);
    return str;
}

QString Date::PreviousDay()
{
    QString str = QString::number(day - 1);
    return str;
}

QString Date::DateToStr(){
    QString str = QString::number(day) + '/' + QString::number(month) + '/' + QString::number(year);
    return str;
}

bool Date::IsLeap()
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        return true;
    }
    return false;
}


short Date::WeekNumber(){
    int monthDays = day;
    for(int i = 0; i < month; ++i){
        monthDays += daysInMonth[i];
    }
    return monthDays / 7;
}

int Date::DateToDays(QString date)
{
    int day = 0, month = 0, year = 0;
    day = date.mid(0,1).toInt();

    month = date.mid(3,4).toInt();
    int monthDays = 0;
    for(int i = 0; i < month; ++i){
        monthDays += daysInMonth[i];
    }

    year = date.mid(6,date.length()).toInt();

    return day + monthDays + year * 365;
}

int Date::DaysTillYourBirthday(QString bDay){
    int birthdayDays = DateToDays(bDay);
    QString currentDateStr = QString("%1/%2/%3")
                              .arg(day, 2, 10, QChar('0'))
                              .arg(month, 2, 10, QChar('0'))
                              .arg(year);
    int currentDateDays = DateToDays(currentDateStr);
    return currentDateDays - birthdayDays;
}

