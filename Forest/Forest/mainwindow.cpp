#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ForestAndBTree.h"
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

Forest a;
linkedBinaryTree b;
bool FLAGA=false;
bool FLAGB=false;

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

//ui窗口类
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Forest&BinaryTree");
    ui->RootEdit->setPlaceholderText("Root");
    ui->FatherL->setPlaceholderText("Father");
    ui->LChild->setPlaceholderText("Child");
    ui->FatherR->setPlaceholderText("Father");
    ui->RChild->setPlaceholderText("Child");
    ui->FatherInsert->setPlaceholderText("Father(-1->root)");
    ui->ChildInsert->setPlaceholderText("Child");
    ui->FatherDelete->setPlaceholderText("Father(-1->root)");
    ui->ChildDelete->setPlaceholderText("Child");
    ui->Root1->setPlaceholderText("Root1");
    ui->Root2->setPlaceholderText("Root1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//二叉树更改根结点
void MainWindow::on_pushButton_clicked()
{
    QString aa=ui->RootEdit->text();
    if(!isDigitStr(aa)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    if(FLAGA&&!FLAGB){
        QString res="Error:The Binary Tree has been changed to Forest!!!";
        ui->label->setText(res);
        return;
    }
    FLAGB=true;
    int a= aa.toInt();
    binaryTreeNode *t=new binaryTreeNode(a);
    b.ChangeRoot(t);
    QString res="Successfully insert the root!!";
    ui->label->setText(res);
}
//二叉树与森林可视化
void MainWindow::on_BTreeShow_clicked()
{
    if(FLAGB){
        b.Visualition();
        QImage *img=new QImage;
        string picture="binarytree.png";
        QString filename;
        filename=QString::fromStdString(picture);
        img->load(filename);
        ui->label_2->setPixmap(QPixmap::fromImage(*img));
    }
    else{
        a.Visualition();
        QImage *img=new QImage;
        string picture="forest.png";
        QString filename;
        filename=QString::fromStdString(picture);
        img->load(filename);
        ui->label_2->setPixmap(QPixmap::fromImage(*img));
    }
}
//退出程序
void MainWindow::on_Exit_clicked()
{
    close();
}
//二叉树插入左孩子
void MainWindow::on_InsertLChild_clicked()
{
    QString aa=ui->FatherL->text();
    QString bb=ui->LChild->text();
    if(!isDigitStr(aa)||!isDigitStr(bb)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    int father= aa.toInt();
    int child= bb.toInt();
    if(FLAGA&&!FLAGB){
        QString res="Error:The Binary Tree has been changed to Forest!!!";
        ui->label->setText(res);
        return;
    }
    b.InsertNode(1,father,child);
    QString res="Successfully insert the LeftChild!!";
    ui->label->setText(res);
}
//二叉树插入右孩子
void MainWindow::on_InsertRChild_clicked()
{
    QString aa=ui->FatherR->text();
    QString bb=ui->RChild->text();
    if(!isDigitStr(aa)||!isDigitStr(bb)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    int father= aa.toInt();
    int child= bb.toInt();
    if(FLAGA&&!FLAGB){
        QString res="Error:The Binary Tree has been changed to Forest!!!";
        ui->label->setText(res);
        return;
    }
    b.InsertNode(0,father,child);
    QString res="Successfully insert the RightChild!!";
    ui->label->setText(res);
}
//二叉树与森林互换
void MainWindow::on_Change_clicked()
{
    QString res="";
    if(!FLAGA&&!FLAGB){
        res="Error:You should initialize the forest or binarytree first!!!";
        ui->label->setText(res);
        return;
    }
    //森林转二叉树
    else if(FLAGA&&!FLAGB){
        a.Transform(b);
        FLAGA=!FLAGA;
        FLAGB=!FLAGB;
        res="Forest to BinaryTree Successfully!!!";
    }
    //二叉树转森林
    else if(!FLAGA&&FLAGB){
        b.BTreeToForest(a);
        FLAGA=!FLAGA;
        FLAGB=!FLAGB;
        res=" BinaryTree to Forest Successfully!!!";
    }
    ui->label->setText(res);
}

//森林插入结点
void MainWindow::on_pushButton_7_clicked()
{
    QString aa=ui->FatherInsert->text();
    QString bb=ui->ChildInsert->text();
    if(!isDigitStr(bb)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    if(!FLAGA&&FLAGB){
        QString res="Error:The Forest has been changed to BinaryTree!!!";
        ui->label->setText(res);
        return;
    }
    FLAGA=true;
    int father= aa.toInt();
    int child= bb.toInt();
    a.InsertNode(father,child);
    QString res="Insert child node successfully!!!";
    ui->label->setText(res);
}


//森林连接两棵树
void MainWindow::on_pushButton_8_clicked()
{
    QString aa=ui->Root1->text();
    QString bb=ui->Root2->text();
    if(!isDigitStr(aa)||!isDigitStr(bb)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    if(!FLAGA&&FLAGB){
        QString res="Error:The Forest has been changed to BinaryTree!!!";
        ui->label->setText(res);
        return;
    }
    int root1= aa.toInt();
    int root2= bb.toInt();
    int judge=a.InsertEdge(root1,root2);
    QString res="";
    if(judge==0)
        res="Link the two roots successfully!!!";
    else if(judge==1)
        res="Error:The first input is not root!!!";
    else if(judge==2)
        res="Error:The second input is not root!!!";
    else
        res="Error:The two input are both not root!!!";
    ui->label->setText(res);
}

//删除森林结点
void MainWindow::on_pushButton_10_clicked()
{
    QString aa=ui->FatherDelete->text();
    QString bb=ui->ChildDelete->text();
    if(!isDigitStr(aa)||!isDigitStr(bb)){
        QString res="Error:Your input must be integer!!!";
        ui->label->setText(res);
        return;
    }
    if(!FLAGA&&FLAGB){
        QString res="Error:The Forest has been changed to BinaryTree!!!";
        ui->label->setText(res);
        return;
    }
    int father= aa.toInt();
    int child= bb.toInt();
    bool judge=a.EraseNode(father,child);
    QString res="";
    if(judge)
        res="Erase Node successfully!!!";
    else
        res="Error:The father or node is not existed!!!";
    ui->label->setText(res);
}
