#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(400, 400);
    view = new QGraphicsView();
    scene = new QGraphicsScene();
     view->setScene(scene);
     scene->setSceneRect(0, 0, 200, 200);

     scene->addRect(0, 0, 200, 200, QPen(Qt::white));
    // scene->addItem(pacman);
}
MainWindow::~MainWindow()
{
    delete ui;
}
