#ifndef CHESSBOARD_H
#define CHESSBOARD_H

//坐标
struct Coordinate{
    int x,y;
    Coordinate(){}
    Coordinate(int xx,int yy):x(xx),y(yy){}
};

class ChessBoard{
    public:
        //构造函数
        ChessBoard(int k,int dx,int dy);
        //析构函数
        ~ChessBoard();
        //覆盖以(sx,sy)为左上角，大小为size的棋盘
        void Dye(int sx,int sy,int dx,int dy,int size);
        //覆盖
        void Cover();
        //输出棋盘
        void Output();
        //判断坐标是否越界
        bool Range(int x,int y);
        //确定当前三格板的最小颜色编号
        void GetNo(int x,int y,bool vis[]);
        //三格板着色
        void Color(int sx,int sy,int dx,int dy,int size);
    //private:
        int **a;        //存储棋盘信息
        int Size;       //棋盘边长
        int default_x;  //残缺点行号
        int default_y;  //残缺点列号
        int num;        //使用三格板的个数
        int tot;		//颜色个数
};

#endif // CHESSBOARD_H
