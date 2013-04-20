# include <circlefollower.h>

Circlefollower::Circlefollower(QImage image, QList<Circle *> circles
                             , QRgb colorOfObject, QRgb colorOfBackGraund)
    : image(image), circles(circles)
    , colorOfObject(colorOfObject), colorOfBackGraund(colorOfBackGraund)
{
}

Circlefollower::~Circlefollower(){
    circles.clear();
    listOfPairOfOppositePoint.clear();
}

Pixel *Circlefollower::getPixelLeft()
{
    return pixelLeft;
}

Pixel *Circlefollower::getPixelRight()
{
    return pixelRight;
}

QList<BracheCandidate *> Circlefollower::circleFollowing()
{
    Pixel *firstPoint;
    Pixel *oppositePoint;
    int count;
    int numberOfEnters;
    int circleNumber = 0;
    int sizeOfListOfCirclePoint;
    foreach(Circle const *circle, circles){
        numberOfEnters = 0;
        count = 0;
        sizeOfListOfCirclePoint = circle -> circlePoints.size();
        while(count < sizeOfListOfCirclePoint
           && image.pixel(circle -> circlePoints.at(count)->xCoordinate
                        , circle -> circlePoints.at(count)->yCoordinate) == colorOfObject){
            count ++;
        }
        if (circleNumber == circles.size() - 2){
            pixelLeft = circle -> circlePoints.at(count - 1);
        }
        while(count < sizeOfListOfCirclePoint)
        {
            if(image.pixel(circle -> circlePoints.at(count) -> xCoordinate
                         , circle -> circlePoints.at(count)-> yCoordinate) == colorOfObject){
                if(numberOfEnters % 2 == 0){
                    firstPoint = circle -> circlePoints.at(count);
                    numberOfEnters ++;
                }
            }
            else{
                if(numberOfEnters % 2 != 0){
                    oppositePoint = circle -> circlePoints.at(count - 1);
                    listOfPairOfOppositePoint.append
                            (new BracheCandidate(firstPoint, oppositePoint
                                               , circleNumber, 0, 0));
                    numberOfEnters ++;
                }
            }
            count ++;
        }
        if (circleNumber == circles.size() - 2){
            pixelRight = firstPoint;
        }
        circleNumber++;
    }
    return listOfPairOfOppositePoint;
}
