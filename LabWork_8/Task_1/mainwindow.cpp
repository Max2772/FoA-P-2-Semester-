#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "bst.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BinarySearchTree<QString> tree;

    qDebug() << "=== Добавление узлов ===";
    tree.add("Alice", 2);
    tree.add("Bob", 1);
    tree.add("Charlie", 4);
    tree.add("David", 5);
    qDebug() << "Добавлены узлы: Bob(1), Alice(2), Charlie(4), David(5)";

    qDebug() << "\n=== Обходы дерева ===";
    qDebug() << "\nInorder (отсортировано по ключам):";
    std::vector<QString> inorder = tree.inorderTraversal();
    for (const QString& s : inorder) {
        qDebug() << s;
    }

    qDebug() << "\nPreorder:";
    std::vector<QString> preorder = tree.preorderTraversal();
    for (const QString& s : preorder) {
        qDebug() << s;
    }

    qDebug() << "\nPostorder:";
    std::vector<QString> postorder = tree.postorderTraversal();
    for (const QString& s : postorder) {
        qDebug() << s;
    }

    qDebug() << "\n=== Поиск узлов ===";
    try {
        qDebug() << "Поиск ключа 2:" << tree.search(2);
        qDebug() << "Поиск ключа 4:" << tree.search(4);
        qDebug() << "Поиск ключа 10:" << tree.search(10);
    } catch (const std::runtime_error& e) {
        qDebug() << "Ошибка:" << e.what();
    }

    qDebug() << "\n=== Удаление узла ===";
    qDebug() << "Удаляем узел с ключом 4 (значение Charlie)";
    tree.remove(4);
    qDebug() << "Inorder после удаления:";
    inorder = tree.inorderTraversal();
    for (const QString& s : inorder) {
        qDebug() << s;
    }

    qDebug() << "\n=== Вставка поддерева ===";
    BinarySearchTree<QString> subtree;
    subtree.add("Eve", 3);
    subtree.add("Frank", 6);
    qDebug() << "Добавляем поддерево с узлами: Eve(3), Frank(6)";
    tree.insertSubtree(subtree);
    qDebug() << "Inorder после вставки поддерева:";
    inorder = tree.inorderTraversal();
    for (const QString& s : inorder) {
        qDebug() << s;
    }

    qDebug() << "\n=== Удаление поддерева ===";
    qDebug() << "Удаляем поддерево с ключом 5 (значение David)";
    tree.removeSubtree(5);
    qDebug() << "Inorder после удаления поддерева:";
    inorder = tree.inorderTraversal();
    for (const QString& s : inorder) {
        qDebug() << s;
    }

    qDebug() << "\n=== Вставка ветви ===";
    try {
        qDebug() << "Добавляем узел Grace(4) как правое дитя узла с ключом 2 (Alice)";
        tree.insertBranch("Grace", 4, 2, false);
        qDebug() << "Inorder после вставки ветви:";
        inorder = tree.inorderTraversal();
        for (const QString& s : inorder) {
            qDebug() << s;
        }
    } catch (const std::runtime_error& e) {
        qDebug() << "Ошибка:" << e.what();
    }

    qDebug() << "\n=== Удаление ветви ===";
    try {
        qDebug() << "Удаляем правое поддерево узла с ключом 2 (Alice)";
        tree.removeBranch(2, false);
        qDebug() << "Inorder после удаления ветви:";
        inorder = tree.inorderTraversal();
        for (const QString& s : inorder) {
            qDebug() << s;
        }
    } catch (const std::runtime_error& e) {
        qDebug() << "Ошибка:" << e.what();
    }

    qDebug() << "\n=== Вставка элемента в определенную позицию ===";
    try {
        qDebug() << "Добавляем узел Hannah(3) как левое дитя узла с ключом 2 (Alice)";
        tree.insertBranch("Hannah", 3, 2, true);
        qDebug() << "Inorder после вставки элемента:";
        inorder = tree.inorderTraversal();
        for (const QString& s : inorder) {
            qDebug() << s;
        }
    } catch (const std::runtime_error& e) {
        qDebug() << "Ошибка:" << e.what();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
