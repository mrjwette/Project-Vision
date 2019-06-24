#ifndef ObjectObjectBwLabel_H
#define ObjectObjectBwLabel_H
#include <qimage.h>

class ObjectBwLabel
{
public:
    ObjectBwLabel();

    int U; // Most up point         (Y-as)
    int R; // Most right point      (X-as)
    int L; // Most left point       (X-as)
    int D; // Most down point       (Y-as)

    int Labelcounter;
    bool set = false;
    int BlockCount = 0;
    QImage image;
    int imheight = 0;
    int imwidth = 0;
    QString s;

};

#endif // OBJECT_H
