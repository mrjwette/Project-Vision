#ifndef NUMBERPLATE_H
#define NUMBERPLATE_H

#include "bwlabel.h"
#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QDebug>
#include <iostream>
#include <vector>
#include <algorithm>
#include <QMainWindow>

using namespace std;

class Numberplate
{
public:
    Numberplate();
    //void setHSV(QImage*, float, float, int, int, int, int, int, int);
    void init(QImage*);
    void loadMasks(int);
    int compareWithMasks(QImage*);
    QString getOutput();
    void setPixmap(QPixmap);
    QPixmap getPixmap();
private:
    QPixmap maskers[36];
    char maskerChar[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
    char output[8];
    QPixmap pixmap;
};

#endif // NUMBERPLATE_H
