#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QPainter>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    image.load("5.png");
    Pixel *startPoint = new Pixel(49, 138);
    Pixel *directionPoint = new Pixel(49, 128);
    Vectorizer *vectorizer = new Vectorizer(image, startPoint, directionPoint, qRgb(0, 0, 0), qRgb(255, 255, 255));
    listOfOutPutPoins = vectorizer ->getListOfOutPutPoints();
    foreach(QList<Pixel *> object, listOfOutPutPoins ){
        for(int i = 0; i < object.size(); i ++){
            image.setPixel(object[i] -> xCoordinate, object[i] -> yCoordinate, qRgb(255, 0, 255));
        }
    }
//    QList<Pixel *> listOfPixel = vectorizer->getListOfPixel();
//    foreach(Pixel *object, listOfPixel){

//            image.setPixel(object -> xCoordinate, object -> yCoordinate, qRgb(100, 0, 255));

//    }

//    QList<Pixel *> listOfOpPixel = vectorizer->getListOfOpPoints();
//    foreach(Pixel *object, listOfOpPixel){

//            image.setPixel(object -> xCoordinate, object -> yCoordinate, qRgb(100, 0, 100));

//    }

//    QList<Pixel *> listOfPlPr = vectorizer->getListOfPlPr();
//    foreach(Pixel *object, listOfPlPr){

//            image.setPixel(object -> xCoordinate, object -> yCoordinate, qRgb(0, 100, 100));

//    }
    painter.drawImage(0, 0, image.scaled(this->size()));
    vectorizer -> ~Vectorizer();
    return;
}

