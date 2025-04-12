#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPicture>
#include <QGraphicsView>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, width_scene, heigth_scene);

    scene->addItem(&rock);
    rock.setPos(450, 500);

    QTimer *time = new QTimer();
    connect(time, &QTimer::timeout, this, &MainWindow::moveObj);
    time->start(6);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::turn_onObj);
    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::restartObj);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveObj()
{
    if(rock.y() < -300){
        restartObj();
    }
    rock.move();
}

void MainWindow::turn_onObj()
{
    rock.turn_on();
    rock.startFlame();
}

void MainWindow::restartObj()
{
    rock.restart();
    rock.stopFlame();
}
