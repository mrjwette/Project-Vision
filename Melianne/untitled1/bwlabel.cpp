#include "bwlabel.h"

BWLabel::BWLabel()
{

}
//Return image held by BWLabel
QImage BWLabel::GetImage()
{
    return this->image;
}
//Set the image for BWLabel to process
void BWLabel::SetImage(QImage temp)
{
    this->image = temp;
}
//Set the color in the picarray, picarray is a 2D dynamic pointer array.
void BWLabel::picarraysetC(int x,int y,QRgb C)
{
    this->image.setPixel(x,y,C);
}
//Get the color in picarray, picarray is a 2D dynamic pointer array.
QRgb BWLabel::picarraygetC(int x,int y)
{
    QColor temp = this->image.pixel(x,y);
    QRgb temp2 = qRgb(temp.red(),temp.green(),temp.blue());
    return temp2;
}
//Resize the picture.
void BWLabel::ResizeIm(int * MaxpixY, int * MaxpixX)
{
    int width = 0;
    int height = 0;
    QImage smallerimage = QPixmap(*MaxpixX/this->ResizeFactor, *MaxpixY/this->ResizeFactor).toImage();
    for (int y = 0;y<*MaxpixY;y = y + this->ResizeFactor) {
        for (int x = 0;x<*MaxpixX;x = x +this->ResizeFactor) {
            if(this->image.pixel(x,y) == this->WHITE)
            {
                smallerimage.setPixel(width,height,this->WHITE);
            }
            else if(this->image.pixel(x,y) == this->BLACK)
            {
                smallerimage.setPixel(width,height,this->BLACK);
            }
            width++;

        }
        width = 0;
        height++;
    }
    height = 0;
    image = smallerimage;
    *MaxpixX = *MaxpixX/this->ResizeFactor;
    *MaxpixY = *MaxpixY/this->ResizeFactor;
}
//Set the resize factor for resizing.
void BWLabel::SetResizefactor(int resize)
{
    this->ResizeFactor = resize;
}
//If you want to debug set this to true. The function will print the actions in the console.
void BWLabel::Setdebug(bool Bbool)
{
    this->debug = Bbool;
}
//If you want to adjust the starting point of the Labelcounter, you can use this function.
void BWLabel::AdjustCC(int t)
{
    this->CCstart = t;
}
//For debugprinting, prints the current image in picarray
void BWLabel::DebugPicarray(bool debug, int MaxpixY, int MaxpixX, int** picarray)
{
    if(debug){
        qDebug() << "";
        for(int y = 0; y < MaxpixY; y++){
            QDebug deb = qDebug();
            deb << "Row: ";
            for(int x = 0; x < MaxpixX; x++){
                deb << picarray[x][y];
            }
        }
    }
}
//For debugprinting, prints Labelcounter with blockcounter
void BWLabel::DebugLCBC(bool debug, int ObjAmount, ObjectBwLabel * objarray)
{
    if(debug)
    {
        for(int i = 1;i<ObjAmount;i++)
        {
            qDebug() << "LC: " << objarray[i].Labelcounter<< "BC: " << objarray[i].BlockCount;
        }
    }
}
//BWLabel and regionprops, insert and image with objects as white pixels.
//It will return a list of objects it finds, these objects contain the x and y of each object.
//Smallesobj is the smallest object wanted, for example if this is 100, any object within the picture smaller then 100 pixels will not be returned.
void BWLabel::BWLabel_RegionProps(int MaxpixY, int MaxpixX, ObjectBwLabel * objarray, int * retObjAmount, int SmallesObj, int resetFirstRow)
{

    int** picarray = new int*[MaxpixX+5];
    for(int i = 0;i<MaxpixX+5;i++)
    {
        picarray[i] = new int[MaxpixY+5];
    }

    int CC = this->CCstart;
    auto conflicts = new int[MAX_Conflicts][2];
    int conflictCounter = 0;
    for(int y = 0; y < MaxpixY; y++)
    {
        for(int x = 0; x < MaxpixX; x++)
        {
            if(this->image.pixel(x,y) == this->WHITE)
            {
                //qDebug() << "Black" << x << y;
                picarray[x][y] = 1;
            }
            else {
                //qDebug() << "White" << x << y;
                picarray[x][y] = 0;
            }
        }
    }
    if(resetFirstRow == 1)
    {
        for(int i = 0;i<MaxpixX;i++)
        {
            picarray[i][0] = 0;
        }
        for(int i = 0;i<MaxpixY;i++)
        {
            picarray[0][i] = 0;
        }
    }

    DebugPicarray(this->debug, MaxpixY,MaxpixX,picarray);



    //BWLabel itself, will mark everything in the image. No conflicts fixed yet.
    for(int y = 1; y < MaxpixY; y++)
    {
        for(int x = 1; x < MaxpixX ; x++)
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
                //Mark all conflicts in a conflicts array. These will be fixed later on
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
    }

    DebugPicarray(this->debug, MaxpixY,MaxpixX,picarray);

    //Fix conflicts
    int temp = 0;
    for(int i = 0; i < conflictCounter; i++){
        if(conflicts[i][0] < conflicts[i][1]){
            temp = conflicts[i][0];
            conflicts[i][0] = conflicts[i][1];
            conflicts[i][1] = temp;
        }
    }

    for(int i = 0; i < conflictCounter; i++){
        for(int y = 1; y < MaxpixY; y++){
            for(int X = 1; X < MaxpixX; X++){
                if(picarray[X][y] == conflicts[i][0])
                {
                    picarray[X][y] = conflicts[i][1];
                }

            }
        }
    }

    DebugPicarray(this->debug, MaxpixY,MaxpixX,picarray);

    //Count objects in the image. Stored in vector for easy pushing
    QVector<int> Objects;
    QVector<int>::iterator IT;
    for(int y = 0; y < MaxpixY; y++){
        for(int x = 0; x < MaxpixX; x++){
            IT = std::find(Objects.begin(),Objects.end(),picarray[x][y]);
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
        if(this->debug)qDebug() << temp.Labelcounter;
        objarray[i] = temp;
    }

    //Count the amount of pixels per object.
    //qDebug() << Objects;
    for(int y = 0; y < MaxpixY; y++){
        for(int x = 0; x < MaxpixX; x++){
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

    //Return the Labelcounter and amount of blocks in debug
     DebugLCBC(this->debug, ObjAmount,objarray);

    //If the blockamount of a certain object is below the set threshold it will be removed from the list.
    for(int i = 0;i<ObjAmount;i++)
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
    DebugLCBC(this->debug, ObjAmount,objarray);

    //per object checking each pixel to find the most Left, Right, Up and down pixel. These are stored in the object.
    for(int o = 0;o<ObjAmount;o++)
    {
        for(int y = 0; y < MaxpixY; y++){
            for(int x = 0; x < MaxpixX; x++){
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

                    if(x > objarray[o].R){
                        objarray[o].R = x;
                    }
                    if(x < objarray[o].L){
                        objarray[o].L = x;
                    }
                    if(y < objarray[o].U){
                        objarray[o].U = y;
                    }
                    if(y > objarray[o].D){
                        objarray[o].D = y;
                    }
                }
            }
        }
        //Mark the object in the image for visual confirmation.
        image.setPixel(objarray[o].R,objarray[o].U,RED);
        image.setPixel(objarray[o].R,objarray[o].D,RED);
        image.setPixel(objarray[o].L,objarray[o].U,RED);
        image.setPixel(objarray[o].L,objarray[o].D,RED);
    }


    *retObjAmount = ObjAmount;


    delete[] picarray;

}
//This will extract the images from the main image and dump them into the QImage of each object.
//count is the amount of objects inside the list. This will not be adjusted.
void BWLabel::SetImages(ObjectBwLabel * objarray, int * count)
{
    int C = *count;
    for (int i = 0;i<C; i++) {
        objarray[i].image = QPixmap(objarray[i].R - objarray[i].L,objarray[i].D - objarray[i].U).toImage();

        int height = 0;
        int width = 0;
        for(int y = objarray[i].U;y<objarray[i].D;y++)
        {
            for(int x = objarray[i].L;x <objarray[i].R;x++)
            {
                objarray[i].image.setPixel(width,height,this->image.pixel(x,y));
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
//This will invert the images and then clear the border.
void BWLabel::Invert(ObjectBwLabel * objarray, int * count)
{
    QRgb BLACK = qRgb(0,0,0);
    QRgb WHITE = qRgb(255,255,255);
    QRgb RED = qRgb(255,0,0);
    int C = *count;
    for(int i = 0 ;i<C;i++)
    {
        if(this->debug)qDebug() << objarray[i].imheight << objarray[i].imwidth;
        for (int y = 0;y<objarray[i].imheight;y++) {
            for (int x = 0;x<objarray[i].imwidth;x++) {
                if(objarray[i].image.pixel(x,y) == RED)
                {
                    objarray[i].image.setPixel(x,y,BLACK);
                }
                if(objarray[i].image.pixel(x,y) == WHITE)
                {
                    objarray[i].image.setPixel(x,y,BLACK);
                }
                else {
                    objarray[i].image.setPixel(x,y,WHITE);
                }
            }
        }
    }

}
//Removes objectes located on the border.
void BWLabel::RemoveBorders(ObjectBwLabel * objarray, int * count)
{
    int C = *count;
    for (int i = 0;i<C; i++) {
        if(this->debug)qDebug() << objarray[i].D << this->image.height();
        if(objarray[i].D == this->image.height() - 1)
        {
            for(int p = i;p<C-1;p++)
            {
                objarray[p] = objarray[p+1];
            }
            C--;
            i--;

        }
        else if(objarray[i].U == 1)
        {
            for(int p = i;p<C-1;p++)
            {
                objarray[p] = objarray[p+1];
            }
            C--;
            i--;
        }
        else if(objarray[i].L == 1)
        {
            for(int p = i;p<C-1;p++)
            {
                objarray[p] = objarray[p+1];
            }
            C--;
            i--;
        }
        else if(objarray[i].R == this->image.width())
        {
            for(int p = i;p<C-1;p++)
            {
                objarray[p] = objarray[p+1];
            }
            C--;
            i--;
        }

    }
    *count = C;
    if(this->debug)qDebug() << C;
}


