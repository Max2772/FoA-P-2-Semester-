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


private slots:
    void UpdateSearch();

private:
    Ui::SearchWindow *ui;
    OrderManager *orderManager;
    QString currentName;
    QDate currentReceiptDate;
    QDate currentCompletionDate;
    QString currentStatus;
};

#endif // SEARCHWINDOW_H
