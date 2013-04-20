#ifndef CIRCLEFOLLOWER_H
#define CIRCLEFOLLOWER_H

#include <vectorizer.h>

class Circlefollower
{
public:
    Circlefollower(QImage image, QList<Circle *> circles
                 , QRgb colorOfObject, QRgb colorOfBackGraund);
    ~Circlefollower();
    QList<BracheCandidate *> circleFollowing();
    Pixel *getPixelLeft();
    Pixel *getPixelRight();
private:
    QImage  image;
    Pixel *pixelLeft;
    Pixel *pixelRight;
    QList<Circle *> circles;
    QRgb colorOfObject;
    QRgb colorOfBackGraund;
    QList<BracheCandidate *> listOfPairOfOppositePoint;
};

#endif // CIRCLEFOLLOWER_H
