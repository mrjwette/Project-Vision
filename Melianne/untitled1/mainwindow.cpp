#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bwlabel.h"
#include "ObjectBwLabel.h"
#include "numberplate.h"

#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QDebug>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXPICINPUTWIDTH 269 // Maximum width for a picture
#define MAXPICINPUTHEIGHT 156 // Maximum height for a picture
#define MAX_Capable_Objects 100 //Maximum amount objects possible per image, set well above expected object count

#define resize 1        //If you want to downscale images to smaller images for faster processing
//When resize is set to 0, set scalingfactor to 1
#define Scalingfactor 1         // Images get scaled down during the process. This is how much
#define OFFSETPICADJUST 0 // When using images that do not resize well, increase this.
#define OffsetBWLabel 2

#define debugI 1        //Set 1 for qDebug() << Set 0 for none
#define Export 0        //If you want to export the image
#define DROPOBJ 100     //If an object is less then 100 pixels bwlabel will not see it
#define HSV_H 1         //Translate QT HSV Values to Paint.net values
#define HSV_S 2.55      //Translate QT HSV Values to Paint.net values
#define HSV_V 2.55      //Translate QT HSV Values to Paint.net values

#define S_Border 40     //Limit set to recoqnize Dice for HSV Saturation
#define V_Border 67     //Limit set to recoqnize Dice for HSV Value
/*
#define H_MIN 0        //Limit set to recognize Numberplate for HSV Hue (minimum)
#define H_MAX 360        //Limit set to recognize Numberplate for HSV Hue (maximum)
#define S_MIN 0        //Limit set to recognize Numberplate for HSV Saturation (minimum)
#define S_MAX 40       //Limit set to recognize Numberplate for HSV Saturation (maximum)
#define V_MIN 67        //Limit set to recognize Numberplate for HSV Value (minimum)
#define V_MAX 100       //Limit set to recognize Numberplate for HSV Value (maximum)
*/

#define H_MIN 30        //Limit set to recognize Numberplate for HSV Hue (minimum)
#define H_MAX 55        //Limit set to recognize Numberplate for HSV Hue (maximum)
#define S_MIN 60        //Limit set to recognize Numberplate for HSV Saturation (minimum)
#define S_MAX 100       //Limit set to recognize Numberplate for HSV Saturation (maximum)
#define V_MIN 75        //Limit set to recognize Numberplate for HSV Value (minimum)
#define V_MAX 100       //Limit set to recognize Numberplate for HSV Value (maximum)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetHSV(QImage *image, float MaxpixY, float MaxpixX, int h_min, int h_max, int s_min, int s_max, int v_min, int v_max)
{
    for (int i = 0; i < MaxpixY; i++)
    {
        for (int j = 0; j < MaxpixX; j++)
        {
            QColor pixel(image->pixel(j, i));
            int h, s, v;
            pixel.getHsv(&h, &s, &v);
            double H, S, V;
            H = h / HSV_H;
            S = s / HSV_S;
            V = v / HSV_V;
            //qDebug() << h << s << v;
            if (H >= h_min && H <= h_max && S >= s_min && S <= s_max && V >= v_min && V <= v_max)
            {
                QRgb WHITE = qRgb(255, 255, 255);
                image->setPixelColor(j, i, WHITE);
            }
            else
            {
                QRgb BLACK = qRgb(0, 0, 0);
                image->setPixelColor(j, i, BLACK);
            }
        }
    }
}

void ResizePic(QImage * image, QImage * resizeimage, int MaxpixY, int MaxpixX)
{
    for (int i = 0; i < MaxpixY - OFFSETPICADJUST; i = i + Scalingfactor / 2)
    {
        for (int j = 0; j < MaxpixX - OFFSETPICADJUST; j = j + Scalingfactor / 2)
        {
            resizeimage->setPixel(j / Scalingfactor, i / Scalingfactor, image->pixel(j, i));
        }
    }
}

//BWLabel and regionprops, insert and image with objects as white pixels.
//It will return a list of objects it finds, these objects contain the x and y of each object.
//Smallesobj is the smallest object wanted, for example if this is 100, any object within the picture smaller then 100 pixels will not be returned.
void BWlabel(QImage * image, int MaxpixY, int MaxpixX, ObjectBwLabel * objarray, int * retObjAmount, int SmallesObj)
{
    int CC = 0;
    auto height = MaxpixY;
    auto width = MaxpixX;
    auto conflicts = new int[MAX_Conflicts][2];
    int conflictCounter = 0;
    //int temp = 0;


    QRgb WHITE = qRgb(255,255,255);
    QRgb RED = qRgb(255,0,0);

    int picarray[MAXPICINPUTWIDTH/Scalingfactor][MAXPICINPUTHEIGHT/Scalingfactor];

    //Set QImage to a 2D array, easier to manipulate.
    for(int i = 0;i<MaxpixY;i++)
    {
        for(int j = 0;j<MaxpixX;j++)
        {
            if(image->pixel(j,i) == WHITE)
            {
                picarray[j][i] = 1;
            }
            else {
                picarray[j][i] = 0;
            }
        }
    }


    //BWLabel itself, will mark everything in the image. No conflicts fixed yet.
    for(int y = 1; y < height; y++)
    {
        for(int x = 1; x < width ; x++)
        {
            if(picarray[x][y] == 1)
            {
                if(picarray[x-1][y] == 0 && picarray[x][y-1] == 0 )
                {
                    CC++;
                    picarray[x][y] = CC;
                }
                else if(picarray[x-1][y] >= 1 && picarray[x][y-1] == 0)
                {
                    picarray[x][y] = picarray[x-1][y];
                }
                else if(picarray[x-1][y] == 0 && picarray[x][y-1] >= 1)
                {
                    picarray[x][y] = picarray[x][y-1];
                }
                else {
                    if(picarray[x-1][y] <= picarray[x][y-1])
                    {
                        picarray[x][y] = picarray[x-1][y];
                    }
                    else {
                        picarray[x][y] = picarray[x][y-1];
                    }
                }
            }
        }
    }

    //Mark all conflicts in a conflicts array. These will be fixed later on
    for(int y = 1; y < height; y++){
        for(int x = 1; x < width ; x++){
            if(picarray[x-1][y] != 0 && picarray[x-1][y] != picarray[x][y] && picarray[x][y] != 0){
                conflicts[conflictCounter][0] = picarray[x][y];
                conflicts[conflictCounter++][1] = picarray[x-1][y];
            }
            if(picarray[x][y-1] != 0 && picarray[x][y-1] != picarray[x][y] && picarray[x][y] != 0){
                conflicts[conflictCounter][0] = picarray[x][y];
                conflicts[conflictCounter++][1] = picarray[x][y-1];
            }
        }
    }

    //    for(int i = 0; i < conflictCounter; i++){
    //        if(conflicts[i][0] < conflicts[i][1]){
    //            temp = conflicts[i][0];
    //            conflicts[i][0] = conflicts[i][1];
    //            conflicts[i][1] = temp;
    //        }
    //    }

    //Fix conflicts
    for(int i = 0; i < conflictCounter; i++)
    {
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                if(picarray[x][y] == conflicts[i][0]){
                    picarray[x][y] = conflicts[i][1];
                }
            }
        }
    }

    //Debug, output the picture after BWLabel fixing.
    if(debugI)
    {
        for(int y = 0; y < height; y++){
            QDebug deb = qDebug();
            deb << "Row: " << y;
            for(int x = 0; x < width; x++){
                deb << picarray[x][y];
            }
        }
    }

    //Count objects in the image. Stored in vector for easy pushing
    QVector<int> Objects;
    QVector<int>::iterator IT;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            IT = find(Objects.begin(),Objects.end(),picarray[x][y]);
            if(IT == Objects.end())
            {
                Objects.push_back(picarray[x][y]);
            }
        }
    }

    //Vector to int, contains the amount of found objects in the picture.
    int ObjAmount = Objects.size();

    //Assign found objects to the objarray. Setting the labelcounter as found by the vector above.
    for(int i = 0;i<ObjAmount;i++)
    {
        ObjectBwLabel temp;
        temp.Labelcounter = Objects.front();
        Objects.pop_front();
        if(debugI)qDebug() << temp.Labelcounter;
        objarray[i] = temp;
    }

    //Count the amount of pixels per object.
    if(debugI)qDebug() << Objects;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(picarray[x][y] != 0)
            {
                for(int i = 1;i<ObjAmount;i++)
                {
                    if(objarray[i].Labelcounter == picarray[x][y])
                    {
                        objarray[i].BlockCount++;
                    }

                }
            }
        }
    }

    //Retur the Labelcounter and amount of blocks in debug
    if(debugI)
    {
        for(int i = 1;i<ObjAmount;i++)
        {
            qDebug() << "LC: " << objarray[i].Labelcounter<< "BC: " << objarray[i].BlockCount;
        }
    }

    //If the blockamount of a certain object is below the set threshold it will be removed from the list.
    for(int i = 1;i<ObjAmount;i++)
    {
        if(objarray[i].BlockCount < SmallesObj)
        {
            for(int p = i;p<ObjAmount-1;p++)
            {
                objarray[p] = objarray[p+1];
            }
            ObjAmount--;
            i--;
        }
    }

    //Retur the Labelcounter and amount of blocks in debug after removing the objects lower then the threshold
    for(int i = 1;i<ObjAmount;i++)
    {
        if(debugI)qDebug() << "LC: " << objarray[i].Labelcounter<< "BC: " << objarray[i].BlockCount;
    }

    //per object checking each pixel to find the most Left, Right, Up and down pixel. These are stored in the object.
    for(int o = 0;o<ObjAmount;o++)
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                if(picarray[x][y] == objarray[o].Labelcounter)
                {
                    if(objarray[o].set == false)
                    {
                        objarray[o].R = x;
                        objarray[o].L = x;
                        objarray[o].D = y;
                        objarray[o].U = y;
                        objarray[o].set = true;
                    }

                    if(x > objarray[o].R)
                    {
                        objarray[o].R = x;
                    }
                    if(x < objarray[o].L)
                    {
                        objarray[o].L = x;
                    }
                    if(y < objarray[o].U)
                    {
                        objarray[o].U = y;
                    }
                    if(y > objarray[o].D)
                    {
                        objarray[o].D = y;
                    }
                }
            }
        }
    }

    //Mark the object in the image for visual confirmation.
    for(int i = 0;i<ObjAmount;i++)
    {
        image->setPixel(objarray[i].R,objarray[i].U,RED);
        image->setPixel(objarray[i].R,objarray[i].D,RED);
        image->setPixel(objarray[i].L,objarray[i].U,RED);
        image->setPixel(objarray[i].L,objarray[i].D,RED);
    }

    *retObjAmount = ObjAmount;

}
//This will extract the images from the main image and dump them into the QImage of each object.
//count is the amount of objects inside the list. This will not be adjusted.
void SetImages(QImage* image,ObjectBwLabel * objarray, int * count)
{
    int C = *count;
    for (int i = 1;i<C; i++) {
        objarray[i].image = QPixmap(objarray[i].R - objarray[i].L,objarray[i].D - objarray[i].U).toImage();

        int height = 0;
        int width = 0;
        for(int y = objarray[i].U;y<objarray[i].D;y++)
        {
            for(int x = objarray[i].L;x <objarray[i].R;x++)
            {
                objarray[i].image.setPixel(width,height,image->pixel(x,y));
                width++;
            }
            objarray[i].imwidth = width;
            width = 0;
            height++;
        }
        objarray[i].imheight = height;


        height = 0;
        width = 0;

    }





}

void Removeborder(ObjectBwLabel * objarray, int * count)
{
    QRgb BLACK = qRgb(0, 0, 0);
    QRgb WHITE = qRgb(255, 255, 255);
    int C = *count;
    for (int i = 1; i < C; i++)
    {
        qDebug() << objarray[i].imheight << objarray[i].imwidth;
        for (int y = 0; y < objarray[i].imheight; y++) {
            for (int x = 0; x < objarray[i].imwidth; x++) {
                if (objarray[i].image.pixel(x, y) == BLACK)
                {
                    objarray[i].image.setPixel(x, y, WHITE);
                }
                else {
                    objarray[i].image.setPixel(x, y, BLACK);
                }
            }
        }
    }

}

void MainWindow::on_letterDice_clicked()
{
    QString filename =  QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
    QImage image(filename);
    image = image.convertToFormat(QImage::Format_RGB32);

    int MaxpixY = image.height();//Test is 11
    int MaxpixX = image.width(); // Test is 10
    qDebug() << MaxpixX << MaxpixY;

    SetHSV(&image,MaxpixY, MaxpixX, H_MIN, H_MAX, S_MIN, S_MAX, V_MIN, V_MAX);

    ObjectBwLabel objarray[MAX_Capable_Objects];
    int ObjAmount = 0;

    BWLabel bwlbl = BWLabel();
    bwlbl.Setdebug(debugI);
    bwlbl.SetImage(image);
    bwlbl.SetResizefactor(Scalingfactor);
    bwlbl.ResizeIm(&MaxpixY,&MaxpixX);
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,100);
    bwlbl.SetImages(objarray, &ObjAmount);
    QImage image1 = bwlbl.GetImage();
    bwlbl.Removeborder(objarray, &ObjAmount);

    qDebug() << ObjAmount;



    QPixmap pixDobb[8];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        ObjectBwLabel objarrayt[50];
        int ObjAmountt = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(1);
        bwlbl.Setdebug(1);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,20);
        objarray[i].s = QString::number(ObjAmountt);
        objarray[i].image = bwlbl.GetImage();
        QImage image2 = objarray[i].image.scaled(141, 91, Qt::KeepAspectRatio);
        QPixmap imagepix;
        imagepix.convertFromImage(image2,Qt::AutoColor);
        pixDobb[i] = imagepix;
    }


    //ui->output->setText(objarray[0].s);
    //ui->output_2->setText(objarray[1].s);
    //ui->output_3->setText(objarray[2].s);
    ui->photo_2->setPixmap(pixDobb[0]);
    ui->photo_3->setPixmap(pixDobb[1]);
    ui->photo_4->setPixmap(pixDobb[2]);
    ui->photo_5->setPixmap(pixDobb[3]);

    QImage image2 = image1.scaled(741, 431, Qt::KeepAspectRatio);
    QPixmap imagepix;
    imagepix.convertFromImage(image2,Qt::AutoColor);

    QPixmap Imageexport;
    Imageexport.convertFromImage(objarray[1].image,Qt::AutoColor);

    if(Export)
    {
        QFile file("Export.png");
        file.open(QIODevice::WriteOnly);
        Imageexport.save(&file, "PNG");
    }
    ui->photo->setPixmap(imagepix);

}

void MainWindow::on_numberplate_clicked()
{
    QString filename = QFileDialog::getOpenFileName
            (
                this, "Open Document",QDir::currentPath(), "All files (*.*)"                            //opens a window where you can select a file
                );

    QImage image(filename);
    QImage image2 = image;

    for (int i = 0; i < image2.height(); i++)
    {
        for (int j = 0; j < image2.width(); j++)
        {
            QColor pixel(image2.pixel(j, i));
            int h, s, v;
            pixel.getHsv(&h, &s, &v);
            double H, S, V;
            H = h / HSV_H;
            S = s / HSV_S;
            V = v / HSV_V;
            //qDebug() << h << s << v;
            if (H >= H_MIN && H <= H_MAX && S >= S_MIN && S <= S_MAX && V >= V_MIN && V <= V_MAX)
            {
                QRgb WHITE = qRgb(255, 255, 255);
                image.setPixelColor(j, i, WHITE);
            }
            else
            {
                QRgb BLACK = qRgb(0, 0, 0);
                image.setPixelColor(j, i, BLACK);
            }
        }
    }

    image2 = image2.convertToFormat(QImage::Format_Mono);                                         //change the photo to a BW photo

    QPixmap pix;
    pix.fromImage(image2);
    ui->photo->setPixmap(pix);
}
