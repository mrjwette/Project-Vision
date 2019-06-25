#ifndef BWLABEL_H
#define BWLABEL_H
#include <QImage>
#include <ObjectBwLabel.h>
#include <qdebug.h>
#include <QImage>
#include "QString"
#include "QDebug"
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
    QImage GetImage();
    void SetImage(QImage temp);
    void BWLabel_RegionProps(int MaxpixY, int MaxpixX, ObjectBwLabel * objarray, int * retObjAmount, int SmallesObj, int resetFirstRow);
    void ResizeIm(int * MaxpixY, int * MaxpixX);
    void SetResizefactor(int);
    void Setdebug(bool);
    void SetImages(ObjectBwLabel * objarray, int * count);
    void Invert(ObjectBwLabel * objarray, int * count);
    void RemoveBorders(ObjectBwLabel * objarray, int * count);
    void AdjustCC(int);

private:
    QRgb picarraygetC(int x,int y);
    void picarraysetC(int x,int y,QRgb C);
    void DebugPicarray(bool debug, int MaxpixY, int MaxpixX, int** picarray);
    void DebugLCBC(bool debug, int ObjAmount, ObjectBwLabel * objarray);
    QImage image;
    QRgb WHITE = qRgb(255,255,255);
    QRgb BLACK = qRgb(0,0,0);
    QRgb RED = qRgb(255,0,0);
    bool debug = false;
    int ResizeFactor = 1;
    int CCstart = 0;

};

#endif // BWLABEL_H
