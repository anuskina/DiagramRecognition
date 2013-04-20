#include <contourfollower.h>

ContourFollower::ContourFollower(QImage image, int followDistance
                               , bool isRightContourFollower
                               , QRgb colorOfObject, QRgb colorOfBackGround)
    : image(image), followDistance(followDistance)
    , isRightContourFollower(isRightContourFollower)
    , colorOfObject(colorOfObject), colorOfBackGround(colorOfBackGround)
{
}

ContourFollower::~ContourFollower()
{
}

void ContourFollower::createNeighbourForRightContourFollower(const Pixel *pixel)
{
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate + 1));
}
void ContourFollower::createNeighbourForLeftContourFollower(const Pixel *pixel)
{
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate + 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate - 1, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate, pixel -> yCoordinate - 1));
    eightConnectedNeighbor.append(
                new Pixel(pixel -> xCoordinate + 1, pixel -> yCoordinate - 1));
}

Pixel *ContourFollower::contourFollowing(Pixel const *startPoint)
{
    Pixel *currentPoint = new Pixel(startPoint->xCoordinate, startPoint->yCoordinate);
    int numberOfContourPoint = 0;
    while (numberOfContourPoint < followDistance){
        if(isRightContourFollower){
            createNeighbourForRightContourFollower(currentPoint);
        }
        else{
            createNeighbourForLeftContourFollower(currentPoint);
        }
        int indexOfNeighbor = 0;
        foreach (Pixel const *neighbor, eightConnectedNeighbor) {
            if(image.pixel(neighbor->xCoordinate, neighbor -> yCoordinate)== colorOfBackGround){
                if(indexOfNeighbor == 7)
                {
                    if(image.pixel(eightConnectedNeighbor.at(0) -> xCoordinate,
                                   eightConnectedNeighbor.at(0) -> yCoordinate) == colorOfObject)
                    {
                        currentPoint = eightConnectedNeighbor.at(0);
                        numberOfContourPoint ++;
                        eightConnectedNeighbor.clear();
                        break;
                    }
                }
                else
                {
                    if(image.pixel(eightConnectedNeighbor.at(indexOfNeighbor + 1)
                                   -> xCoordinate,
                                   eightConnectedNeighbor.at(indexOfNeighbor + 1)
                                   -> yCoordinate) == colorOfObject)
                    {
                        currentPoint = eightConnectedNeighbor.at(indexOfNeighbor + 1);
                        numberOfContourPoint ++;
                        eightConnectedNeighbor.clear();
                        break;
                    }
                }
            }
            indexOfNeighbor ++;
        }
    }
    return currentPoint;
}
