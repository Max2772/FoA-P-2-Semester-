#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTreeWidgetItem>
#include "avltree.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static const int MINIMUM_RANDOM_SIZE = 1;
    static const int MAXIMUM_RANDOM_SIZE = 30;
    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 30;

private:
    void CreateRandomAVLTree();
    void PrintTree(AVLTree* tree);
    void Update();
    QTreeWidgetItem *UpdateTree(AVLTree *tree);

private slots:
    void on_pushButtonInsert_clicked();
    void on_pushButtonDoTask_clicked();
    void on_pushButtonContains_clicked();
    void on_pushButtonRemove_clicked();

private:
    AVLTree* tree;
    AVLTree* root;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
