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


    view->setBackgroundBrush(Qt::white);
    view->setScene(scene);
    body->addWidget(view);

    createSteps();
    scene->setSceneRect(0, 0, 200, 200);

     scene->addRect(0, 0, 200, 200, QPen(Qt::green));
}
MainWindow::~MainWindow()
{
    delete ui;
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
one_st->setOpacity(1);
        scene->addItem(one_st);
        steps.push_back(one_st);
        //connect(one_st,SIGNAL(signalStep()),this,SLOT(Make_a_step()));

        connect(one_st,&Step::signalStep,this,&MainWindow ::Make_a_step);

    }
}
void MainWindow ::Make_a_step(QGraphicsItem *one_step)
{
//здесь будем удалять нажатые квадратики и в соответствии с картой минных полей реагировать
    foreach (QGraphicsItem *point, steps) {
        if(point == one_step)
        {
            if(first_step != true)
            {
                //произведем рандомную очистку поля
                QRandomGenerator *gen = new QRandomGenerator();
                QGraphicsTextItem *numb;

                scene->removeItem(one_step);

                for(int i = 0;i < steps.size();i++)
                {
                    if (gen->generate() & 1)
                    {
                        if(gen->generate() & 1)
                        {
                             mines.push_back(steps[i]);
                             if( i == 0)
                             {
                                 numbers[i+1] +=1;
                                 numbers[i+10] +=1;
                                 numbers[i+11] +=1;
                             }
                             else if(i == 9)
                             {
                                 numbers[i-1] +=1;
                                 numbers[i+9] +=1;
                                 numbers[i+10] +=1;
                             }
                             else if(i == 90)
                             {
                                 numbers[i-9] +=1;
                                 numbers[i-10] +=1;
                                 numbers[i+1] +=1;
                             }
                             else if(i == 99)
                             {
                                 numbers[i-10] +=1;
                                 numbers[i-11] +=1;
                                 numbers[i-1] +=1;
                             }
                             else if(i == 19 ||
                                     i == 29 ||
                                     i == 39 ||
                                     i == 49 ||
                                     i == 59 ||
                                     i == 69 ||
                                     i == 79 ||
                                     i == 89)
                             {
                                 numbers[i-1] +=1;
                                 numbers[i-10] +=1;
                                 numbers[i-11] +=1;
                                 numbers[i+9] +=1;
                                 numbers[i+10] +=1;
                             }
                             else if(i == 10 ||
                                     i == 20 ||
                                     i == 30 ||
                                     i == 40 ||
                                     i == 50 ||
                                     i == 60 ||
                                     i == 70 ||
                                     i == 80)
                             {
                                 numbers[i-9] +=1;
                                 numbers[i-10] +=1;
                                 numbers[i+1] +=1;
                                 numbers[i+10] +=1;
                                 numbers[i+11] +=1;
                             }
                             else
                             {
                                 if(i < 9)
                                 {
                                     numbers[i-1] +=1;
                                     numbers[i+1] +=1;
                                     numbers[i+9] +=1;
                                     numbers[i+10] +=1;
                                     numbers[i+11] +=1;
                                 }
                                 else if ( i > 90)
                                 {
                                     numbers[i-11] +=1;
                                     numbers[i-10] +=1;
                                     numbers[i-9] +=1;
                                     numbers[i-1] +=1;
                                     numbers[i+1] +=1;
                                 }
                                 else
                                 {
                                     numbers[i-11] +=1;
                                     numbers[i-10] +=1;
                                     numbers[i-9] +=1;
                                     numbers[i-1] +=1;
                                     numbers[i+1] +=1;
                                     numbers[i+9] +=1;
                                     numbers[i+10] +=1;
                                     numbers[i+11] +=1;
                                 }

                             }
                             numbers[i] = 55;
                        }
                        else
                        {
                            squars[i] = true;
                        }

                        continue;
                    }
//                    numb = scene->addText("1");
//                    numb->setPos(steps[i]->scenePos());
                    scene->removeItem(steps[i]);
                    qDebug() << steps[i];
                    //steps.removeOne(steps[i]);
                }
                for(int i = 0; i < 100; i++)
                {
                    if(numbers[i] > 0 && numbers[i] < 54)
                    {
                        QString string_num = QString::number(numbers[i]);

                        numb = scene->addText(string_num);
                        numb->setPos(steps[i]->scenePos());
                       // if(squars[i] == true)
                       // {
                       //    numb->hide();
                       // }

                    }
                    else if(numbers[i] == 0)
                    {
                        scene->removeItem(steps[i]);
                    }
                }
                first_step = true;
            }
            else
            {
               foreach(QGraphicsItem *numb,mines)
               {
                   if(numb == one_step)
                   {
                       QGraphicsTextItem *numb;

                       numb = scene->addText("M");
                       numb->setPos(one_step->scenePos());

                   }
               }

                scene->removeItem(one_step);

                //steps.removeOne(one_step);
            }

        }
    }

}
