#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SplayTree.h"
#include <bits/stdc++.h>
#include <QMessageBox>
#include <QString>
#include <windows.h>
#include <QFileDialog>
using namespace std;

SplayTree<int> test;
Solve rnk;
vector<SplayTreeNode<int>*> roots;
string filepath;

//判断输入是否为数字
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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    close();
}

//Insert
void MainWindow::on_pushButton_7_clicked()
{
    QString aa=ui->lineEdit->text();
    if(!isDigitStr(aa)){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Please input integer !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    int a= aa.toInt();
    test.InsertNode(a);
    test.Visualization();
    ui->label_10->setText("Successfully Insert the Node!\n");
    QPixmap fitpixmap;
    fitpixmap.load("SplayTree.png");
    fitpixmap=fitpixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(fitpixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->show();
}

//Search
void MainWindow::on_pushButton_2_clicked()
{
    QString aa=ui->lineEdit->text();
    if(!isDigitStr(aa)){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Please input integer !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    int a= aa.toInt();
    SplayTreeNode<int>* t=test.SearchNode(a);
    test.Visualization();

    QPixmap fitpixmap;
    fitpixmap.load("SplayTree.png");
    fitpixmap=fitpixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(fitpixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->show();

    QString res="";
    if(t->element==a){
        res+="Successfully find the node ";
        res+=aa;
        res+=" and the count is ";
        res+=QString::number(t->count);
        res+=".\n ";
        ui->label_10->setText(res);
    }
    else{
        res+="Error:The node ";
        res+=aa;
        res+=" dos not exist!!";
        QMessageBox message(QMessageBox::NoIcon, "Error", res);
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        ui->label_10->setText(res);
    }


}


//Delete
void MainWindow::on_pushButton_3_clicked()
{
    QString aa=ui->lineEdit->text();
    if(!isDigitStr(aa)){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Please input integer !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    int a= aa.toInt();
    bool flag=test.EraseNode(a);
    test.Visualization();

    QPixmap fitpixmap;
    fitpixmap.load("SplayTree.png");
    fitpixmap=fitpixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(fitpixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->show();

    QString res="";
    if(flag){
        res+="Successfully delete the node!";
        ui->label_10->setText(res);
    }
    else{
        res+="Error:The node ";
        res+=aa;
        res+=" dos not exist!!";
        QMessageBox message(QMessageBox::NoIcon, "Error", res);
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        ui->label_10->setText(res);
    }
}

//Split
void MainWindow::on_pushButton_6_clicked()
{
    QString aa=ui->lineEdit->text();
    if(!isDigitStr(aa)){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Please input integer !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    int a= aa.toInt();
    roots=test.SplitTree(a);
    test.Visualization(roots);
    QString res="";
    res+="Successfully Split the Tree by ";
    res+=aa;
    res+="!\n";
    ui->label_10->setText(res);
    QPixmap fitpixmap;
    fitpixmap.load("SplayTree.png");
    fitpixmap=fitpixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(fitpixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->show();
}

//Merge
void MainWindow::on_pushButton_5_clicked()
{
    test.MergeTree(roots);
    test.Visualization();
    ui->label_10->setText("Successfully merge the tree!\n");
    QPixmap fitpixmap;
    fitpixmap.load("SplayTree.png");
    fitpixmap=fitpixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_2->setPixmap(fitpixmap);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->show();
}

//Words Solve
void MainWindow::on_pushButton_9_clicked()
{
     rnk.~Solve();
    //QString qstr=ui->lineEdit_2->text();
    QString kk=ui->lineEdit_3->text();
    if(!isDigitStr(kk)){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   The input K must be integer !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    int k= kk.toInt();

    rnk.Preprocessing(filepath);
    int inf=1e9;
    if(kk=="")
         k=inf;

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nBeginTime);//开始计时
    rnk.StatisticsSolve(k);

    QueryPerformanceCounter(&nEndTime);//停止计时
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout<<"运行时间："<<time*1000<<"ms"<<endl;

    QString res="Successfully Done! The all result is in output_1.txt\n";
    res+="Successfully Sorted! The top K result is in output_2.txt\n";
    res+="Total time: ";
    res+=QString::number(time*1000, 'f', 4);
    res+="ms\n";
    ui->label_10->setText(res);
}

//Search Word
void MainWindow::on_pushButton_10_clicked()
{
    QString aa=ui->lineEdit_4->text();
    string s=aa.toStdString();
    int k=rnk.SearchWord(s);
    if(k==-1){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   The word does not exist !!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    else{
        QString res="Successfull find the word, ans the pair is:( ";
        res+=aa;
        res+=", ";
        res+=QString::number(k);
        res+=").";
        ui->label_10->setText(res);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("选择输入文件"),
                                                        "F:",
                                                        tr("文件类型(*.txt)"));
    if (fileName=="") return;
    ui->label_15->setText(fileName);

    filepath = fileName.toStdString();
}
