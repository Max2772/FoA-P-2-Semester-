#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include "ordermanager.h"
#include "utils.h"
#include "order.h"

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();


private:
    Ui::SearchWindow *ui;
    OrderManager orderManager;
};

#endif // SEARCHWINDOW_H
