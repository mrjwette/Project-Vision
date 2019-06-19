#ifndef ObjectObjectBwLabel_H
#define ObjectObjectBwLabel_H
#include <qimage.h>

class ObjectBwLabel
{
public:
    ObjectBwLabel();

    int U; // Most up point
    int R; // Most right point
    int L; // Most left point
    int D; // Most down point

    int Labelcounter;
    bool set = false;
    int BlockCount;
    QImage image;
    int imheight;
    int imwidth;
    QString s;
};

#endif // OBJECT_H
