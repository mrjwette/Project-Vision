#ifndef NUMBERPLATE_H
#define NUMBERPLATE_H

#define H_MIN 30 //Limit set to recognize Numberplate for HSV Hue (minimum)
#define H_MAX 55 //Limit set to recognize Numberplate for HSV Hue (maximum)
#define S_MIN 60 //Limit set to recognize Numberplate for HSV Saturation (minimum)
#define S_MAX 100
#define V_MIN 75 //Limit set to recognize Numberplate for HSV Value (minimum)
#define V_MAX 100

#define HSV_H 1         //Translate QT HSV Values to Paint.net values
#define HSV_S 2.55      //Translate QT HSV Values to Paint.net values
#define HSV_V 2.55      //Translate QT HSV Values to Paint.net values

#include <QMainWindow>
#include <QDebug>

class Numberplate
{
public:
    Numberplate();
    void loadMasks(int);
    int compareWithMasks(QImage);
private:
    QPixmap maskers[36];
    char maskerChar[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
    char output[7];
};

#endif // NUMBERPLATE_H
