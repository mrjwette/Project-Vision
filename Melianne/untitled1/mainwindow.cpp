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

#define MAXPICINPUTWIDTH 1920 // Maximum width for a picture
#define MAXPICINPUTHEIGHT 1080 // Maximum height for a picture
#define MAX_Capable_Objects 250 //Maximum amount objects possible per image, set well above expected object count
#define MAX_Conflicts 200000 //Maximum amount of conflicts, set around 15000 for a 1920 x 1080 picture containing 5 objects.
#define MAXDices 10 //Maximum amount of dices in a picture

#define Scalingfactor 1         // Images get scaled down during the process. For no scaling set it to 1, this does take a long time for 1920x1080 pictures
#define ResizeFactorSecondRun 1 // Second run the resizefactor doesnt need to be as big, because the image is cropt.

#define debugBWLabel_D 0        //Set 1 for qDebug() << Set 0 for none
#define debugBWLabel2_D 0        //Set 1 for qDebug() << Set 0 for none
#define debugHSV_D 0        //Set 1 for qDebug() << Set 0 for none
#define debugXY_D 0        //Set 1 for qDebug() << Set 0 for none

#define MinOBJCountDicesFirstrun 200 //Min amount of pixel to be recognized as an object
#define MinOBJCountDicesSecondrun 5 //Min amount of pixel to be recognized as an object

#define debugNumberplate_N 0        //Set 1 for qDebug() << Set 0 for none
#define debugNumberplate2_N 0        //Set 1 for qDebug() << Set 0 for none
#define debugHSV_N 0        //Set 1 for qDebug() << Set 0 for none
#define debugXY_N 0        //Set 1 for qDebug() << Set 0 for none

#define Export 1        //If you want to export the image
#define DROPOBJ 100     //If an object is less then 100 pixels bwlabel will not see it
#define HSV_H 1         //Translate QT HSV Values to Paint.net values
#define HSV_S 2.55      //Translate QT HSV Values to Paint.net values
#define HSV_V 2.55      //Translate QT HSV Values to Paint.net values

#define S_Border 40     //Limit set to recoqnize Dice for HSV Saturation
#define V_Border 67     //Limit set to recoqnize Dice for HSV Value

#define H_MIN_D 0        //Limit set to recognize Dices for HSV Hue (minimum)
#define H_MAX_D 360        //Limit set to recognize Dices for HSV Hue (maximum)
#define S_MIN_D 0        //Limit set to recognize Dices for HSV Saturation (minimum)
#define S_MAX_D 40       //Limit set to recognize Dices for HSV Saturation (maximum)
#define V_MIN_D 67        //Limit set to recognize Dices for HSV Value (minimum)
#define V_MAX_D 100       //Limit set to recognize Dices for HSV Value (maximum)

#define H_MIN_N 30        //Limit set to recognize Numberplate for HSV Hue (minimum)
#define H_MAX_N 60        //Limit set to recognize Numberplate for HSV Hue (maximum)
#define S_MIN_N 53        //Limit set to recognize Numberplate for HSV Saturation (minimum)
#define S_MAX_N 100       //Limit set to recognize Numberplate for HSV Saturation (maximum)
#define V_MIN_N 53        //Limit set to recognize Numberplate for HSV Value (minimum)
#define V_MAX_N 100       //Limit set to recognize Numberplate for HSV Value (maximum)
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
            if(debugHSV_N)qDebug() << h << s << v;
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

    for (out = n - 1; out > 0; out--)
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

void MainWindow::ExportImage(QImage image)
{
    if(Export)
    {
        QPixmap Imageexport;
        Imageexport.convertFromImage(image,Qt::AutoColor);
        QFile file("Export.png");
        file.open(QIODevice::WriteOnly);
        Imageexport.save(&file, "PNG");
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

    int MaxpixY = image.height();
    int MaxpixX = image.width();
    if(debugXY_D)qDebug() << MaxpixX << MaxpixY;

    SetHSV(&image,MaxpixY, MaxpixX,H_MIN_D,H_MAX_D,S_MIN_D,S_MAX_D,V_MIN_D,V_MAX_D );

    ObjectBwLabel objarray[MAX_Capable_Objects];
    int ObjAmount = 0;

    BWLabel bwlbl = BWLabel();
    bwlbl.Setdebug(debugBWLabel_D);
    bwlbl.SetImage(image);
    bwlbl.SetResizefactor(Scalingfactor);
    bwlbl.ResizeIm(&MaxpixY,&MaxpixX);
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,MinOBJCountDicesFirstrun,0);
    bwlbl.SetImages(objarray, &ObjAmount);
    QImage image1 = bwlbl.GetImage();
    bwlbl.Invert(objarray, &ObjAmount);

    QPixmap pixDobb[MAXDices];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        ObjectBwLabel objarraySecond[50];
        int ObjAmountSecond = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(ResizeFactorSecondRun);
        bwlbl.Setdebug(debugBWLabel2_D);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarraySecond,&ObjAmountSecond,MinOBJCountDicesSecondrun,1);
        bwlbl.SetImages(objarraySecond, &ObjAmountSecond);
        bwlbl.RemoveBorders(objarraySecond, &ObjAmountSecond);
        objarray[i].s = QString::number(ObjAmountSecond);
        objarray[i].image = bwlbl.GetImage();
        QImage image2 = objarray[i].image.scaled(141, 91, Qt::KeepAspectRatio);
        QPixmap imagepix;
        imagepix.convertFromImage(image2,Qt::AutoColor);
        pixDobb[i] = imagepix;
    }
    ui->output_2->setText(objarray[0].s);
    ui->output_3->setText(objarray[1].s);
    ui->output_4->setText(objarray[2].s);
    ui->output_5->setText(objarray[3].s);
    ui->output_6->setText(objarray[4].s);
    ui->output_7->setText(objarray[5].s);
    ui->photo_1->setPixmap(pixDobb[0]);
    ui->photo_2->setPixmap(pixDobb[1]);
    ui->photo_3->setPixmap(pixDobb[2]);
    ui->photo_4->setPixmap(pixDobb[3]);
    ui->photo_5->setPixmap(pixDobb[4]);
    ui->photo_6->setPixmap(pixDobb[5]);

    QImage image2 = image1.scaled(641, 411, Qt::KeepAspectRatio);
    QPixmap imagepix;
    imagepix.convertFromImage(image2,Qt::AutoColor);

    ExportImage(image2);

    ui->photo->setPixmap(imagepix);


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
    if(debugXY_N)qDebug() << MaxpixX << MaxpixY;

    SetHSV(&image,MaxpixY, MaxpixX, H_MIN_N, H_MAX_N, S_MIN_N, S_MAX_N, V_MIN_N, V_MAX_N);

    image.invertPixels();

    ObjectBwLabel objarray[MAX_Capable_Objects];
    int ObjAmount = 0;

    BWLabel bwlbl = BWLabel();
    bwlbl.Setdebug(debugNumberplate_N);
    bwlbl.SetImage(image);
    bwlbl.SetResizefactor(Scalingfactor);
    bwlbl.ResizeIm(&MaxpixY,&MaxpixX);
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,100,0);
    bwlbl.SetImages(objarray, &ObjAmount);
    bwlbl.Invert(objarray, &ObjAmount);

    QPixmap pixDobb[6];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        Numberplate NP;
        ObjectBwLabel objarrayt[50];
        int ObjAmountt = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(ResizeFactorSecondRun);
        bwlbl.Setdebug(debugNumberplate2_N);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,100,0);
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
    //hiervoor kan een aparte functie worden gemaakt!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
        else if (isalpha(outputChar[i - 1]) && isalpha(outputChar[i]) && isalpha(outputChar[i + 1]) && isalpha(outputChar[i + 2]))
        {
            outputPlate.push_back('-');
        }
        else if (isdigit(outputChar[i - 1]) && isdigit(outputChar[i]) && isdigit(outputChar[i + 1]) && isdigit(outputChar[i + 2]))
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

    image.invertPixels();
    image = image.scaled(741, 431, Qt::KeepAspectRatio);
    QPixmap pix;
    pix.convertFromImage(image);
    ui->photo->setPixmap(pix);

    ExportImage(objarray[1].image);
}
