#ifndef SKELETONIZATION_H
#define SKELETONIZATION_H

#include <QtGui/QMainWindow>

namespace Ui {
class Skeletonization;
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
    QImage image;
    void    paintEvent(QPaintEvent *);
    void    firstSubIteration(Pixel *pixel);
    void    secondSubiteration(Pixel *pixel);
    void    createListOfEigntConnectrdNeighbor(Pixel *pixel);
    void    getSkeleton();
    void    deleteMarkedPixel();
    QList<Pixel *>  eightConnectedNeighbor;
    QList<Pixel *>  listOfMarkedPixel;
    int NumberOfDistinctEightConnectedNeighbor();
    int EndPointCheckReplacing();
    int DetectionOfEndPoinForFirstIteration();
    int DetectionOfEndPoinForSecondIteration();
    int FirstArgument();
    int SecondArgument();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Skeletonization *ui;
};

#endif // SKELETONIZATION_H
