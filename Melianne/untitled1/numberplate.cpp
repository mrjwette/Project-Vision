#include "numberplate.h"

Numberplate::Numberplate()
{

}

//changes the all the pixels that are within the HSV range to white
//all the other pixels will be changed to black


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
void Numberplate::loadMasks(int hoogte, int breedte)
{
    maskers[0] = QPixmap("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\A.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[1] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\B.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[2] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\C.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[3] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\D.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[4] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\E.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[5] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\F.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[6] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\G.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[7] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\H.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[8] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\J.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[9] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\K.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[10] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\L.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[11] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\M.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[12] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\N.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[13] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\O.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[14] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\P.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[15] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Q.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[16] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\R.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[17] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\S.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[18] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\T.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[19] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\U.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[20] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\V.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[21] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\W.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[22] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\X.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[23] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Y.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);;
    maskers[24] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\Z.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);

    maskers[25] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\0.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[26] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\1.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[27] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\2.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[28] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\3.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[29] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\4.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[30] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\5.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[31] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\6.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[32] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\7.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[33] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\8.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
    maskers[34] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\9.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);

    maskers[35] = QPixmap ("C:\\Users\\2125228\\Documents\\MATLAB\\Foto\\Project\\Masks\\-.png").scaled(hoogte, breedte, Qt::KeepAspectRatio);
}

//This function compares the given image to all the available characters
int Numberplate::compareWithMasks(QImage *image)
{
    double highestPercentage = 0;
        int indexHighestPerc = 0;
        double countCorrectPixels = 0;

        for(int i = 0; i < 36; i++)
        {
            qDebug() << maskerChar[i];
            QImage masks(maskers[i].toImage().convertToFormat(QImage::Format_Mono));
            masks = masks.scaled(image->width(), image->height());

            for(int j = 0; j < image->height(); j++)
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
            double percentage = (countCorrectPixels/(image->height()*image->width()))*100.f;
            qDebug() << "Correct aantal pixels :" << percentage;
            qDebug() << "Hoogste corr aantal pixels: " << highestPercentage;
            if(percentage > highestPercentage)
            {
                highestPercentage = percentage;
                indexHighestPerc = i;
            }
            qDebug() << "Nieuwe hoogste: " << highestPercentage;
            qDebug() << " ";
            countCorrectPixels = 0;
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
