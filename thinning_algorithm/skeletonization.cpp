#include "skeletonization.h"
#include "ui_skeletonization.h"
#include "QPainter"

Skeletonization::Skeletonization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::skeletonization)
{
    ui->setupUi(this);
}

Skeletonization::~Skeletonization()
{
    delete ui;
}

void Skeletonization::paintEvent(QPaintEvent *)
{
    image.load("5.png");
    QPainter    painter(this);
    colorOfBackGround = qRgb(255, 255, 255);
    colorOfObject = qRgb(0, 0, 0);
    getSkeleton();
    painter.drawImage(0, 0, image.scaled(this->size()));
}

void Skeletonization::getSkeleton()
{
    int windthOfimage = image.width();
    int heightOfImage = image.height();
    bool breakTemp = false;
    do
    {
        for(int i = 1; i < windthOfimage; i++){
            for(int j = 1; j < heightOfImage; j++){
                if(image.pixel(i, j) == colorOfObject){
                    Pixel *myPixel = new Pixel(i, j);
                    createListOfEigntConnectrdNeighbor(myPixel);
                    iteration(myPixel, 5, 3);
                    eightConnectedNeighbor.clear();
                }
            }
        }
        if(!listOfMarkedPixel.empty()){
            deleteMarkedPixel();
            breakTemp = true;
        }
        else{
            breakTemp = false;
        }
        for(int i = 1; i < windthOfimage; i++){
            for(int j = 1; j < heightOfImage; j++){
                if(image.pixel(i, j) == colorOfObject){
                    Pixel *myPixel = new Pixel(i, j);
                    createListOfEigntConnectrdNeighbor(myPixel);
                    iteration(myPixel, 7, 1);
                    eightConnectedNeighbor.clear();
                }
            }
        }
        if(!listOfMarkedPixel.empty()){
            deleteMarkedPixel();
            breakTemp = true;
        }
        else{
            breakTemp = false;
        }
    }while (breakTemp);
}

void Skeletonization::deleteMarkedPixel()
{
    foreach(Pixel *object, listOfMarkedPixel)
    {
        image.setPixel(object -> xCoordinate, object -> yCoordinate, colorOfBackGround);
    }
    listOfMarkedPixel.clear();
}

void Skeletonization::createListOfEigntConnectrdNeighbor(Pixel *pixel)
{
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate, pixel -> yCoordinate - 1));
}

int Skeletonization::numberOfBlackNeighbor()
{
    int result = 0;
    foreach(Pixel *object, eightConnectedNeighbor)
    {
        if(colorOfPixel(object) == colorOfObject){
            result++;
        }
    }
    return result;
}

QRgb Skeletonization::colorOfPixel(Pixel *pixel)
{
    return image.pixel(pixel -> xCoordinate, pixel -> yCoordinate);
}

int Skeletonization::connectivityNumber()
{
    int result = 0;
    for(int count = 0; count < 7; count ++){
        if(colorOfPixel(eightConnectedNeighbor.at(count)) == colorOfBackGround
        && colorOfPixel(eightConnectedNeighbor.at(count + 1)) == colorOfObject){
            result++;
        }
    }
    if(colorOfPixel(eightConnectedNeighbor.at(7)) == colorOfBackGround
    && colorOfPixel(eightConnectedNeighbor.at(0)) == colorOfObject){
        result++;
    }
    return result;
}

void Skeletonization::iteration(Pixel *pixel, int firstNeighbor, int secondNeighbor)
{
    int blackNeighbor = numberOfBlackNeighbor();
    int connectivity = connectivityNumber();
    if(blackNeighbor >= 2 && blackNeighbor <= 6 && connectivity == 1){
        if(colorOfPixel(eightConnectedNeighbor.at(1)) == colorOfBackGround
        || colorOfPixel(eightConnectedNeighbor.at(3)) == colorOfBackGround
        || colorOfPixel(eightConnectedNeighbor.at(firstNeighbor)) == colorOfBackGround){
            if(colorOfPixel(eightConnectedNeighbor.at(secondNeighbor)) == colorOfBackGround
            || colorOfPixel(eightConnectedNeighbor.at(5)) == colorOfBackGround
            || colorOfPixel(eightConnectedNeighbor.at(7)) == colorOfBackGround){
                listOfMarkedPixel.append(pixel);
            }
        }
    }
}

