#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Icons
    // QIcon icon(":/icons/sprites/clock_black.ico");
    // a.setWindowIcon(QIcon(icon));

    // QSS bs
    QFile styleSheetFile("/home/user/Documents/453502/ОАиП2/QSS/Combinear.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
