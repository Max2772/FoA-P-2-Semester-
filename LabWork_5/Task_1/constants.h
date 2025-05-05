#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

enum Language{
    English = 0,
    Russian = 1,
    German = 2,
    French = 3,
    Arabic = 4,
    Chinese = 5,
    Belarusian = 6,
    Hebrew = 7
};

const QString LanguageNames[] = {
    "English",
    "Russian",
    "German",
    "French",
    "Arabic",
    "Chinese",
    "Belarusian",
    "Hebrew"
};

QString getLanguageName(int index);

extern const QString Keyboards[8][2];


#endif // CONSTANTS_H
