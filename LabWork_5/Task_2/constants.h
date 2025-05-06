#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString functionName[]{
        "memcpy",
        "memmove",
        "strcpy",
        "strncpy",
        "strcat",
        "strncat",
        "memcmp",
        "strcmp",
        "strcoll",
        "strncmp",
        "strxfrm",
        "strtok",
        "memset",
        "strerror",
        "strlen"
};

const QString functionExample[] = {
    // 1. memcpy
    "s1=Hello, s2=Buffer, n=3",
    // 2. memmove
    "s1=Hello, s2=Buffer, n=3",
    // 3. strcpy
    "s1=, s2=World",
    // 4. strncpy
    "s1=Hello, s2=World, n=3",
    // 5. strcat
    "s1=Hello, , s2=World",
    // 6. strncat
    "s1=Hello, , s2=World, n=3",
    // 7. memcmp
    "s1=abc, s2=abd, n=3",
    // 8. strcmp
    "s1=abc, s2=abc",
    // 9. strcoll
    "s1=абв, s2=где",
    // 10. strncmp
    "s1=Hello, s2=Hel, n=3",
    // 11. strxfrm
    "s1=, s2=абв, n=10",
    // 12. strtok
    "s1=Hello,World,Qt, s2=,,",
    // 13. memset
    "s1=Buffer, c=A, n=5",
    // 14. strerror
    "n=2",
    // 15. strlen
    "s1=Hello"
};

#endif // CONSTANTS_H
