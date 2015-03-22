#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QMenu>
#include "boximage.h"
class BoxImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void InvalidItem();
    void quit();

private:
    QSplitter *splitter;
    BoxImage *box;
    void Init();
};

#endif // MAINWINDOW_H
