#include <QCoreApplication>
#include <QDebug>
#include "mystring.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyString s1("Hello");
    const char* src1 = "Buffer";
    MyString::memcpy(s1.begin(), src1, 3);
    qDebug() << "memcpy:" << s1.begin();

    MyString s2("Hello");
    MyString::memmove(s2.begin() + 2, s2.begin(), 3);
    qDebug() << "memmove (overlap):" << s2.begin();

    MyString s3(10, '\0');
    MyString::strcpy(s3.begin(), "World");
    qDebug() << "strcpy:" << s3.begin();

    MyString s4("Hello");
    MyString::strncpy(s4.begin(), "World", 3);
    qDebug() << "strncpy:" << s4.begin();

    MyString s5("Hello");
    char temp[20];
    MyString::strcpy(temp, s5.begin());
    MyString::strcat(temp, "World");
    qDebug() << "strcat:" << temp;

    char temp2[20] = "Hello";
    MyString::strncat(temp2, "World", 3);
    qDebug() << "strncat:" << temp2;

    const char* m1 = "abc";
    const char* m2 = "abd";
    int memcmp_result = MyString::memcmp(m1, m2, 3);
    qDebug() << "memcmp (abc, abd, 3):" << memcmp_result;

    int strcmp_result = MyString::strcmp("ab0", "ab");
    qDebug() << "strcmp (ab0, ab):" << strcmp_result;

    int strncmp_result = MyString::strncmp("Hello", "Hel", 3);
    qDebug() << "strncmp (Hello, Hel, 3):" << strncmp_result;

    size_t strcspn_result = MyString::strcspn("Hello", "lo");
    qDebug() << "strcspn (Hello, lo):" << strcspn_result;

    MyString s6("Buffer");
    MyString::memset(s6.begin(), 'A', 5);
    qDebug() << "memset:" << s6.begin();

    size_t len = MyString::strlen("Hello");
    qDebug() << "strlen:" << len;

    return a.exec();
}
