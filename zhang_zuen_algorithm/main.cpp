#include <QtGui/QApplication>
#include "skeletonization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Skeletonization w;
    w.show();
    
    return a.exec();
}
