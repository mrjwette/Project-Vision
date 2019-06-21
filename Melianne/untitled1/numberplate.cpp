#include "numberplate.h"

Numberplate::Numberplate()
{

}

//this is the main function of the number plate assignment
void Numberplate::init(QImage *image2)
{


    /*
    QPixmap pixNum[8];

    for(int i = 0 ;i<ObjAmount;i++)
        {
            objarray[i].image.invertPixels();
            ObjectBwLabel objarrayt[50];
            ObjectBwLabel firstt;
            objarrayt[0] = firstt;
            int ObjAmountt = 0;
            BWlab.SetImage(objarray[i].image);
            BWlab.SetResizefactor(1);
            BWlab.Setdebug(0);
            BWlab.BWLabel_RegionProps(objarray[i].imheight,objarray[i].imwidth,objarrayt,&ObjAmountt,5);
            objarray[i].s = QString::number(ObjAmountt);
            objarray[i].image = BWlab.GetImage();
            QImage image2 = objarray[i].image.scaled(301, 201, Qt::KeepAspectRatio);
            QPixmap imagepix;
            imagepix.convertFromImage(image2,Qt::AutoColor);
            pixNum[i] = imagepix;
        }


    loadMasks(image2->height());                                                                    //load all the masks and resize them to the height of the number plate
    for(int i = 0; i < 8; i++)
    {
        QImage photo(pixNum[i].toImage().convertToFormat(QImage::Format_Mono));
        int index = compareWithMasks(&photo);                                                       //compare the masks with the cropped image
        output[i] = maskerChar[index];                                                              //fill the output array with the charachter that has the highest similarity
    }
    */

}

//The masks are loaded according to the given height of the photo
//This way the masks will fit perfectly over the number plate
void Numberplate::loadMasks(int hoogte)
{
    maskers[0] = QPixmap("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\A.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[1] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\B.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[2] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\C.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[3] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\D.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[4] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\E.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[5] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\F.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[6] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\G.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[7] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\H.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[8] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\J.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[9] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\K.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[10] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\L.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[11] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\M.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[12] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\N.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[13] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\O.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[14] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\P.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[15] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Q.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[16] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\R.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[17] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\S.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[18] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\T.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[19] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\U.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[20] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\V.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[21] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\W.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[22] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\X.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[23] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Y.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[24] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Z.png").scaledToHeight(hoogte, Qt::SmoothTransformation);

    maskers[25] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\0.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[26] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\1.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[27] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\2.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[28] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\3.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[29] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\4.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[30] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\5.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[31] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\6.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[32] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\7.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[33] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\8.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
    maskers[34] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\9.png").scaledToHeight(hoogte, Qt::SmoothTransformation);

    maskers[35] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\-.png").scaledToHeight(hoogte, Qt::SmoothTransformation);
}

//This function compares the given image to all the available characters
int Numberplate::compareWithMasks(QImage *image)
{
    double highestPercentage = 0;
    int indexHighestPerc = 0;
    double countCorrectPixels = 0;

    for(int i = 0; i < 36; i++)                                                             //go through all the masks
    {
        qDebug() << maskerChar[i];

        QImage masks(maskers[i].toImage().convertToFormat(QImage::Format_Mono));
        *image = image->scaled(masks.width(), masks.height());                              //scale the image to the size of the mask

        for(int j = 0; j < image->height(); j++)                                            //go through the image to check how many pixels are the same as the masks
        {
            for(int k = 0; k < image->width(); k++)
            {
                QColor pixelMask = masks.pixel(k, j);
                QColor pixelFoto = image->pixel(k, j);
                if(pixelMask == pixelFoto)
                {
                    countCorrectPixels++;
                }
            }
        }
        double percentage = (countCorrectPixels/(image->height()*image->width()))*100.f;    //convert the correct amount of pixels to a percentage
        qDebug() << "Correct aantal pixels :" << percentage;
        qDebug() << "Hoogste corr aantal pixels: " << highestPercentage;
        if(percentage > highestPercentage)
        {                                                                                   //if the new percentage is higher than the highest percentage
            highestPercentage = percentage;                                                 //change the highest percentage to the new percentage
            indexHighestPerc = i;                                                           //set the index of the highest percentage to the index of the new highest percentage
        }
        qDebug() << "Nieuwe hoogste: " << highestPercentage;
        qDebug() << " ";
        countCorrectPixels = 0;                                                             //reset correct amount of pixels
    }
    return indexHighestPerc;
}

//returns the output of the numberplate in a QString
QString Numberplate::getOutput()
{
    QString text = output;                                                                  //change the char array output[] to a QString
    return text;                                                                            //return the QString that contains all the chars of output[]
}

void Numberplate::setPixmap(QPixmap pix)
{
    this->pixmap = pix;
}

QPixmap Numberplate::getPixmap()
{
    return pixmap;
}
