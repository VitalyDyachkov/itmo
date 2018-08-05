#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtWidgets>
#include <fild.h>
#include <mine.h>
#include<QMediaPlayer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//public:slots
  //  void GameOverWindow();
private:
    Ui::MainWindow *ui;
    QVBoxLayout *body;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPushButton *start;
    QMediaPlayer *sound_efect;
    bool first_step = false;

    QVector<QGraphicsItem*> steps;
    QVector<QGraphicsItem*>mines;
    int numbers[100] = {0};
    bool squars[100] = {false};
    bool flag_new_game = false;
    void CreateSteps();
    void CreateNewGame();
    void RemoveSteps(QGraphicsItem *one_step,QGraphicsScene *scene);
private slots:
    void Make_a_step(QGraphicsItem *one_step);
};

#endif // MAINWINDOW_H
