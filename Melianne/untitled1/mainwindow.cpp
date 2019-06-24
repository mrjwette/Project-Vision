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

#define resize 0        //If you want to downscale images to smaller images for faster processing
//When resize is set to 0, set scalingfactor to 1
#define Scalingfactor 1         // Images get scaled down during the process. This is how much
#define OFFSETPICADJUST 0 // When using images that do not resize well, increase this.
#define OffsetBWLabel 2

#define debugI 0        //Set 1 for qDebug() << Set 0 for none
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

void MainWindow::sortOutput()
{
    qDebug() << "Voor Sorteren: ";
    for(int i = 0; i < 6; i++)
    {
        qDebug() << outputInt[i] << outputChar[i];
    }

    qDebug();

    int out, in;

    for (out = 6 - 1; out > 1; out--)
    {
        for (in = 0; in < out; in++)
        {
            if (outputInt[in] > outputInt[in + 1])
            {
                int temp = outputInt[in];
                char temp2 = outputChar[in];

                outputInt[in] = outputInt[in+1];
                outputChar[in] = outputChar[in+1];

                outputInt[in+1] = temp;
                outputChar[in+1] = temp2;
            }
        }
    }

    qDebug();
    qDebug() << "Na sorteren: ";
    for(int i = 0; i < 6; i++)
    {
        qDebug() << outputInt [i] << outputChar[i];
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
    bwlbl.BWLabel_RegionProps(MaxpixY,MaxpixX, objarray, &ObjAmount,125);
    bwlbl.SetImages(objarray, &ObjAmount);
    QImage image1 = bwlbl.GetImage();
    bwlbl.Removeborder(objarray, &ObjAmount);
    qDebug() << ObjAmount;



    QPixmap pixDobb[6];
    for(int i = 0 ;i<ObjAmount;i++)
    {
        Numberplate NP;
        ObjectBwLabel objarrayt[50];
        int ObjAmountt = 0;
        bwlbl.SetImage(objarray[i].image);
        bwlbl.SetResizefactor(1);
        bwlbl.Setdebug(1);
        bwlbl.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,20);
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
        ui->photo_1->setPixmap(imagepix);
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

    //ui->output->setText(objarray[0].s);
    //ui->output_2->setText(objarray[1].s);
    //ui->output_3->setText(objarray[2].s);

    QPixmap img1;
    img1.convertFromImage(image1, Qt::AutoColor);

    ui->photo_1->setPixmap(pixDobb[0]);
    ui->photo_2->setPixmap(pixDobb[1]);
    ui->photo_3->setPixmap(pixDobb[2]);
    ui->photo_4->setPixmap(pixDobb[3]);
    ui->photo_5->setPixmap(pixDobb[4]);
    ui->photo_6->setPixmap(pixDobb[5]);
    ui->photo_7->setPixmap(pixDobb[6]);
    ui->photo_8->setPixmap(pixDobb[7]);


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
