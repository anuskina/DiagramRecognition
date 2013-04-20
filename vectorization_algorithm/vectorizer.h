#ifndef VECTORIZER_H
#define VECTORIZER_H
#include <QList>
#include <QImage>

struct Pixel
{
    Pixel(int xCoordinate, int yCoordinate)
        : xCoordinate(xCoordinate), yCoordinate(yCoordinate){}
    int xCoordinate;
    int yCoordinate;
};

struct BracheCandidate
{
    BracheCandidate(Pixel *firstPoint, Pixel *oppositePoint, int circleNumber
                  , int branchNumberOfTheFirstPoint
                  , int branchNumberOfTheOppositePoint)
        : firstPoint(firstPoint), oppositePoint(oppositePoint), circleNumber(circleNumber)
        , branchNumberOfTheFirstPoint(branchNumberOfTheFirstPoint)
        , branchNumberOfTheOppositePoint(branchNumberOfTheOppositePoint){}
    Pixel *firstPoint;
    Pixel *oppositePoint;
    int circleNumber;
    int branchNumberOfTheFirstPoint;
    int branchNumberOfTheOppositePoint;
};

struct Circle
{
    Circle (QList<Pixel * > circlePoints, Pixel *startMedianPoint)
        : circlePoints (circlePoints), startMedianPoint(startMedianPoint){}
    QList<Pixel *> circlePoints;
    Pixel *startMedianPoint;
};

struct PairOfOppositePoints
{
    PairOfOppositePoints(Pixel *leftPoint, Pixel *rightPoint)
        : leftPoint(leftPoint), rightPoint(rightPoint){}
    Pixel *leftPoint;
    Pixel *rightPoint;
};

class Vectorizer
{
public:
    Vectorizer(QImage image, Pixel *startPoint, Pixel *directionPoint
             , QRgb colorOfObject, QRgb colorOfBackGround);
    ~Vectorizer();
    QList<QList<Pixel *> > getListOfOutPutPoints();
    QList<Pixel *> getListOfPixel();
    QList<Pixel *> getListOfOpPoints();
    QList<Pixel *> getListOfPlPr();
private:
    int defineDirection(int firstDirection, int secondDirection
                      , int thirdDirection);
    bool stopCriterion(Pixel *rightPoint, Pixel *leftPoint);
    bool branchingCriterion(int numberOfMedianPoint);
    bool isEqualPixel(Pixel *firstPixel, Pixel *secondPixel);
    bool isMorePixel(Pixel *firstPixel, Pixel *secondPixel);
    bool isMoreLessPixel(Pixel *firstPixel, Pixel *secondPixel);
    bool isLessMorePixel(Pixel *firstPixel, Pixel *secondPixel);
    bool isLessPixel(Pixel *firstPixel, Pixel *secondPixel);
    bool isBranch(BracheCandidate *branch, int currentBranch);
    bool isLineThinning(Pixel *rightPoint, Pixel *leftPoint
                      , Pixel *previousRightPoint, Pixel *previousLeftPoint);
    void getStartPairOfOppositePoint();
    void getlistOfPairOfOppositePoints();
    void defineBranches(Pixel *medialPoint);
    Pixel *createMedianPoint(Pixel *firstPixel, Pixel *secondPixel);
    QList<Pixel *> createCircle(Pixel *centerPoint, int radius);
    int closestFixedDirection;
    QImage image;
    Pixel *startPoint;
    Pixel *directionPoint;
    QRgb colorOfObject;
    QRgb colorOfBackGround;
    Pixel *firstRightPoint;
    Pixel *firstLeftPoint;
    PairOfOppositePoints *startPair;
    QList<Pixel *> listOfMedianPoints;
//    QList<Pixel *> listOfPixel;
//    QList<Pixel *> listOfOpPoints;
//    QList<Pixel *> lisOfPlPr;
    QList<QList<Pixel *> > listOfOutPutPoins;
};

#endif // VECTORIZER_H
