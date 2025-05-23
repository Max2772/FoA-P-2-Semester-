#include "date.h"

Date Date::NextDay() const
{
    Date nextDay = *this;
    int maxDays = daysInMonth[nextDay.month];
    if(IsLeapYear(nextDay.year) && nextDay.month == 2){
        maxDays = 29;
    }

    if(nextDay.day < maxDays){
        nextDay.day++;
    }else{
        nextDay.day = 1;
        if(nextDay.month == 12){
            nextDay.month = 1;
            nextDay.year++;
        }else{
            nextDay.month++;
        }
    }
    return nextDay;
}

Date Date::PreviousDay() const
{
    Date previousDay = *this;
    int maxDaysPreviousMonth = daysInMonth[previousDay.month-1];
    if(maxDaysPreviousMonth == 0){ // Проверка на январь
        maxDaysPreviousMonth = 31;
    }

    if(IsLeapYear(previousDay.year) && previousDay.month == 3){
        maxDaysPreviousMonth = 29;
    }

    if(previousDay.day > 1){
        previousDay.day--;
    }else{
        if(previousDay.month == 1){
            previousDay.month = 12;
            previousDay.year--;
            previousDay.day = maxDaysPreviousMonth;
        }else{
            previousDay.month--;
            previousDay.day = maxDaysPreviousMonth;
        }
    }

    return previousDay;
}

QString Date::DateToStr(){
    return QString("%1/%2/%3")
        .arg(day, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(year);
}

short Date::WeekNumber(){
    int monthDays = day;
    for(int i = 0; i < month; ++i){
        monthDays += daysInMonth[i];
    }

    return monthDays / 7 + 1;
}

int Date::DateToDays(const Date& date)
{
    int day = date.day, month = date.month, year = date.year;
    bool isLeap = IsLeapYear(year);
    int monthDays = 0;
    for(int i = 1; i < month; ++i){
        if(isLeap && i == 2)
            monthDays += 29;
        else
            monthDays += daysInMonth[i];
    }
    auto leap_count = year/4 - year/100 + year/400;
    auto no_leap_count = year - leap_count;

    return day + monthDays + no_leap_count * 365 + leap_count * 366;

}

int Date::DaysTillYourBirthday(const Date& date, const Date& bDate){

    bool isCurrentLeap = IsLeapYear(date.year);
    bool isNextYearLeap = IsLeapYear(bDate.year);

    Date bDateTemp = bDate;
    Date dateTemp = date;
    bDateTemp.year = 0;
    dateTemp.year = 0;

    if(dateTemp.month > bDate.month ||
      (dateTemp.month == bDateTemp.month && dateTemp.day > bDateTemp.day)){
        int daysToEndOfTheYear = (isCurrentLeap ? 366 : 365) - DateToDays(dateTemp);

        if(bDate.month == 2 && bDate.day == 29 && !isNextYearLeap){
            bDateTemp.day = 28;
        }

        int bDateDays = DateToDays(bDateTemp);
        return daysToEndOfTheYear + bDateDays;
    }

    return DateToDays(bDateTemp) - DateToDays(dateTemp);
}


int Date::Duration(const Date& givenDate)
{
    int daysGivenDate = DateToDays(givenDate);
    int daysThisDate = DateToDays(*this);

    int result = daysGivenDate - daysThisDate;

    return (result < 0 ? -result : result);
}

