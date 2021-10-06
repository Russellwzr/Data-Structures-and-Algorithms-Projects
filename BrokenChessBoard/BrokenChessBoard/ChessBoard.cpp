#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>
#include "ChessBoard.h"
using namespace std;

//位移
int d[][2]={{0,1},{0,-1},{1,0},{-1,0}};

//构造函数
ChessBoard::ChessBoard(int k,int dx,int dy){
    Size=pow(2,k);
    default_x=dx;
    default_y=dy;
    tot=num=0;
    //动态申请二维数组
    a=new int*[Size];
    for(int i=0;i<Size;i++)
        a[i]=new int[Size];
    //初始化数组
    for(int i=0;i<Size;i++)
       for(int j=0;j<Size;j++)
           a[i][j]=0;
    //设置残缺点
    a[dx][dy]=-1;
}

//析构函数
ChessBoard::~ChessBoard(){
    //释放内存空间
    for(int i=0;i<Size;i++)
        delete[] a[i];
    delete []a;
}

//判断坐标是否越界
bool ChessBoard::Range(int x,int y){
    if(x<0||x>=Size||y<0||y>=Size||(x==default_x&&y==default_y))
        return false;
    return true;
}

//确定当前三格板的最小颜色编号
void ChessBoard::GetNo(int x,int y,bool vis[]){
    for(int i=0;i<4;i++){
        int dx=x+d[i][0],dy=y+d[i][1];
        if(Range(dx,dy)){
            vis[a[dx][dy]]=true;
        }
    }
}

//三格板染色
void ChessBoard::Color(int sx,int sy,int dx,int dy,int size){
    Coordinate tmp[10];
    tmp[0]=Coordinate(sx+size-1,sy+size-1);
    tmp[1]=Coordinate(sx+size-1,sy+size);
    tmp[2]=Coordinate(sx+size,sy+size-1);
    tmp[3]=Coordinate(sx+size,sy+size);
    bool vis[tot+10];
    memset(vis,0,sizeof(vis));
    //搜索周围区域
    for(int i=0;i<4;i++){
        if(!(tmp[i].x==dx&&tmp[i].y==dy)){
            GetNo(tmp[i].x,tmp[i].y,vis);
        }
    }
    int No=0;
    //确定三格板的最小颜色编号
    for(int i=0;i<tot+10;i++){
        if(!vis[i]){
            No=i;
            break;
        }
    }
    tot=max(tot,No);
    //染色
    for(int i=0;i<4;i++){
        if(!(tmp[i].x==dx&&tmp[i].y==dy)){
            a[tmp[i].x][tmp[i].y]=No;
        }
    }
}

//分治
void ChessBoard::Dye(int sx,int sy,int dx,int dy,int size){
    //覆盖完毕
    if(size<2)
        return;
    num++;
    //从中间分割棋盘
    size/=2;
    // 覆盖左上角子棋盘
    if (dx<sx+size&&dy<sy+size){
        Color(sx,sy,sx+size-1,sy+size-1,size);
        Dye(sx,sy,dx,dy,size);
    }
    else
        Dye(sx,sy,sx+size-1,sy+size-1,size);
    //覆盖右上角子棋盘
    if (dx<sx+size&&dy>=sy+size){
        Color(sx,sy,sx+size-1,sy+size,size);
        Dye(sx,sy+size,dx,dy,size);
    }
    else
        Dye(sx,sy+size,sx+size-1,sy+size,size);
    //覆盖左下角子棋盘
    if (dx>=sx+size&&dy<sy+size){
        Color(sx,sy,sx+size,sy+size-1,size);
        Dye(sx+size,sy,dx,dy,size);
    }
    else
        Dye(sx+size,sy,sx+size,sy+size-1,size);
    // 覆盖右下角子棋盘
    if (dx>=sx+size&&dy>=sy+size){
        Color(sx,sy,sx+size,sy+size,size);
        Dye(sx+size,sy+size,dx,dy,size);
    }
    else
        Dye(sx+size,sy+size,sx+size,sy+size,size);
}

//覆盖
void ChessBoard::Cover(){
    Dye(0,0,default_x,default_y,Size);
}

//输出
void ChessBoard::Output(){
    for(int i=0;i<Size;i++){
        for(int j=0;j<Size;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}
