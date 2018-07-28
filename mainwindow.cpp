#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(400, 400);

    QWidget *base = new QWidget();
    this->setCentralWidget(base);

    body = new QVBoxLayout(base);
    view = new QGraphicsView();
    scene = new QGraphicsScene();


    view->setBackgroundBrush(Qt::green);
    view->setScene(scene);
    body->addWidget(view);



    //createMine(20);
    createSteps();
    scene->setSceneRect(0, 0, 200, 200);

     scene->addRect(0, 0, 200, 200, QPen(Qt::green));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createMine(int amount)
{

    QRandomGenerator *gen = new QRandomGenerator();

    int row = 0, col = 0;

    for(int i = 0; i < 100; i++)
    {

        if (row > 9)
        {
            row = 0;
            col++;
        }

        Mine *np = new Mine();
        np->setPos(col * 20, row * 20);
        row ++;

        if (gen->generate() & 1)
        {
            continue;
        }

        scene->addItem(np);
    }

}
void MainWindow::createSteps()
{
    int row = 0, col = 0;

    for(int i = 0;i < 100; i++)
    {
        if (row > 9)
        {
            row = 0;
            col++;
        }

        Step *one_st = new Step();

        one_st->setPos(col * 20,row * 20);

        row ++;

        scene->addItem(one_st);
        steps.push_back(one_st);
        connect(one_st,SIGNAL(signalStep()),this,SLOT(Make_a_step()));
    }
}
void MainWindow ::Make_a_step()
{
//здесь будем удалять нажатые квадратики и в соответствии с картой минных полей реагировать
}
