#ifndef SKELETONIZATION_H
#define SKELETONIZATION_H

#include <QtGui/QMainWindow>

namespace Ui {
class skeletonization;
}
struct Pixel
{
    Pixel(int xCoordinate, int yCoordinate) : xCoordinate(xCoordinate), yCoordinate(yCoordinate){}
    int xCoordinate;
    int yCoordinate;
};
class Skeletonization : public QMainWindow
{
    Q_OBJECT

public:
    explicit Skeletonization(QWidget *parent = 0);
    ~Skeletonization();
    QImage  image;
    void    paintEvent(QPaintEvent *);
    void    firstSubIteration(Pixel *pixel);
    void    secondSubiteration(Pixel *pixel);
    void    createListOfEigntConnectrdNeighbor(Pixel *pixel);
    void    getSkeleton();
    void    deleteMarkedPixel();
    QList<Pixel *>  eightConnectedNeighbor;
    QList<Pixel *>  listOfMarkedPixel;
    int numberOfBlackNeighbor();
    int connectivityNumber();
private:
    Ui::skeletonization *ui;
};

#endif // SKELETONIZATION_H
