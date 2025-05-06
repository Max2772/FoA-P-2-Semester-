#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "string.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::WriteResults()
{
    for (int i = 0; i < 15; ++i) {
        QString s1 = "", s2 = "", n_str = "", c_str = "";
        size_t n = 0;
        QChar c = '\0';

        QStringList params = functionExample[i].split(", ");
        for (const QString& param : params) {
            if (param.startsWith("s1=")) {
                s1 = param.mid(3);
            } else if (param.startsWith("s2=")) {
                s2 = param.mid(3);
            } else if (param.startsWith("n=")) {
                n_str = param.mid(2);
                n = n_str.toULongLong();
            } else if (param.startsWith("c=")) {
                c_str = param.mid(2);
                c = c_str.isEmpty() ? QChar('\0') : c_str[0];
            }
        }

        std::string s1_std = s1.toStdString();
        std::string s2_std = s2.toStdString();
        switch (i) {
        case 0: // memcpy
        {
            std::string dest = s2_std;
            dest.resize(std::max(dest.size(), n));
            memcpy(dest.data(), s1_std.data(), std::min(n, s1_std.size()));
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 1: // memmove
        {
            std::string dest = s2_std;
            dest.resize(std::max(dest.size(), n));
            memmove(dest.data(), s1_std.data(), std::min(n, s1_std.size()));
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 2: // strcpy
        {
            std::string dest(s1_std.size() + s2_std.size() + 1, '\0');
            strcpy(dest.data(), s2_std.c_str());
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 3: // strncpy
        {
            std::string dest = s1_std;
            dest.resize(std::max(dest.size(), n));
            strncpy(dest.data(), s2_std.c_str(), n);
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 4: // strcat
        {
            std::string dest = s1_std;
            dest.resize(dest.size() + s2_std.size() + 1);
            strcat(dest.data(), s2_std.c_str());
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 5: // strncat
        {
            std::string dest = s1_std;
            dest.resize(dest.size() + n + 1);
            strncat(dest.data(), s2_std.c_str(), n);
            results[i] = QString::fromStdString(dest);
            break;
        }
        case 6: // memcmp
        {
            int result = memcmp(s1_std.data(), s2_std.data(), std::min(n, std::min(s1_std.size(), s2_std.size())));
            results[i] = QString::number(result);
            break;
        }
        case 7: // strcmp
        {
            int result = strcmp(s1_std.c_str(), s2_std.c_str());
            results[i] = QString::number(result);
            break;
        }
        case 8: // strcoll
        {
            setlocale(LC_ALL, "ru_RU.UTF-8");
            int result = strcoll(s1_std.c_str(), s2_std.c_str());
            results[i] = QString::number(result);
            break;
        }
        case 9: // strncmp
        {
            int result = strncmp(s1_std.c_str(), s2_std.c_str(), n);
            results[i] = QString::number(result);
            break;
        }
        case 10: // strxfrm
        {
            setlocale(LC_ALL, "ru_RU.UTF-8");
            std::string dest(n + 1, '\0');
            size_t len = strxfrm(dest.data(), s2_std.c_str(), n);
            results[i] = QString::fromStdString(dest) + ", Length: " + QString::number(len);
            break;
        }
        case 11: // strtok
        {
            std::string str = s1_std;
            std::vector<std::string> tokens;
            char* token = strtok(str.data(), s2_std.c_str());
            while (token) {
                tokens.push_back(token);
                token = strtok(nullptr, s2_std.c_str());
            }
            std::string result;
            for (size_t j = 0; j < tokens.size(); ++j) {
                result += tokens[j];
                if (j < tokens.size() - 1) result += ", ";
            }
            results[i] = QString::fromStdString(result);
            break;
        }
        case 12: // memset
        {
            std::string buffer = s1_std;
            buffer.resize(std::max(buffer.size(), n));
            memset(buffer.data(), c.toLatin1(), n);
            results[i] = QString::fromStdString(buffer);
            break;
        }
        case 13: // strerror
        {
            results[i] = QString::fromStdString(strerror(errnum));
            break;
        }
        case 14: // strlen
        {
            results[i] = QString::number(strlen(s1_std.c_str()));
            break;
        }
        }
    }
}
