#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtWidgets>
#include <fild.h>
#include <mine.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *body;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QPushButton *start;


    QVector<QGraphicsItem *> steps;

    void createMine(int amount);
    void createSteps();
private slots:

    void Make_a_step(QGraphicsItem *one_step);
};

#endif // MAINWINDOW_H
