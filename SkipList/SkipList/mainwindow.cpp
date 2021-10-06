#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SkipListView.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QPalette>
using namespace std;

skipList<int, string> z(INT_MAX,2000,0.5);
pair<int, string> p;
int op=1;


bool isDigitStr(QString src){
    QByteArray ba = src.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;
    if (*s){ 
        return false;
    }
    else{ 
        return true;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SkipList");
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/bg.png")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//插入
{
    QString aa=ui->lineEdit->text();
    QString bb=ui->lineEdit_2->text();
    if(!isDigitStr(aa)){
        QString res="Error:Your input must be integer!!!";
        ui->label_3->setText(res);
        return;
    }
    int a= aa.toInt();
    string b=bb.toStdString();
    p.first=a;
    p.second=b;
    string c;
    QString res="Before Insert:";
    z.OutputToString(c);
    z.insert(p);
    res+=QString::fromStdString(c);
    res+="After Insert:";
    z.OutputToString(c);
    res+=QString::fromStdString(c);
    ui->label_3->setText(res);
    string note="Op ";
    AppendInt(note,op);
    note+=": Insert (";
    AppendInt(note,a);
    note+=", ";
    note+=p.second;
    note+=") ";
    z.visualition(note,op);
    QImage *img=new QImage; //新建一个image对象
    string picture="";
    AppendInt(picture,op);
    picture+=".png";
    QString filename;
    filename=QString::fromStdString(picture);
    img->load(filename); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    ui->label_5->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*im
    op++;
}


void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::on_pushButton_3_clicked()//删除指定关键字
{  

    QString aa=ui->lineEdit_3->text();
    if(!isDigitStr(aa)){
        QString res="Error:Your input must be integer!!!";
        ui->label_3->setText(res);
        return;
    }
    int a= aa.toInt();
    string c;
    QString res="Before Delete:";
    z.OutputToString(c);
    res+=QString::fromStdString(c);
    int size1=z.size();
    z.erase(a);
    int size2=z.size();
    if(size1==size2){
        QString res="Error:There is no matching node to be deleted!!!";
        ui->label_3->setText(res);
        return;
    }
    z.OutputToString(c);
    res+="After Delete:";
    res+=QString::fromStdString(c);
    ui->label_3->setText(res);
    string note="Op ";
    AppendInt(note,op);
    note+=": Delete ";
    AppendInt(note,a);
    z.visualition(note,op);
    QImage *img=new QImage; //新建一个image对象
    string picture="";
    AppendInt(picture,op);
    picture+=".png";
    QString filename;
    filename=QString::fromStdString(picture);
    img->load(filename); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    ui->label_5->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*im
    op++;
}

void MainWindow::on_pushButton_4_clicked()//删除最小
{
    int size=z.size();
    if(size==0){
        QString res="Error:The SkipList is empty!!!";
        ui->label_3->setText(res);
        return;
    }
    string c;
    QString res="Before Delete:";
    z.OutputToString(c);
    res+=QString::fromStdString(c);
    z.eraseMin();
    z.OutputToString(c);
    res+="After Delete:";
    res+=QString::fromStdString(c);
    ui->label_3->setText(res);
    string note="Op ";
    AppendInt(note,op);
    note+=": Delete MinKey";
    z.visualition(note,op);
    QImage *img=new QImage; //新建一个image对象
    string picture="";
    AppendInt(picture,op);
    picture+=".png";
    QString filename;
    filename=QString::fromStdString(picture);
    img->load(filename); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    ui->label_5->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*im
    op++;
}

void MainWindow::on_pushButton_5_clicked()//删除最大
{
    int size=z.size();
    if(size==0){
        QString res="Error:The SkipList is empty!!!";
        ui->label_3->setText(res);
        return;
    }
    string c;
    QString res="Before Delete:";
    z.OutputToString(c);
    res+=QString::fromStdString(c);
    z.eraseMax();
    z.OutputToString(c);
    res+="After Delete:";
    res+=QString::fromStdString(c);
    ui->label_3->setText(res);
    string note="Op ";
    AppendInt(note,op);
    note+=": Delete MaxKey";
    z.visualition(note,op);
    QImage *img=new QImage; //新建一个image对象
    string picture="";
    AppendInt(picture,op);
    picture+=".png";
    QString filename;
    filename=QString::fromStdString(picture);
    img->load(filename); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    ui->label_5->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*im
    op++;
}

void MainWindow::on_pushButton_6_clicked()//查找
{
    QString aa=ui->lineEdit_4->text();
    if(!isDigitStr(aa)){
        QString res="Error:Your input must be integer!!!";
        ui->label_3->setText(res);
        return;
    }
    else{
        int a= aa.toInt();
        string pp=z.find(a);
        if(pp=="Error"){
            ui->label_3->setText("There is no matching element");
        }
        else{
            QString res="The Element that you are finding is:";
            string note=" (";
            AppendInt(note,a);
            note+=", ";
            note+=pp;
            note+=")";
            res+=QString::fromStdString(note);
            ui->label_3->setText(res);
        }
    }
}
