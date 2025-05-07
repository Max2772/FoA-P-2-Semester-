#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include "mystring.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyString s1("Hello");
    const char* src1 = "Buffer";
    MyString::memcpy(s1.begin(), src1, 3);
    qDebug() << "memcpy: " << s1.begin();

    MyString s2("Hello");
    const char* src2 = "Buffer";
    MyString::memcpy(s2.begin(), src2, 3);
    qDebug() << "memmove: " << s2.begin();

    MyString s3(10, '\0');
    MyString::strcpy(s3.begin(), "World");
    qDebug() << "strcpy: " << s3.begin();

    MyString s4("Hello");
    MyString::strncpy(s4.begin(), "World", 3);
    qDebug() << "strncpy: " << s4.begin();

    MyString s5("Hello");
    char temp[20];
    MyString::strcpy(temp, s5.begin());
    MyString::strcat(temp, "World");
    qDebug() << "strcat: " << temp;

    qDebug() << "strncat: Not implemented";

    const char* m1 = "abc";
    const char* m2 = "abd";
    int memcmp_result = MyString::memcmp(m1, m2, 3);
    qDebug() << "memcmp: " << memcmp_result;

    int strcmp_result = MyString::strcmp("abc", "abc");
    qDebug() << "strcmp: " << strcmp_result;

    int strcoll_result = MyString::strcmp("абв", "где");
    qDebug() << "strcoll: " << strcoll_result;

    int strncmp_result = MyString::strncmp("Hello", "Hel", 3);
    qDebug() << "strncmp: " << strncmp_result;

    qDebug() << "strxfrm: Not implemented";

    MyString s13("Buffer");
    MyString::memset(s13.begin(), 'A', 5);
    qDebug() << "memset: " << s13.begin();

    qDebug() << "strerror: Not implemented";

    size_t len = MyString::strlen("Hello");
    qDebug() << "strlen: " << len;

    qDebug() << "strcspn: Not implemented";

}

MainWindow::~MainWindow()
{
    delete ui;
}
