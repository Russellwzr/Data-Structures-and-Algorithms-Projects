#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LoserTree.h"
#include <QString>

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

void MainWindow::on_pushButton_2_clicked()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    LoserTree a;
    QString aa=ui->lineEdit->text();
    string Input_File=aa.toStdString();
    input_file=(char*)Input_File.c_str();
    QString bb=ui->lineEdit_2->text();
    if(!isDigitStr(bb)){
        ui->label_5->setText("Error:The input of data size is not integer!");
        return;
    }
    Count=bb.toInt();
    QString cc=ui->lineEdit_3->text();
    if(!isDigitStr(cc)){
        ui->label_5->setText("Error:The input of buffer size is not integer!");
        return;
    }
    BUF_SIZE=cc.toInt();
    if(BUF_SIZE<0||BUF_SIZE>2000000){
        QString res="Error:The input data of buffer size is illegal ";
        ui->label_5->setText(res);
        return;
    }
    QString dd=ui->lineEdit_4->text();
    if(!isDigitStr(dd)){
        ui->label_5->setText("Error:The input of k-ways is not integer!");
        return;
    }
    int ways;
    ways=dd.toInt();
    BUF_PAGES=ways+1;
    PAGE_SIZE=BUF_SIZE/BUF_PAGES;
    QString OutPut=a.ExternSort(ways);
    ui->label_5->setText(OutPut);
}
