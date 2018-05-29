//SEED FILL WITH MOUSE B2
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"
QImage image(400,400,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(double x1, double y1, double x2, double y2)
{
    float dx,dy,steps,xinc,yinc,x,y;
    dx=x2-x1;
    dy=y2-y1;
    if(abs(dx)>=abs(dy))
    {
        steps=abs(dx);
    }
    else
        steps=abs(dy);
    x=x1;
    y=y1;
    xinc=dx/steps;
    yinc=dy/steps;

    for(int i=0;i<steps;i++)
    {
        image.setPixel(floor(x),floor(y),qRgb(255,255,255));
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

}
int MainWindow::sign(double u)
{
    if(u<0)
        return -1;
    if(u>0)
        return 1;
    else
        return 0;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x,y;
        if(k!=999)
        {
            if(event->button()==Qt::LeftButton)
            {
                    if(k==0)
                    {
                        a1=event->x();
                        b1=event->y();
                        k++;
                        a3=a1;
                        b3=b1;
                    }
                    else
                    {
                        a2=event->x();
                        b2=event->y();
                        dda(a1,b1,a2,b2);
                        a1=a2;
                        b1=b2;
                    }
            }
            else if(event->button()==Qt::RightButton)
            {
                    dda(a2,b2,a3,b3);
                    k=999;
            }
        }
        else
        {
           x=event->x();
           y=event->y();
           seedfill(x,y,qRgb(255,0,0),qRgb(255,255,255));
           ui->label->setPixmap(QPixmap::fromImage(image));
        }
}


void MainWindow:: seedfill(int x,int y,int f_color,int b_color)
{

   QRgb val=image.pixel(QPoint(x,y));

    if(val!=b_color && val!=f_color)
    {
        image.setPixel(x,y,f_color);
        seedfill(x+1,y,f_color,b_color);
        seedfill(x,y+1,f_color,b_color);
        seedfill(x-1,y,f_color,b_color);
        seedfill(x,y-1,f_color,b_color);
    }
}

