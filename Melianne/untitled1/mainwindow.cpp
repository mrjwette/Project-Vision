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

#define resize 8        //If you want to downscale images to smaller images for faster processing
//When resize is set to 0, set scalingfactor to 1
#define Scalingfactor 1         // Images get scaled down during the process. This is how much
#define OFFSETPICADJUST 0 // When using images that do not resize well, increase this.
#define OffsetBWLabel 2

#define debugI 0        //Set 1 for qDebug() << Set 0 for none
#define Export 1        //If you want to export the image
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
#define H_MAX 60        //Limit set to recognize Numberplate for HSV Hue (maximum)
#define S_MIN 50        //Limit set to recognize Numberplate for HSV Saturation (minimum)
#define S_MAX 100       //Limit set to recognize Numberplate for HSV Saturation (maximum)
#define V_MIN 50        //Limit set to recognize Numberplate for HSV Value (minimum)
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

void MainWindow::sortOutput()
{
    int out, in;
    int n = 6;

    for(int i = 0; i < 6; i++)
    {
        qDebug() << outputInt[i] << outputChar[i];
    }

    qDebug();

    for (out = n - 1; out > 1; out--)
    {
        for (in = 0; in < out; in++)
        {
            if (outputInt[in] > outputInt[in + 1])
            {
                int tempInt = outputInt[in];
                char tempChar = outputChar[in];

                outputInt[in] = outputInt[in + 1];
                outputChar[in] = outputChar[in + 1];

                outputInt[in + 1] = tempInt;
                outputChar[in + 1] = tempChar;
            }
        }
    }

    qDebug();

    for(int i = 0; i < 6; i++)
    {
        qDebug() << outputInt[i] << outputChar [i];
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

    image.invertPixels();
    ObjectBwLabel objarray[MAX_Capable_Objects];
    int ObjAmount = 0;

    BWLabel bwlbl = BWLabel();
    bwlbl.Setdebug(debugI);
    bwlbl.SetImage(image);
    bwlbl.SetResizefactor(Scalingfactor);
    bwlbl.ResizeIm(&MaxpixY,&MaxpixX);
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,100);
    bwlbl.SetImages(objarray, &ObjAmount);
    bwlbl.Removeborder(objarray, &ObjAmount);
    QImage image1 = bwlbl.GetImage();

    QPixmap pixDobb[6];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        Numberplate NP;
        ObjectBwLabel objarrayt[50];
        int ObjAmountt = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(1);
        bwlbl.Setdebug(1);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,80);
        objarray[i].s = QString::number(ObjAmountt);
        objarray[i].image = bwlbl.GetImage();
        NP.loadMasks(objarray[i].image.height(), objarray[i].image.width());
        int index = NP.compareWithMasks(&objarray[i].image);
        outputChar[i] = maskerChar[index];
        qDebug() << "L: " << objarray[i].L << "R: " << objarray[i].R << "U: " << objarray[i].U << "D: " << objarray[i].D;
        outputInt[i] = objarray[i].L;
        QImage image2 = objarray[i].image.scaled(141, 91, Qt::KeepAspectRatio);
        QPixmap imagepix;
        imagepix.convertFromImage(image2,Qt::AutoColor);
        pixDobb[i] = imagepix;
    }


    image = image.scaled(741, 431, Qt::KeepAspectRatio);
    QPixmap pix;
    pix.convertFromImage(image);
    ui->photo->setPixmap(pix);

}

void MainWindow::on_numberplate_clicked()
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

    image.invertPixels();

    ObjectBwLabel objarray[MAX_Capable_Objects];
    int ObjAmount = 0;

    BWLabel bwlbl = BWLabel();
    bwlbl.Setdebug(debugI);
    bwlbl.SetImage(image);
    bwlbl.SetResizefactor(Scalingfactor);
    bwlbl.ResizeIm(&MaxpixY,&MaxpixX);
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,75);
    bwlbl.SetImages(objarray, &ObjAmount);
    bwlbl.Removeborder(objarray, &ObjAmount);
    QImage image1 = bwlbl.GetImage();

    QPixmap pixDobb[6];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        Numberplate NP;
        ObjectBwLabel objarrayt[50];
        int ObjAmountt = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(1);
        bwlbl.Setdebug(1);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,75);
        objarray[i].s = QString::number(ObjAmountt);
        objarray[i].image = bwlbl.GetImage();
        NP.loadMasks(objarray[i].image.height(), objarray[i].image.width());
        int index = NP.compareWithMasks(&objarray[i].image);
        outputChar[i] = maskerChar[index];
        qDebug() << "L: " << objarray[i].L << "R: " << objarray[i].R << "U: " << objarray[i].U << "D: " << objarray[i].D;
        outputInt[i] = objarray[i].L;
        QImage image2 = objarray[i].image.scaled(141, 91, Qt::KeepAspectRatio);
        QPixmap imagepix;
        imagepix.convertFromImage(image2,Qt::AutoColor);
        pixDobb[i] = imagepix;
    }

    sortOutput();

    QVector<char> outputPlate;

    for (int i = 0; i < 6; i++)
    {
        outputPlate.push_back(outputChar[i]);
        if(isdigit(outputChar[i]) && isalpha(outputChar[i+1]))
        {
            outputPlate.push_back('-');
        }
        else if(isalpha(outputChar[i]) && isdigit(outputChar[i+1]))
        {
            outputPlate.push_back('-');
        }
    }

    string out(outputPlate.begin(), outputPlate.end());
    QString out2 = QString::fromStdString(out);
    ui->output->setText(out2);

    ui->photo_1->setPixmap(pixDobb[0]);
    ui->photo_2->setPixmap(pixDobb[1]);
    ui->photo_3->setPixmap(pixDobb[2]);
    ui->photo_4->setPixmap(pixDobb[3]);
    ui->photo_5->setPixmap(pixDobb[4]);
    ui->photo_6->setPixmap(pixDobb[5]);

    image1 = image1.scaled(741, 431, Qt::KeepAspectRatio);
    QPixmap pix;
    pix.convertFromImage(image1);
    ui->photo->setPixmap(pix);


    QPixmap Imageexport;
    Imageexport.convertFromImage(objarray[1].image,Qt::AutoColor);

    //to export the photo, please change the definition of Export to 1
    if(Export)
    {
        QFile file("Export.png");
        file.open(QIODevice::WriteOnly);
        Imageexport.save(&file, "PNG");
    }
    out2.clear();
}
