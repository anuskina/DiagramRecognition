#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vectorizer.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT   
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
private:
    QImage  image;
    Ui::MainWindow *ui;
    QList<QList<Pixel *> > listOfOutPutPoins;
};

#endif // MAINWINDOW_H
