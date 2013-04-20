#ifndef CONTOURFOLLOWER_H
#define CONTOURFOLLOWER_H

#include <vectorizer.h>

class ContourFollower
{
public:
    ContourFollower(QImage image, int followDistance, bool isRightContourFollower
                  , QRgb colorOfObject, QRgb colorOfBackGround);
    ~ContourFollower();
    Pixel *contourFollowing(const Pixel *startPoint);
private:
    void createNeighbourForRightContourFollower(Pixel const *pixel);
    void createNeighbourForLeftContourFollower(Pixel const *pixel);
    QImage  image;
    int followDistance;
    bool isRightContourFollower;
    QRgb colorOfObject;
    QRgb colorOfBackGround;
    QList<Pixel *>  eightConnectedNeighbor;
};

#endif // CONTOURFOLLOWER_H
