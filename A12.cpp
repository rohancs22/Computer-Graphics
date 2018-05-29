//A1
#include "pixel.h"
#include "ui_pixel.h"
#include <QtGui>
QImage image(300,300, QImage::Format_RGB888);
Pixel::Pixel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pixel)
{
    ui->setupUi(this);
}
Pixel::~Pixel()
{
    delete ui;
}

void Pixel::assign()
{
    x=ui->textEdit->toPlainText().toDouble();
    y=ui->textEdit_2->toPlainText().toDouble();
    len=ui->textEdit_3->toPlainText().toDouble();
    heig=ui->textEdit_4->toPlainText().toDouble();
}

int Pixel::sign(double n)
{
    if(n>0)
    {
        return 1;
    }
    if(n<0)
    {
        return -1;
    }
    else
        return 0;
}

void Pixel::dda(double x1, double y1,double x2, double y2 )
{
    double dx,dy;
    int L;
    int i=0;

    if(abs(x2-x1)>abs(y2-y1))
    {
        L=abs(x2-x1);
    }
    else
    {
        L=abs(y2-y1);
    }
    dx= (x2-x1)/L;
    dy=(y2-y1)/L;
    double x=x1+ (0.5*sign(dx));
    double y=y1+ (0.5*sign(dy));
    while(i<L)
    {
        image.setPixel(x,y,qRgb(255,0,0));
        x=x+dx;
        y=y+dy;

        i++;
    }
     ui->label_3->setPixmap(QPixmap::fromImage(image));
}


void Pixel::bresenham(double x1, double y1, double x2, double y2)
{

            double dx,dy,e;
            double x,y;
            int inter,i=0;
            int s1,s2;
             x=x1;
             y=y1;
         dx=abs(x2-x1);
         dy=abs(y2-y1);
         s1=sign(x2-x1);
         s2=sign(y2-y1);
         if(dx<dy)
         {
             int temp=dx;
             dx=dy;
             dy=temp;
             inter=1;
         }
         else
         {
             inter=0;
         }
             e=(2*dy)-dx;
             for(i=0;i<dx;i++)
             {
                 image.setPixel(x,y,qRgb(255,0,0));
                 while(e>=0)
                 {
                     if(inter==1)
                     {
                         x=x+s1;
                     }
                     else
                     {
                         y=y+s2;
                     }
                     e=e-(2*dx);
                 }
                 if(inter==1)
                 {
                     y=y+s2;
                 }
                 else
                 {
                     x=x+s1;
                 }
                 e=e+(2*dy);
             }
             ui->label_3->setPixmap(QPixmap::fromImage(image));
}

void Pixel::on_pushButton_2_clicked()//Two rectangles
{
    x=ui->textEdit->toPlainText().toDouble();
    y=ui->textEdit_2->toPlainText().toDouble();
    len=ui->textEdit_3->toPlainText().toDouble();
    heig=ui->textEdit_4->toPlainText().toDouble();

    //Outer Rectangle
    bresenham(x,y,(len+x),y);
    bresenham((len+x),y,(len+x),(heig+y));
    bresenham(x,(y+heig),(x+len),(y+heig));
    bresenham(x,y,x,(y+heig));

    //Iner Rectangle
    double xa,xb,ya,yb;
    xa= ((4*x)+len)/4;
    ya=((4*y)+heig)/4;
    xb=((4*x)+(3*len))/4;
    yb=((4*y)+(3*heig))/4;

    bresenham(xa,ya,xb,ya);
    bresenham(xb,ya,xb,yb);
    bresenham(xb,yb,xa,yb);
    bresenham(xa,ya,xa,yb);

}

void Pixel::on_pushButton_clicked()
{
    x=ui->textEdit->toPlainText().toDouble();
    y=ui->textEdit_2->toPlainText().toDouble();
    len=ui->textEdit_3->toPlainText().toDouble();
    heig=ui->textEdit_4->toPlainText().toDouble();

    double xa=((2*x)+len)/2;
    double yb=((2*y)+heig)/2;

    //Diamond
    dda(x,yb,xa,y);
    dda(xa,y,(x+len),yb);
    dda((x+len),yb,xa,(y+heig));
    dda(xa,(y+heig),x,yb);
}
