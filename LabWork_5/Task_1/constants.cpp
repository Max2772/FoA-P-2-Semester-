#include "constants.h"
#include <QVector>

const QString Keyboards[8][2] = {
    // English (0)
    {
        "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./",
        "~!@#$%^?*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?"
    },
    // Russian (1)
    {
        "`1234567890-=йцукенгшщзхъ\\фывапролджэячсмитьбю.",
        "~!@#$%^?*()_+ЙЦУКЕНГШЩЗХЪ|ФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,"
    },
    // German (2)
    {
        "`1234567890-=qwertzuiopü+\\asdfghjklöäyxcvbnm,./",
        "~!@#$%^?*()_+QWERTZUIOPÜ*|ASDFGHJKLÖÄ>YXCVBNM<>?"
    },
    // French (3)
    {
        "`1234567890-=azertyuiop^$\\qsdfghjklmùwxcvbn,;./",
        "~!@#$%^?*()_+AZERTYUIOP{}|QSDFGHJKLMÙ*WXCVBNM<>?"
    },
    // Arabic (4)
    {
        "`1234567890-=ضصثقفغعهخحجد\\شسيبلاتنمكطئءرزظد,;./",
        "~!@#$%^?*()_+ضصثقفغعهخحجد|شسيبلاتنمكطئءرزظد<>?"
    },
    // Chinese (5)
    {
        "`1234567890-=手田水口廿卜山戈人心[]\\日尸木火土竹十大中;'Ｚ難金女月弓一,./",
        "~!@#$%^?*()_+手田水口廿卜山戈人心{}|日尸木火土竹十大中:\"Ｚ難金女月弓一<>?"
    },
    // Belarusian (6)
    {
        "`1234567890-=йцукенгшўзх'\\фывапролджэячсмитьбю.",
        "~!@#$%^?*()_+ЙЦУКЕНГШЎЗХ\"|ФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,"
    },
    // Hebrew (7)
    {
        "`1234567890-=קראטוןםפ][\\שדגכעיחלךף,זסבהנמצתץ,./",
        "~!@#$%^?*()_+קראטוןםפ{}|שדגכעיחלךף:זסבהנמצתץ<>?"
    }
};

QString getLanguageName(int index)
{
    return LanguageNames[index];
}
