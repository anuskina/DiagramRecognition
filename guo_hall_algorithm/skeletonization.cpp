#include "skeletonization.h"
#include "ui_skeletonization.h"
#include "QPainter"

Skeletonization::Skeletonization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Skeletonization)
{
    ui->setupUi(this);
}

Skeletonization::~Skeletonization()
{
    delete ui;
}

void Skeletonization::paintEvent(QPaintEvent *)
{
    image.load("im4.png");
    QPainter painter(this);
    getSkeleton();
    painter.drawImage(0, 0, image.scaled(this->size()));
}

void Skeletonization::getSkeleton()
{
    int widthOfImage = image.width();
    int heightOfImage = image.height();
    bool breakTemp = false;
    do
    {
        for(int i = 1; i < widthOfImage; i++){
            for(int j = 1; j < heightOfImage; j++){
                if(image.pixel(i, j) == qRgb(0, 0, 0)){
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
        for(int i = 1;i < widthOfImage; i++){
            for(int j = 1; j < heightOfImage; j++){
                if(image.pixel(i, j) == qRgb(0, 0, 0)){
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
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate + 1));
}

int Skeletonization::NumberOfDistinctEightConnectedNeighbor()
{
    int result = 0;
    for (int count = 0; count < 3; count ++){
        if(image.pixel(eightConnectedNeighbor.at(2 * count) -> xCoordinate,
                       eightConnectedNeighbor.at(2 * count) -> yCoordinate) == qRgb(255, 255, 255)
        && (image.pixel(eightConnectedNeighbor.at(2 * count + 1) -> xCoordinate,
                        eightConnectedNeighbor.at(2 * count + 1) -> yCoordinate) == qRgb(0, 0, 0)
           ||image.pixel(eightConnectedNeighbor.at(2 * count + 2) -> xCoordinate,
                         eightConnectedNeighbor.at(2 * count + 2) -> yCoordinate) == qRgb(0, 0, 0))){
            result += 1;
        }
    }
    if(image.pixel(eightConnectedNeighbor.at(6) -> xCoordinate,
                   eightConnectedNeighbor.at(6) -> yCoordinate) == qRgb(255, 255, 255)
    && (image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                    eightConnectedNeighbor.at(7) -> yCoordinate) == qRgb(0, 0, 0)
       ||image.pixel(eightConnectedNeighbor.at(0) -> xCoordinate,
                     eightConnectedNeighbor.at(0) -> yCoordinate) == qRgb(0, 0, 0))){
        result += 1;
    }
    return result;
}

int Skeletonization::EndPointCheckReplacing()
{
    return std :: min(FirstArgument(), SecondArgument());
}

int Skeletonization::FirstArgument()
{
    int result = 0;
    int firstColor = 0;
    int secondColor = 0;
    for(int count = 0; count < 4; count++){
        firstColor = (image.pixel(eightConnectedNeighbor.at(2 * count) -> xCoordinate,
                                  eightConnectedNeighbor.at(2 * count) -> yCoordinate) == qRgb(0, 0, 0)) ? 1 : 0;
        secondColor = (image.pixel(eightConnectedNeighbor.at(2 * count + 1) -> xCoordinate,
                                   eightConnectedNeighbor.at(2 * count + 1) -> yCoordinate) == qRgb(0, 0, 0)) ? 1 : 0;
        if(firstColor == 1 && secondColor == 1){
            result += 1;
        }
        else{
            result += firstColor + secondColor;
        }
    }
    return result;
}

int Skeletonization::SecondArgument()
{
    int result = 0;
    int firstColor = 0;
    int secondColor = 0;
    for(int count = 0; count < 3; count++){
        firstColor = image.pixel(eightConnectedNeighbor.at(2 * count + 1) -> xCoordinate,
                                 eightConnectedNeighbor.at(2 * count + 1) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
        secondColor = image.pixel(eightConnectedNeighbor.at(2 * count + 2) -> xCoordinate,
                                  eightConnectedNeighbor.at(2 * count + 2) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
        if(firstColor == 1 && secondColor == 1){
            result += 1;
        }
        else{
            result += firstColor+secondColor;
        }
    }
    firstColor = image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                             eightConnectedNeighbor.at(7) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    secondColor = image.pixel(eightConnectedNeighbor.at(0) -> xCoordinate,
                              eightConnectedNeighbor.at(0) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    if(firstColor == 1 && secondColor == 1){
        result += 1;
    }
    else{
        result += firstColor + secondColor;
    }
    return result;
}

int Skeletonization::DetectionOfEndPoinForFirstIteration()
{
    int firstColor = image.pixel(eightConnectedNeighbor.at(0) -> xCoordinate,
                                 eightConnectedNeighbor.at(0) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int secondColor = image.pixel(eightConnectedNeighbor.at(1) -> xCoordinate,
                                  eightConnectedNeighbor.at(1) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int thirdColor = image.pixel(eightConnectedNeighbor.at(2) -> xCoordinate,
                                 eightConnectedNeighbor.at(2) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int fourthColor = image.pixel(eightConnectedNeighbor.at(7) -> xCoordinate,
                                  eightConnectedNeighbor.at(7) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    if(fourthColor == 0){
        fourthColor = 1;
    }
    else{
        fourthColor = 0;
    }
    if(firstColor == 0){
        return 0;
    }
    else{
        if(secondColor == 0 && thirdColor == 0 && fourthColor == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int Skeletonization::DetectionOfEndPoinForSecondIteration()
{
    int firstColor = image.pixel(eightConnectedNeighbor.at(4) -> xCoordinate,
                                 eightConnectedNeighbor.at(4) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int secondColor = image.pixel(eightConnectedNeighbor.at(5) -> xCoordinate,
                                  eightConnectedNeighbor.at(5) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int thirdColor = image.pixel(eightConnectedNeighbor.at(6) -> xCoordinate,
                                 eightConnectedNeighbor.at(6) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    int fourthColor = image.pixel(eightConnectedNeighbor.at(3) -> xCoordinate,
                                  eightConnectedNeighbor.at(3) -> yCoordinate) == qRgb(0, 0, 0) ? 1 : 0;
    if(fourthColor == 0){
        fourthColor = 1;
    }
    else{
        fourthColor = 0;
    }
    if(firstColor == 0){
        return 0;
    }
    else{
        if(secondColor == 0 && thirdColor == 0 && fourthColor == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

void Skeletonization::firstSubIteration(Pixel *pixel)
{
    if(NumberOfDistinctEightConnectedNeighbor() == 1){
        int endPointCheckReplacing = EndPointCheckReplacing();
        if(endPointCheckReplacing >=2 && endPointCheckReplacing <= 3){
            if(DetectionOfEndPoinForFirstIteration() == 0){
                listOfMarkedPixel.append(pixel);
            }
        }
    }
}
void Skeletonization::secondSubiteration(Pixel *pixel)
{
    if(NumberOfDistinctEightConnectedNeighbor() == 1){
        int endPointCheckReplacing = EndPointCheckReplacing();

        if(endPointCheckReplacing >= 2 && endPointCheckReplacing <= 3){
            if(DetectionOfEndPoinForSecondIteration() == 0){
                listOfMarkedPixel.append(pixel);
            }
        }
    }
}

