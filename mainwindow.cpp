#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QPushButton>
#include <QString>
#include <QMediaPlayer>
#include <cstdlib>
#include <QTime>

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
    sound_efect = new QMediaPlayer();
    sound_efect->setMedia(QUrl("qrc:/sounds/boom_2.mp3"));

    view->setBackgroundBrush(Qt::white);
    view->setScene(scene);
    body->addWidget(view);

    CreateSteps();
    scene->setSceneRect(0, 0, 200, 200);

    scene->addRect(0, 0, 200, 200, QPen(Qt::green));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: CreateNewGame()
{

    for(int i = 0;i < steps.size();i++)
    {
        delete steps[i];
    }
    steps.erase(steps.begin(),steps.end());
    mines.erase(mines.begin(),mines.end());
    for(int i = 0;i < 100;i++)
    {
        squars[i] = false;
        numbers[i] = 0;
    }
    first_step = false;
    scene->clear();
    CreateSteps();

}
void MainWindow::CreateSteps()
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


                QGraphicsTextItem *numb;

                QTime time = QTime::currentTime();
                int sec = time.second();
                int msec = time.msec();
                QRandomGenerator *gen = new QRandomGenerator((quint32)msec);
                 QRandomGenerator *mines_gen = new QRandomGenerator((quint32)sec);
             //   gen->generate((quint32)sec,(quint32)msec);

                scene->removeItem(one_step);

                for(int i = 0;i < steps.size();i++)
                {
                    if (gen->generate() % 2)
                    {
                        if(mines_gen->generate() & 1)
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

                    scene->removeItem(steps[i]);
                    qDebug() << steps[i];

                }
                for(int i = 0; i < 100; i++)
                {
                    /*произведем вывод чисел в квадратики в соответствии с картой минного поля*/
                    if(numbers[i] > 0 && numbers[i] < 54)
                    {
                        QString string_num = QString::number(numbers[i]);

                        if(squars[i] == true)
                        {
                            dynamic_cast<Step *>(steps[i])->numb = string_num;
                        }
                        else
                        {
                            numb = scene->addText(string_num);
                            numb->setPos(steps[i]->scenePos());
                        }

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
               foreach(QGraphicsItem *one_mine,mines)
               {
                   if(one_mine == one_step)
                   {
                       QGraphicsTextItem *numb;

                       for(int i = 0 ; i< mines.size();i++)
                       {
                           numb = scene->addText("M");
                           numb->setPos(mines[i]->scenePos());
                       }
                       sound_efect->play();

                       QMessageBox *dialog = new QMessageBox(QMessageBox::Information,
                                                                 "Dialog", "You lost!Create new game?",
                                                                 QMessageBox::Yes | QMessageBox::Cancel);

                           if (dialog->exec() == QMessageBox::Yes)
                           {
                            //произведем подготовку нового минного поля
                               CreateNewGame();
                               flag_new_game = true;
                           }

                           else
                           {
                               this->close();
                           }
                   }
               }
               if(!flag_new_game)
               {
                   QGraphicsTextItem *numer;
                   numer = scene->addText(dynamic_cast<Step*>(one_step)->numb);
                   numer->setPos(one_step->scenePos());
                   scene->removeItem(one_step);
               }
               else
               {
                    flag_new_game = false;
               }
               //steps.removeOne(one_step);

            }

        }
    }

}

