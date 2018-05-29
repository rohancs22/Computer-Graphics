//COHEN B3
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
QImage image(400,400,QImage::Format_RGB888);
int A=8,B=4,R=2,L=1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xmin=100,ymin=100,xmax=300,ymax=300;
    dda(100,100,300,100);
    dda(300,100,300,300);
    dda(300,300,100,300);
    dda(100,300,100,100);
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
}
    else
        return 0;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(k==0)
    {
        a1=event->x();
        b1=event->y();
        k++;
    }
    else
    {
        a2=event->x();
        b2=event->y();
        cohen(a1,b1,a2,b2);
        k--;
    }
}
int MainWindow::outcode(int x, int y)
{
    int code=0;

    if(y<ymin)
    {
        code|=A;
    }
    else if(y>ymax)
    {
        code|=B;
    }
    else if(x>xmax)
    {
        code|=R;
    }
    else if(x<xmin)
    {
        code|=L;
    }
    return code;
}

void MainWindow::cohen(int x1, int y1, int x2, int y2)
{
    int code1=outcode(x1,y1);
    int code2=outcode(x2,y2);

    if((code1==0) && (code2==0))
    {
        ui->label_2->setText("full visi");
        dda(x1,y1,x2,y2);
        return;
    }
    else if((code1 & code2)!=0 )
    {
        ui->label_2->setText("In visi");
        return;
    }
    else
    {
        if(code1!=0)
        {
            if(code1 & A)
            {
                x1=x1+(x2-x1)*(ymin-y1)/(y2-y1);
                y1=ymin;
            }
            else if (code1 & B)
            {
                x1=x1+(x2-x1)*(ymax-y1)/(y2-y1);
                y1=ymax;
            }
            else if(code1 & R)
            {
                x1=xmax;
                y1=y1+(y2-y1)*(xmax-x1)/(x2-x1);
            }
            else if(code1 & L)
            {
                x1=xmin;
                y1=y1+(y2-y1)*(xmin-x1)/(x2-x1);
            }
        }

        if(code2!=0)
        {
            if(code2 & A)
            {
                x2=x2+(x1-x2)*(ymin-y2)/(y1-y2);
                y2=ymin;
            }
            else if (code2 & B)
            {
                x2=x2+(x1-x2)*(ymax-y2)/(y1-y2);
                y2=ymax;
            }
            else if(code2 & R)
            {
                x2=xmax;
                y2=y2+(y1-y2)*(xmax-x2)/(x1-x2);
            }
            else if(code2 & L)
            {
                x2=xmin;
                y2=y2+(y1-y2)*(xmin-x2)/(x1-x2);
            }
        }
        ui->label_2->setText("partu visi");
        dda(x1,y1,x2,y2);
        return;


    }
}
