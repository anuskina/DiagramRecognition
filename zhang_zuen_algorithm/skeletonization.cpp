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
    image.load("im7.png");
    QPainter    painter(this);
    getSkeleton();
    painter.drawImage(0,0,image.scaled(this->size()));
}

void Skeletonization::getSkeleton()
{
    int windthOfimage = image.width();
    int heightOfImage = image.height();
    bool breakTemp = false;
    do
    {
        for(int i=1; i<windthOfimage; i++){
            for(int j=1; j<heightOfImage; j++){
                if(image.pixel(i,j) == qRgb(0, 0, 0)){
                    Pixel *myPixel = new Pixel(i, j);
                    createListOfEigntConnectrdNeighbor(myPixel);
                    firstSubIteration(myPixel);
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
        for(int i=1; i<windthOfimage; i++){
            for(int j=1; j<heightOfImage; j++){
                if(image.pixel(i,j)==qRgb(0, 0, 0)){
                    Pixel *myPixel = new Pixel(i, j);
                    createListOfEigntConnectrdNeighbor(myPixel);
                    secondSubiteration(myPixel);
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
    for(int i=0; i<listOfMarkedPixel.size();i++)
    {
        image.setPixel(listOfMarkedPixel.at(i)->xCoordinate,listOfMarkedPixel.at(i)->yCoordinate,qRgb(255, 255, 255));
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
    for(int count = 0; count < 8; count ++){
        if(image.pixel(eightConnectedNeighbor.at(count) -> xCoordinate,
           eightConnectedNeighbor.at(count) -> yCoordinate) == qRgb(0, 0, 0)){
            result++;
        }
    }
    return result;
}

int Skeletonization::connectivityNumber()
{
    int result = 0;
    for(int count = 0; count < 7; count ++){
        if(image.pixel(eightConnectedNeighbor.at(count) -> xCoordinate,
                       eightConnectedNeighbor.at(count) -> yCoordinate) == qRgb(255, 255, 255)
        && image.pixel(eightConnectedNeighbor.at(count+1) -> xCoordinate,
                       eightConnectedNeighbor.at(count+1) -> yCoordinate) == qRgb(0, 0, 0)){
            result++;
        }
    }
    if(image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                   eightConnectedNeighbor.at(7) -> yCoordinate) == qRgb(255, 255, 255)
    && image.pixel(eightConnectedNeighbor.at(0) -> xCoordinate,
                   eightConnectedNeighbor.at(0) -> yCoordinate) == qRgb(0, 0, 0)){
        result++;
    }
    return result;
}

void Skeletonization::firstSubIteration(Pixel *pixel)
{
    int blackNeighbor = numberOfBlackNeighbor();
    int connectivity = connectivityNumber();
    if(blackNeighbor >= 2 && blackNeighbor <= 6 && connectivity == 1){

        if(image.pixel(eightConnectedNeighbor.at(1) -> xCoordinate,
                       eightConnectedNeighbor.at(1) -> yCoordinate) == qRgb(255, 255, 255)
        || image.pixel(eightConnectedNeighbor.at(3) -> xCoordinate,
                       eightConnectedNeighbor.at(3)->yCoordinate) == qRgb(255, 255, 255)
        || image.pixel(eightConnectedNeighbor.at(5) -> xCoordinate,
                       eightConnectedNeighbor.at(5) -> yCoordinate) == qRgb(255, 255, 255)){
            if(image.pixel(eightConnectedNeighbor.at(3) -> xCoordinate,
                           eightConnectedNeighbor.at(3) -> yCoordinate) == qRgb(255, 255, 255)
            || image.pixel(eightConnectedNeighbor.at(5) -> xCoordinate,
                           eightConnectedNeighbor.at(5) -> yCoordinate) == qRgb(255, 255, 255)
            || image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                           eightConnectedNeighbor.at(7)->yCoordinate) == qRgb(255, 255, 255)){
                listOfMarkedPixel.append(pixel);
            }
        }
    }
}

void Skeletonization::secondSubiteration(Pixel *pixel)
{
    int blackNeighbor = numberOfBlackNeighbor();
    int connectivity = connectivityNumber();
    if(blackNeighbor >= 2 && blackNeighbor <= 6 && connectivity == 1){

        if(image.pixel(eightConnectedNeighbor.at(1) -> xCoordinate,
                       eightConnectedNeighbor.at(1) -> yCoordinate) == qRgb(255, 255, 255)
        || image.pixel(eightConnectedNeighbor.at(3) -> xCoordinate,
                       eightConnectedNeighbor.at(3)->yCoordinate) == qRgb(255, 255, 255)
        || image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                       eightConnectedNeighbor.at(7) -> yCoordinate) == qRgb(255, 255, 255)){
            if(image.pixel(eightConnectedNeighbor.at(1) -> xCoordinate,
                           eightConnectedNeighbor.at(1) -> yCoordinate) == qRgb(255, 255, 255)
            || image.pixel(eightConnectedNeighbor.at(5) -> xCoordinate,
                           eightConnectedNeighbor.at(5) -> yCoordinate) == qRgb(255, 255, 255)
            || image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                           eightConnectedNeighbor.at(7)->yCoordinate) == qRgb(255, 255, 255)){
                listOfMarkedPixel.append(pixel);
            }
        }
    }
}
