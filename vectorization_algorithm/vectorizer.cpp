#include "contourfollower.h"
#include "circlefollower.h"
#include "vectorizer.h"

#include "QList"
#include "QImage"
#include "math.h"

using namespace std;

Vectorizer::Vectorizer(QImage image, Pixel *startPoint, Pixel *directionPoint
                     , QRgb colorOfObject, QRgb colorOfBackGround)
    : image(image), startPoint(startPoint), directionPoint(directionPoint)
    , colorOfObject(colorOfObject), colorOfBackGround(colorOfBackGround)
{
}

Vectorizer::~Vectorizer()
{

}

//QList<Pixel *> Vectorizer::getListOfPixel()
//{
//    return listOfPixel;
//}

//QList<Pixel *> Vectorizer::getListOfOpPoints()
//{
//    return listOfOpPoints;
//}

//QList<Pixel *> Vectorizer::getListOfPlPr()
//{
//    return lisOfPlPr;
//}

bool Vectorizer::isEqualPixel(Pixel *firstPixel, Pixel *secondPixel)
{
    return (firstPixel -> xCoordinate == secondPixel ->xCoordinate
         && firstPixel -> yCoordinate == secondPixel -> yCoordinate);
}

bool Vectorizer::isLessMorePixel(Pixel *firstPixel, Pixel *secondPixel)
{
    return (firstPixel -> xCoordinate < secondPixel ->xCoordinate
         && firstPixel -> yCoordinate > secondPixel -> yCoordinate);
}

bool Vectorizer::isLessPixel(Pixel *firstPixel, Pixel *secondPixel)
{
    return (firstPixel -> xCoordinate < secondPixel ->xCoordinate
         && firstPixel -> yCoordinate < secondPixel -> yCoordinate);
}

bool Vectorizer::isMoreLessPixel(Pixel *firstPixel, Pixel *secondPixel)
{
    return (firstPixel -> xCoordinate > secondPixel ->xCoordinate
         && firstPixel -> yCoordinate < secondPixel -> yCoordinate);
}

bool Vectorizer::isMorePixel(Pixel *firstPixel, Pixel *secondPixel)
{
    return (firstPixel -> xCoordinate > secondPixel ->xCoordinate
         && firstPixel -> yCoordinate < secondPixel -> yCoordinate);
}

bool Vectorizer::isBranch(BracheCandidate *branch, int currentBranch)
{
    return(branch -> branchNumberOfTheFirstPoint > 0
        && branch -> branchNumberOfTheOppositePoint > 0
        && branch -> branchNumberOfTheFirstPoint
           <= branch -> branchNumberOfTheOppositePoint
        && ((branch->branchNumberOfTheFirstPoint == currentBranch)
        ||(branch->branchNumberOfTheOppositePoint == currentBranch)));
}

Pixel* Vectorizer::createMedianPoint(Pixel *firstPixel, Pixel *secondPixel)
{
    return new Pixel(firstPixel -> xCoordinate
                           - static_cast<int>((firstPixel -> xCoordinate
                                               - secondPixel -> xCoordinate) / 2),
                           firstPixel -> yCoordinate
                           - static_cast<int>((firstPixel -> yCoordinate
                                               - secondPixel -> yCoordinate) / 2));
}

bool Vectorizer::branchingCriterion(int numberOfMedianPoint)
{
    return (isEqualPixel(listOfMedianPoints.at(numberOfMedianPoint)
                         , listOfMedianPoints.at(numberOfMedianPoint - 1)));
}

bool Vectorizer::isLineThinning(Pixel *rightPoint, Pixel *leftPoint
                              , Pixel *previousRightPoint, Pixel *previousLeftPoint)
{
    switch (closestFixedDirection){
        case 0:
            if(rightPoint -> yCoordinate < previousRightPoint -> yCoordinate
            || leftPoint -> yCoordinate > previousLeftPoint -> yCoordinate){
                return true;
            }
            break;
        case 1:
            if(isLessPixel(rightPoint , previousRightPoint)
            || isMorePixel(leftPoint, previousLeftPoint)){
                return true;
            }
            break;
        case 2:
            if(rightPoint -> xCoordinate < previousRightPoint -> xCoordinate
            || leftPoint -> xCoordinate > previousLeftPoint -> xCoordinate){
                return true;
            }
            break;
        case 3:
            if(isLessMorePixel(rightPoint , previousRightPoint)
            || isMoreLessPixel(leftPoint, previousLeftPoint)){
                return true;
            }
            break;
        case 4:
            if(rightPoint -> yCoordinate > previousRightPoint -> yCoordinate
            || leftPoint -> yCoordinate < previousLeftPoint -> yCoordinate){
                return true;
            }
            break;
        case 5:
            if(isMorePixel(rightPoint , previousRightPoint)
            || isLessPixel(leftPoint, previousLeftPoint)){
                return true;
            }
            break;
        case 6:
            if(rightPoint -> xCoordinate > previousRightPoint -> xCoordinate
            || leftPoint -> xCoordinate < previousLeftPoint -> xCoordinate){
                return true;
            }
            break;
        case 7:
            if(isMoreLessPixel(rightPoint , previousRightPoint)
            || isLessMorePixel(leftPoint, previousLeftPoint)){
                return true;
            }
            break;
    }
    return false;
}

bool Vectorizer::stopCriterion(Pixel *rightPoint, Pixel *leftPoint)
{
    switch (closestFixedDirection){
        case 0:
            if(rightPoint -> yCoordinate < leftPoint -> yCoordinate){
                return true;
            }
            break;
        case 1:
            if(isLessPixel(rightPoint , leftPoint))
            {
                return true;
            }
            break;
        case 2:
            if(rightPoint -> xCoordinate < leftPoint -> xCoordinate){
                return true;
            }
            break;
        case 3:
            if(isLessMorePixel(rightPoint , leftPoint))
            {
                return true;
            }
            break;
        case 4:
            if(rightPoint -> yCoordinate > leftPoint -> yCoordinate){
                return true;
            }
            break;
        case 5:
            if(isMorePixel(rightPoint , leftPoint))
            {
                return true;
            }
            break;
        case 6:
            if(rightPoint -> xCoordinate > leftPoint -> xCoordinate){
                return true;
            }
            break;
        case 7:
            if(isMoreLessPixel(rightPoint , leftPoint))
            {
                return true;
            }
            break;
    }
    if(isEqualPixel(leftPoint, startPair ->leftPoint)
    && isEqualPixel(rightPoint, startPair -> rightPoint))
    {
        return true;
    }
    return false;
}

int Vectorizer::defineDirection(int firstDirection, int secondDirection
                                , int thirdDirection)
{
    int direction = 0;
    int closestFixedDirection = 0;
    int firstDistance = abs(directionPoint -> xCoordinate - startPoint -> xCoordinate);
    int secondDistance = static_cast<int>(
                abs(directionPoint -> yCoordinate + directionPoint -> xCoordinate
                  - startPoint -> xCoordinate - startPoint -> yCoordinate) / sqrt(2));
    int thirdDistance = abs(directionPoint -> yCoordinate - startPoint -> yCoordinate);
    direction = min(firstDistance, secondDistance);
    if(direction == thirdDirection){
        closestFixedDirection = min(firstDistance, thirdDistance)
                ? secondDirection : firstDirection;
    }
    else{
        closestFixedDirection = min(secondDistance, thirdDistance)
                ? thirdDirection : firstDirection;
    }
    return closestFixedDirection;
}

QList<QList<Pixel *> > Vectorizer::getListOfOutPutPoints()
{
    getStartPairOfOppositePoint();
    getlistOfPairOfOppositePoints();
    return listOfOutPutPoins;
}

void Vectorizer::getStartPairOfOppositePoint()
{
    int widthOfImage = image.width();
    int heightOfImage = image.height();
    if(directionPoint -> yCoordinate < startPoint -> yCoordinate){
        if(directionPoint -> xCoordinate > startPoint -> xCoordinate){
            closestFixedDirection = defineDirection(0, 1, 2);
        }
        if(directionPoint -> xCoordinate == startPoint -> xCoordinate){
            closestFixedDirection = 2;
        }
        if(directionPoint -> xCoordinate < startPoint -> xCoordinate){
            closestFixedDirection = defineDirection(4, 2, 3);
        }
    }
    if(directionPoint -> yCoordinate > startPoint -> yCoordinate){
        if(directionPoint -> xCoordinate > startPoint -> xCoordinate){
            closestFixedDirection = defineDirection(0, 6, 7);
        }
        if(directionPoint -> xCoordinate == startPoint -> xCoordinate){
            closestFixedDirection = 2;
        }
        if(directionPoint -> xCoordinate < startPoint -> xCoordinate){
            closestFixedDirection = defineDirection(4, 6, 5);
        }
    }
    if(directionPoint -> yCoordinate == startPoint -> yCoordinate){
        if(directionPoint -> xCoordinate > startPoint -> xCoordinate){
            closestFixedDirection = 0;
        }
        else{
            closestFixedDirection = 4;
        }
    }
    if(closestFixedDirection == 0 || closestFixedDirection == 4){
        for (int i = startPoint -> yCoordinate; i >= 0; i --){
            if(image.pixel(startPoint -> xCoordinate, i) == colorOfBackGround){
                if(closestFixedDirection == 4){
                    firstRightPoint = new Pixel(startPoint -> xCoordinate, i + 1);
                    break;
                }
                else{
                    firstLeftPoint = new Pixel(startPoint -> xCoordinate, i + 1);
                    break;
                }
            }
        }
        for (int i = startPoint->yCoordinate; i <= heightOfImage; i ++){
            if(image.pixel(startPoint->xCoordinate, i) == colorOfBackGround){
                if(closestFixedDirection == 4){
                    firstLeftPoint = new Pixel(startPoint->xCoordinate, i - 1);
                    break;
                }
                else{
                    firstRightPoint = new Pixel(startPoint->xCoordinate, i - 1);
                    break;
                }
            }
        }
    }
    if(closestFixedDirection == 1 || closestFixedDirection == 5){
        int i = startPoint -> xCoordinate;
        int j = startPoint -> yCoordinate;
        while(i >= 0 && j >= 0){
            if(image.pixel(i, j) == colorOfBackGround){
                if(closestFixedDirection == 1){
                    firstLeftPoint = new Pixel(i+1, j+1);
                    break;
                }
                else{
                    firstRightPoint = new Pixel(i+1, j+1);
                    break;
                }
            }
            i --;
            j --;
        }
        i = startPoint -> xCoordinate;
        j = startPoint -> yCoordinate;
        while(i <= widthOfImage && j <= heightOfImage){
            if(image.pixel(i, j) == colorOfBackGround){
                if(closestFixedDirection == 1){
                    firstRightPoint = new Pixel(i - 1, j - 1);
                    break;
                }
                else{
                    firstLeftPoint = new Pixel(i - 1, j - 1);
                    break;
                }
            }
            i ++;
            j ++;
        }
    }
    if(closestFixedDirection == 2 || closestFixedDirection == 6){
        for (int i = startPoint -> xCoordinate; i >= 0; i --){
            if(image.pixel(i, startPoint -> yCoordinate) == colorOfBackGround){
                if(closestFixedDirection == 2){
                    firstLeftPoint = new Pixel(i + 1, startPoint -> yCoordinate);
                    break;
                }
                else{
                    firstRightPoint = new Pixel(i + 1, startPoint -> yCoordinate);
                    break;
                }
            }
        }
        for (int i = startPoint -> xCoordinate; i <= widthOfImage; i ++){
            if(image.pixel(i, startPoint -> yCoordinate) == colorOfBackGround){
                if(closestFixedDirection == 2){
                    firstRightPoint = new Pixel(i - 1, startPoint -> yCoordinate);
                    break;
                }
                else{
                    firstLeftPoint = new Pixel(i - 1, startPoint -> yCoordinate);
                    break;
                }
            }
        }
    }
    if(closestFixedDirection == 3 || closestFixedDirection == 7){
        int i = startPoint -> xCoordinate;
        int j = startPoint -> yCoordinate;
        while(i <= widthOfImage && j >= 0){
            if(image.pixel(i, j) == colorOfBackGround){
                if(closestFixedDirection == 3){
                    firstRightPoint = new Pixel(i - 1, j + 1);
                    break;
                }
                else{
                    firstLeftPoint = new Pixel(i - 1, j + 1);
                    break;
                }
            }
            i ++;
            j --;
        }
        i = startPoint -> xCoordinate;
        j = startPoint -> yCoordinate;
        while(i >= 0 && j <= heightOfImage){
            if(image.pixel(i, j) == colorOfBackGround){
                if(closestFixedDirection == 3){
                    firstLeftPoint = new Pixel(i + 1, j - 1);
                    break;
                }
                else{
                    firstRightPoint = new Pixel(i + 1, j - 1);
                    break;
                }
            }
            i --;
            j ++;
        }
    }
    startPair = new PairOfOppositePoints(firstLeftPoint, firstRightPoint);
    return;
}

void Vectorizer::getlistOfPairOfOppositePoints()
{
    int countOfMedianPoint = 0;
    Pixel *previousRightPoint;
    Pixel *previousLeftPoint;
    Pixel *rightPoint;
    Pixel *leftPoint;
    ContourFollower *rightContourFollower = new ContourFollower(image, 3, true
                                                              , colorOfObject, colorOfBackGround);
    ContourFollower *leftContourFollower = new ContourFollower(image, 3, false
                                                             , colorOfObject, colorOfBackGround);
    listOfMedianPoints.append(createMedianPoint(startPair -> rightPoint, startPair -> leftPoint));
    countOfMedianPoint ++;
    rightPoint = rightContourFollower->contourFollowing(startPair -> rightPoint);
    leftPoint = leftContourFollower->contourFollowing(startPair -> leftPoint);
    listOfMedianPoints.append(createMedianPoint(rightPoint, leftPoint));
    countOfMedianPoint ++;
    if(branchingCriterion(countOfMedianPoint - 1))
    {
        defineBranches(listOfMedianPoints.at(countOfMedianPoint - 1));
        rightContourFollower -> ~ContourFollower();
        leftContourFollower -> ~ContourFollower();
        return;
    }
    previousRightPoint = startPair -> rightPoint;
    previousLeftPoint = startPair -> leftPoint;
    while(! stopCriterion(rightPoint, leftPoint)){
        previousRightPoint = rightPoint;
        previousLeftPoint = leftPoint;
        rightPoint = rightContourFollower->contourFollowing(rightPoint);
        leftPoint = leftContourFollower->contourFollowing(leftPoint);
        listOfMedianPoints.append(createMedianPoint(rightPoint, leftPoint));
        countOfMedianPoint ++;
        if(branchingCriterion(countOfMedianPoint - 1))
        {
            if(isLineThinning(rightPoint, leftPoint
                              , previousRightPoint, previousLeftPoint)){
                continue;
            }
            rightContourFollower -> ~ContourFollower();
            leftContourFollower -> ~ContourFollower();
            defineBranches(listOfMedianPoints.at(countOfMedianPoint - 1));
            return;
        }
    }
    //listOfOutPutPoins.append(listOfMedianPoints);
}
 void Vectorizer::defineBranches(Pixel *medialPoint)
 {
     QList<BracheCandidate *> listOfBranchesCandidate;
     QList<Circle *> listOfCicles;
     Pixel *currentPointOfContourFollowing;
     int numberOfMedianPoints = listOfMedianPoints.size() - 1;
     bool oppositPrevious = false;
     int numberOfCircles = 0;
     int numberOfCurrentBranche = 0;
     int centerXCoordinate = 0;
     int centerYCoordinate = 0;
     int radius = 0;
     for (int i = numberOfMedianPoints - 2; i >= 0; i --){
         centerXCoordinate =
                 pow((medialPoint->xCoordinate
                    - listOfMedianPoints.at(i) -> xCoordinate), 2);
         centerYCoordinate =
                 pow((medialPoint->yCoordinate
                    - listOfMedianPoints.at(i) -> yCoordinate), 2);
         radius =  sqrt(abs(centerXCoordinate + centerYCoordinate));
         listOfCicles.append(
                     new Circle(createCircle(medialPoint, radius)
                              , listOfMedianPoints.at(i)));
     }
     Circlefollower *circleFollower = new Circlefollower(image, listOfCicles, colorOfObject, colorOfBackGround);
     listOfBranchesCandidate = circleFollower -> circleFollowing();
//     for(int i = 0; i<listOfCicles.size(); i++){
//         for (int j = 0; j<listOfCicles.at(i)->circlePoints.size(); j++ ){
//             listOfPixel.append(listOfCicles.at(i)->circlePoints.at(j));
//         }
//     }
//     foreach(BracheCandidate * object,listOfBranchesCandidate){
//         listOfOpPoints.append(object->firstPoint);
//         listOfOpPoints.append(object->oppositePoint);
//     }
//     lisOfPlPr.append(circleFollower -> getPixelLeft());
//     lisOfPlPr.append(circleFollower -> getPixelRight());

     ContourFollower *contourFollower = new ContourFollower(image, 1, false, colorOfObject, colorOfBackGround);
     currentPointOfContourFollowing =
             contourFollower -> contourFollowing(circleFollower -> getPixelLeft());
     while(numberOfCurrentBranche == 0){
        foreach(BracheCandidate *branch, listOfBranchesCandidate){
            if(isEqualPixel(currentPointOfContourFollowing, branch -> firstPoint)){
                numberOfCurrentBranche++;
                branch->branchNumberOfTheFirstPoint = numberOfCurrentBranche;
                break;
            }
        }
        currentPointOfContourFollowing =
                contourFollower->contourFollowing(currentPointOfContourFollowing);
     }
     numberOfCircles = numberOfMedianPoints - 1;
     while(!isEqualPixel(currentPointOfContourFollowing
                         , circleFollower->getPixelRight())){
        foreach(BracheCandidate *branch, listOfBranchesCandidate){
            if(isEqualPixel(currentPointOfContourFollowing, branch -> firstPoint)){
                if(oppositPrevious){
                    numberOfCurrentBranche ++;
                    oppositPrevious = false;
                }
                branch -> branchNumberOfTheFirstPoint = numberOfCurrentBranche;
                if(branch -> circleNumber == numberOfCircles){
                    currentPointOfContourFollowing = branch -> oppositePoint;
                    branch->branchNumberOfTheOppositePoint = numberOfCurrentBranche;
                }
                break;
            }
            if(isEqualPixel(currentPointOfContourFollowing, branch -> oppositePoint)){
               branch -> branchNumberOfTheOppositePoint = numberOfCurrentBranche;
               oppositPrevious = true;
               break;
            }
        }
        currentPointOfContourFollowing =
                contourFollower -> contourFollowing(currentPointOfContourFollowing);
     }
     circleFollower -> ~Circlefollower();
     for(int count = 1; count <= numberOfCurrentBranche; count ++){
         listOfOutPutPoins.append(listOfMedianPoints);
         listOfMedianPoints.clear();
         foreach(BracheCandidate *branch, listOfBranchesCandidate){
             if(isBranch(branch, count)){
                 listOfMedianPoints.append(createMedianPoint(branch -> oppositePoint
                                                           , branch->firstPoint));
             }
         }
         int numberOfStartPoint = listOfMedianPoints.size() - 2;
         startPoint = listOfMedianPoints.at(numberOfStartPoint);
         directionPoint = listOfMedianPoints.at(numberOfStartPoint + 1);
         listOfOutPutPoins.append(listOfMedianPoints);
         listOfMedianPoints.clear();
         getStartPairOfOppositePoint();
         getlistOfPairOfOppositePoints();
     }
     listOfOutPutPoins.append(listOfMedianPoints);
     listOfMedianPoints.clear();
}

QList<Pixel *> Vectorizer::createCircle(Pixel *centerPoint, int radius)
{
    QList<Pixel *> circlePoints;
    QList<Pixel *> firstSector;
    QList<Pixel *> secondSector;
    QList<Pixel *> thirdSector;
    QList<Pixel *> fourthSector;
    int x = 0;
    int y = radius;
    int delta = 2 - 2 * radius;
    int error = 0;
    while(y >= 0) {
           firstSector.append(
                       new Pixel(centerPoint -> xCoordinate + x
                               , centerPoint -> yCoordinate + y));
           secondSector.append(
                       new Pixel(centerPoint -> xCoordinate + x
                               , centerPoint -> yCoordinate - y));
           thirdSector.append(
                       new Pixel(centerPoint -> xCoordinate  - x
                               , centerPoint->yCoordinate + y));
           fourthSector.append(
                       new Pixel(centerPoint -> xCoordinate - x
                               , centerPoint->yCoordinate - y));
            error = 2 * (delta + y) - 1;
            if(delta < 0 && error <= 0) {
                    ++ x;
                    delta += 2 * x + 1;
                    continue;
            }
            error = 2 * (delta - x) - 1;
            if(delta > 0 && error > 0) {
                    -- y;
                    delta += 1 - 2 * y;
                    continue;
            }
            ++ x;
            delta += 2 * (x - y);
            -- y;
    }
    for (int i = 0; i < thirdSector.size(); i ++){
        circlePoints.append(thirdSector.at(i));
    }
    for (int i = fourthSector.size() - 1; i >= 0; i --){
        circlePoints.append(fourthSector.at(i));
    }
    for (int i = 0; i < secondSector.size(); i ++){
        circlePoints.append(secondSector.at(i));
    }
    for (int i = firstSector.size() - 1; i >= 0; i --){
        circlePoints.append(firstSector.at(i));
    }
    firstSector.clear();
    secondSector.clear();
    thirdSector.clear();
    fourthSector.clear();
    return circlePoints;
}
