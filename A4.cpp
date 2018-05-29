//A4
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
 QImage image( 400, 400, QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        QRgb value;
        value=qRgb(0,255,0);
        //draws a line using setPixel() function
        for(int x=0;x<400;++x)
        {
            image.setPixel(x,200,value);
        }
        for(int y=0;y<400;++y)
        {
            image.setPixel(200,y,value);
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::sign(float x)
{
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}


void MainWindow::bresenham(float x1,float y1,float x2,float y2)
{
    float dx,dy,s1,s2,inter,e,temp,x,y;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    s1=sign(x2-x1);
    s2=sign(y2-y1);
    x=x1;
    y=y1;
    if(dy>dx)
    {
        temp=dx;
        dx=dy;
        dy=temp;
        inter=1;
    }
    else
        inter=0;
     e=(2*dy)-dx;
    for(int i=0;i<dx;i++)
    {
        image.setPixel(x,y,qRgb(255,255,255));
        while(e>=0)
        {
            if(inter==1)
                x=x+s1;
            else
                y=y+s2;
            e=e-(2*dx);
        }
        if(inter==1)
        {
            y=y+s2;
        }
        else
            x=x+s1;
        e=e+(2*dy);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    int x1,y1,x2,y2;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    bresenham(x1+200,200-y1,x2+200,200-y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    int x1,y1,x2,y2,tx,ty;
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();
    tx=ui->textEdit_8->toPlainText().toInt();
    ty=ui->textEdit_9->toPlainText().toInt();
    bresenham(x1+tx+200,200-ty-y1,x2+tx+200,200-ty-y2);
 }

void MainWindow::on_pushButton_3_clicked()
{
    int m[2][2],s[2][2],t[2][2];
    m[0][0]=ui->textEdit->toPlainText().toInt();
    m[0][1]=ui->textEdit_2->toPlainText().toInt();
    m[1][0]=ui->textEdit_3->toPlainText().toInt();
    m[1][1]=ui->textEdit_4->toPlainText().toInt();
    s[0][0]=ui->textEdit_5->toPlainText().toInt();
    s[0][1]=0;
    s[1][0]=0;
    s[1][1]=ui->textEdit_6->toPlainText().toInt();
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            t[i][j]=0;
            for(int k=0;k<2;k++)
            {
                t[i][j]+=m[i][k]*s[k][j];
            }
        }
    }
    bresenham(t[0][0]+200,200-t[0][1],t[1][0]+200,200-t[1][1]);

}

void MainWindow::on_pushButton_4_clicked()
{
    int m[2][2],r[2][2],t[2][2];
    double d=ui->textEdit_7->toPlainText().toDouble();
    double deg=d*3.142/180;
    m[0][0]=ui->textEdit->toPlainText().toInt();
    m[0][1]=ui->textEdit_2->toPlainText().toInt();
    m[1][0]=ui->textEdit_3->toPlainText().toInt();
    m[1][1]=ui->textEdit_4->toPlainText().toInt();
    r[0][0]=ceil(cos(deg));
    r[0][1]=ceil(sin(deg));
    r[1][0]=-ceil(sin(deg));
    r[1][1]=ceil(cos(deg));
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            t[i][j]=0;
            for(int k=0;k<2;k++)
            {
                t[i][j]+=m[i][k]*r[k][j];
            }
        }
    }
    bresenham(t[0][0]+200,200-t[0][1],t[1][0]+200,200-t[1][1]);
}

