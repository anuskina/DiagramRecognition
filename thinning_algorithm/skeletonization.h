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
    void getSkeleton();
private:
    void paintEvent(QPaintEvent *);
    void    iteration(Pixel *pixel, int firstNeighbor, int secondNeighbor);
    void secondSubiteration(Pixel *pixel);
    void createListOfEigntConnectrdNeighbor(Pixel *pixel);
    void deleteMarkedPixel();
    int numberOfBlackNeighbor();
    int connectivityNumber();
    QRgb colorOfPixel(Pixel *pixel);
    QList<Pixel *>  eightConnectedNeighbor;
    QList<Pixel *>  listOfMarkedPixel;
    QImage  image;
    QRgb colorOfBackGround;
    QRgb colorOfObject;
    Ui::skeletonization *ui;
};

#endif // SKELETONIZATION_H
