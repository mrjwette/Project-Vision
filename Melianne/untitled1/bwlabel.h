#ifndef BWLABEL_H
#define BWLABEL_H
#include <QImage>
#include <qdebug.h>
#include <QImage>
#include <QString>
#include <QDebug>
#include <iostream>
#include <vector>
#include <algorithm>
#include <QPixmap>
#include "ObjectBwLabel.h"

#define MAX_Conflicts 200000

class BWLabel
{
public:
    BWLabel();
    void picarraysetC(int x,int y,QRgb C);
    QImage GetImage();
    QRgb picarraygetC(int x,int y);
    void SetImage(QImage temp);
    void BWLabel_RegionProps(int MaxpixY, int MaxpixX, ObjectBwLabel * objarray, int * retObjAmount, int SmallesObj);
    void ResizeIm(int * MaxpixY, int * MaxpixX);
    void SetResizefactor(int);
    void Setdebug(bool);
    void SetImages(ObjectBwLabel * objarray, int * count);
    void Removeborder(ObjectBwLabel * objarray, int * count);
private:
    QImage image;
    QRgb WHITE = qRgb(255,255,255);
    QRgb BLACK = qRgb(0,0,0);
    QRgb RED = qRgb(255,0,0);
    bool debug = false;
    int ResizeFactor = 1;

};

#endif // BWLABEL_H
