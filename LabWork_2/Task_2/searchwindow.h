#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include "ordermanager.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(OrderManager *manager, QWidget *parent = nullptr);
    ~SearchWindow();


private:
    Ui::SearchWindow *ui;
    OrderManager *orderManager;
};

#endif // SEARCHWINDOW_H
