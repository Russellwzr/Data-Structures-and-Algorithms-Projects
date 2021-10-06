#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ChessBoard.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QString>
#include <cmath>

//判断用户输入是否为整数
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
    this->setWindowTitle("BrokenChessBoard");
    this->setFixedSize(QSize(1230, 980)); // 固定界面的大小
    test=new ChessBoard(2,0,0); // 初始化棋盘
    //flag_1:create
    //flag_2:color
    flag_1=flag_2=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // 初始化棋盘
    map = new QPixmap(900, 900); // 初始化QPixmap的大小
    map->fill(Qt::white); // 填充背景色为白色
    QPainter painter(map); // 指定绘图设备为map
    // 创建一个画笔
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen); // 设置画笔

    sizeH=qreal(map->height())/test->Size;
    sizeW=qreal(map->width())/test->Size;

    // 绘制棋盘
    for(int i=1; i<=test->Size+1;i++)
        // 竖线
        painter.drawLine(QLineF(i*sizeW, 0, i*sizeW, map->height()));
    for(int i=1;i<=test->Size+1;i++)
        // 横线
        painter.drawLine(QLineF(0, i*sizeH, map->width(), i*sizeH));

    // 绘制残缺方格
    // 设置一个画刷
    QBrush brush;
    brush.setColor(QColor(0,0,0));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    QRect rect(test->default_y*sizeW, test->default_x*sizeH, sizeW, sizeH);
    if (flag_1)
        painter.drawRect(rect);

    // flag为true，表示“覆盖棋盘”
    if (flag_2){
        QRandomGenerator generator(10);
        int nums=(test->Size*test->Size-1)/3 + 1;
        QColor colors[nums];
        colors[0]=QColor(0, 0, 0); // 残缺棋盘的数字0，为黑色
        for (int i=1;i<nums;i++)
            colors[i]=QColor(generator.bounded(80, 255),generator.bounded(80, 255),generator.bounded(60, 255));
        for(int i=0;i<test->Size;i++){
            for(int j=0;j<test->Size;j++){
                // 填充颜色
                int temp=test->a[i][j];
                QBrush brusher;
                brusher.setColor(colors[temp]);
                brusher.setStyle(Qt::SolidPattern);
                painter.setBrush(brusher);
                rect.setRect(j*sizeW, i*sizeH, sizeW, sizeH);
                painter.drawRect(rect);
                // 填写数字
                painter.drawText(QPoint(j*sizeW+sizeW/2, i*sizeH+sizeH/2), QString::number(temp));
            }
        }
        flag_2 = false;
    }
    // 绘制
    QPainter painterAll(this); // 指定绘图设备为界面
    painterAll.drawPixmap(QPoint(300, 50), *map);
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

//Create
void MainWindow::on_pushButton_clicked()
{
    // 初始化棋盘
    flag_1 = true;
    QString kk=ui->lineEdit->text();
    QString dr=ui->lineEdit_2->text();
    QString dc=ui->lineEdit_3->text();
    if(!isDigitStr(kk)||!isDigitStr(dr)||!isDigitStr(dc)){
        ui->label_4->setText("Error:The input must be integer!");
        return;
    }
    int k = kk.toInt();
    int defectRow = dr.toInt()-1;
    int defectColumn = dc.toInt()-1;
    delete test; // 清空原来的棋盘
    int sz=pow(2,k);
    if(k<=0||defectRow<=0||defectColumn<=0){
        ui->label_4->setText("Error:The input must be positive integer!");
        return;
    }
    if(defectRow>sz||defectColumn>sz){
        ui->label_4->setText("Error:The input is out of range!");
        return;
    }
    test = new ChessBoard(k, defectRow, defectColumn);
    //绘制棋盘
    this->repaint();
    QString res="Successfully Create ChessBoard!\n";

    res+="The Size of the ChessBoard is ";
    res+=QString::number(sz);
    res+="\n";
    res+="The imperfect coordinates is (";
    res+=dr;res+=", ";res+=dc;res+=").\n";
    ui->label_4->setText(res);
}

//Color
void MainWindow::on_pushButton_3_clicked()
{
    flag_2=true;
    test->Cover();
    this->repaint();
    ui->label_4->setText("Successfully Color ChessBoard!");
}

//Reset
void MainWindow::on_pushButton_4_clicked()
{
    delete test;
    flag_1=false;
    test=new ChessBoard(2,0,0);
    this->repaint();
    ui->label_4->setText("Successfully Reset ChessBoard!");
}
