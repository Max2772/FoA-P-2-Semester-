#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSS bs(Combinear, Genetive, Geoo, Toolery)
    QFile styleSheetFile("/home/user/Documents/453502/ОАиП2/QSS/Geoo.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);


    MainWindow w;
    w.show();
    return a.exec();
}
