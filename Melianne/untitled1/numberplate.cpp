#include "numberplate.h"

Numberplate::Numberplate()
{

}

void Numberplate::init()
{
    QString filename = QFileDialog::getOpenFileName
    (
                this, "Open Document",QDir::currentPath(), "All files (*.*)"                            //opens a window where you can select a file
    );

    QImage image2(filename);

    int h_min = H_MIN, h_max = H_MAX;
    int s_min = S_MIN, s_max = S_MAX;
    int v_min = V_MIN, v_max = V_MAX;
    int x_max = 0, x_min = 0, y_max = 0, y_min = 0;

    SetHSV(&image2, image2.height(), image2.width(), h_min, h_max, s_min, s_max, v_min, v_max, &x_min, &y_min, &x_max, &y_max);

    image2 = image2.convertToFormat(QImage::Format_MonoLSB);
    QRect rect(x_min, y_min,(x_max - x_min), (y_max - y_min));
    image2 = image2.copy(rect);
    QPixmap imagepix;
    imagepix.convertFromImage(image2,Qt::AutoColor);
    ui->photo->setPixmap(imagepix);
}

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

int Numberplate::compareWithMasks(QImage image)
{

    double highestPercentage = 0;
    int indexHighestPerc = 0;
    double countCorrectPixels = 0;

    for(int i = 0; i < 36; i++)
    {
        qDebug() << maskerChar[i];

        QImage masks(maskers[i].toImage().convertToFormat(QImage::Format_Mono));
        image = image.scaled(masks.width(), masks.height());

        for(int j = 0; j < image.height(); j++)
        {
            for(int k = 0; k < image.width(); k++)
            {
                QColor pixelMask = masks.pixel(k, j);
                QColor pixelFoto = image.pixel(k, j);
                if(pixelMask == pixelFoto)
                {
                    countCorrectPixels++;
                }
            }
        }
        double percentage = (countCorrectPixels/(image.height()*image.width()))*100.f;
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
