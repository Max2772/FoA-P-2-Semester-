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

int Date::DateToDays(QString date, bool noYear)
{
    int day = 0, month = 0, year = 0;
    day = date.mid(0,2).toInt();

    month = date.mid(3,2).toInt();
    int monthDays = 0;
    for(int i = 0; i < month; ++i){
        monthDays += daysInMonth[i];
    }

    if(noYear){
        return day + monthDays;
    }else{
        year = date.mid(6,date.length() - 5).toInt();
        qDebug() << year;
        return day + monthDays + year * 365;
    }
}

int Date::DateToDays(int day, int month, int year)
{
    int monthDays = 0;
    for(int i = 0; i < month; ++i){
        monthDays += daysInMonth[i];
    }

    return day + monthDays + year * 365;
}

int Date::DaysTillYourBirthday(Date bDate){
    if(month > bDate.month || (month == bDate.month && day > bDate.day)){
        return 365 - DateToDays(bDate.day, bDate.month, 0) - DateToDays(day, month, 0);
    }

    return abs(DateToDays(bDate.day, bDate.month, 0) - DateToDays(day, month, 0));
}


int Date::Duration(Date date)
{
    int dateDays = DateToDays(date.day, date.month, date.year);
    int currentDays = DateToDays(day , month, year);

    return abs(dateDays - currentDays);
}




/*

    QString currentDateStr = QString("%1/%2/%3")
                              .arg(day, 2, 10, QChar('0'))
                              .arg(month, 2, 10, QChar('0'))
                              .arg(year);
*/

