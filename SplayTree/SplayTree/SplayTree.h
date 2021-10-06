#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "maxHeap.h"
#include <QMessageBox>
#include <QString>

using namespace std;

//存储单词信息
struct WordFrequency{
    //单词
    string word;
    //出现次数
    int frequency;
    //构造函数
    WordFrequency(){word="";frequency=0;}
    WordFrequency(string ww,int fre){
        word=ww;
        frequency=fre;
    }
    //重载运算符
    bool operator<(const WordFrequency &s)const{
        return frequency<s.frequency;
    }
    bool operator>=(const WordFrequency &s)const{
        return !(frequency<s.frequency);
    }
};

//伸展树节点
template <class T>
struct SplayTreeNode{
    T element;//关键字
    SplayTreeNode *LeftChild;//左孩子
    SplayTreeNode *RightChild;//右孩子
    int count;//该关键字出现的次数
    int sz;//子树中节点的数目

    //构造函数
    SplayTreeNode():count(1),sz(1) {LeftChild=RightChild=NULL;}
    SplayTreeNode(T& theElement):element(theElement),count(1),sz(1){LeftChild=RightChild=NULL;}
    SplayTreeNode(T& theElement,
                SplayTreeNode *theLeftChild,
                SplayTreeNode *theRightChild)
                :element(theElement),count(1),sz(1){LeftChild=theLeftChild;RightChild=theRightChild;}

    //复制构造函数
    SplayTreeNode(SplayTreeNode<T>* t){
        element=t->element;
        LeftChild=t->LeftChild;
        RightChild=t->RightChild;
        count=t->count;
        sz=t->sz;
    }
};

class Solve;

template <class T>
class SplayTree{
    friend class Solve;
    public:
        //构造函数
        SplayTree();
        //析构函数
        ~SplayTree();
        //返回树中节点个数
        int TreeSize(){return Size;}
        //更改根节点
        void ChangeRoot(SplayTreeNode<T>* t);
        //返回根节点
        SplayTreeNode<T>* TreeRoot(){return Root;}
        //删除t节点及其子树
        void DeleteTree(SplayTreeNode<T>* t);
        //左旋
        SplayTreeNode<T>* Left_Rotate(SplayTreeNode<T>* t);
        //右旋
        SplayTreeNode<T>* Right_Rotate(SplayTreeNode<T>* t);
        //伸展
        SplayTreeNode<T>* Splay(SplayTreeNode<T>* t,T key);
        //查找
        SplayTreeNode<T>* SearchNode(T& theElement);
        //返回最大
        SplayTreeNode<T>* MaxElement();
        //返回最小
        SplayTreeNode<T>* MinElement();
        //初始化
        void Init(vector<T> a);
        //插入
        void InsertNode(T& theElement);
        //删除
        bool EraseNode(T& theElement);
        //中序插入
        void InorderInsert(SplayTreeNode<T>* t);
        //拆分
        vector<SplayTreeNode<T>*> SplitTree(T& theElement);
        //合并
        SplayTreeNode<T>* MergeTree(vector<SplayTreeNode<T>* >);
        //层次遍历
        void LevelOrder(SplayTreeNode<T>* t);
        void LevelOrder();
        //可视化
        void Visualization();
        void Visualization(vector<SplayTreeNode<T>*> roots);
    private:
        //根节点
        SplayTreeNode<T> *Root;
        //节点数目
        int Size;
};

//构造函数
template <class T>
SplayTree<T>::SplayTree(){
    Root=NULL,Size=0;
}

//改变根节点
template <class T>
void SplayTree<T>::ChangeRoot(SplayTreeNode<T>* t){
    Root=t;
    Size=t->sz;
}

//析构函数
template <class T>
SplayTree<T>::~SplayTree(){
    DeleteTree(Root);
    Size=0;
}

//删除t及其子树
template <class T>
void SplayTree<T>::DeleteTree(SplayTreeNode<T>* t){
    if(t!=NULL){
        //删除左子树
        DeleteTree(t->LeftChild);
        //删除右子树
        DeleteTree(t->RightChild);
        //删除t
        delete t;
    }
}

//左旋
template <class T>
SplayTreeNode<T>* SplayTree<T>::Left_Rotate(SplayTreeNode<T>* t){
    SplayTreeNode<T>* right=t->RightChild;
    t->RightChild=right->LeftChild;
    //更新各节点的子节点数目信息
    int PreTsz=(t==NULL)?0:t->sz,
        PreRsz=(right==NULL)?0:right->sz,
        PreLsz=(t->RightChild==NULL)?0:t->RightChild->sz;
    right->LeftChild=t;
    t->sz=PreTsz-PreRsz+PreLsz;
    right->sz=PreTsz;
    return right;
}

//右旋
template <class T>
SplayTreeNode<T>* SplayTree<T>::Right_Rotate(SplayTreeNode<T>* t){
    SplayTreeNode<T>* left=t->LeftChild;
    t->LeftChild=left->RightChild;
    //更新各节点的子节点数目信息
    int PreTsz=(t==NULL)?0:t->sz,
        PreLsz=(left==NULL)?0:left->sz,
        PreRsz=(t->LeftChild==NULL)?0:t->LeftChild->sz;
    left->RightChild=t;
    t->sz=PreTsz-PreLsz+PreRsz;
    left->sz=PreTsz;
    return left;
}

//伸展
template <class T>
SplayTreeNode<T>* SplayTree<T>::Splay(SplayTreeNode<T>* t,T key){
    //树为空退出
    if(t==NULL)
        return t;

    //创建两棵临时树
    //左树保存小于当前根节点的节点
    //右树保存大于当前根节点的节点
    SplayTreeNode<T> head;
    SplayTreeNode<T> *LeftTree,*RightTree;
    head.LeftChild=head.RightChild=NULL;
    LeftTree=RightTree=&head;

    while(key!=t->element){
        if(key<t->element){
            if(t->LeftChild==NULL)
                break;
            //右旋
            if(key<t->LeftChild->element){
                t=Right_Rotate(t);
            }
            if(t->LeftChild==NULL)
                break;
            //连接到右树
            RightTree->LeftChild=t;
            RightTree=t;
            t=t->LeftChild;
        }
        else{
            if(t->RightChild==NULL)
                break;
            //左旋
            if(key>t->RightChild->element)
                t=Left_Rotate(t);
            if(t->RightChild==NULL)
                break;
            //连接到左树
            LeftTree->RightChild=t;
            LeftTree=t;
            t=t->RightChild;
        }
    }

    //组装
    LeftTree->RightChild=t->LeftChild;
    RightTree->LeftChild=t->RightChild;
    t->LeftChild=head.RightChild;
    t->RightChild=head.LeftChild;
 //   Root=t;

    return t;
}

//返回最小
template <class T>
SplayTreeNode<T>* SplayTree<T>::MinElement(){
    SplayTreeNode<T> t=new SplayTreeNode<T>(Root);
    while(t!=NULL){
        //沿着左子树搜索最小元素
        while(t->LeftChild!=NULL)
            t=t->LeftChild;
        //将最小元素伸展到根节点
        return Root=Splay(Root,t->element);
    }
    return NULL;
}

//返回最大
template <class T>
SplayTreeNode<T>* SplayTree<T>::MaxElement(){
    SplayTreeNode<T> t=new SplayTreeNode<T>(Root);
    while(t!=NULL){
        //沿着右子树搜索最大元素
        while(t->RightChild!=NULL)
            t=t->RightChild;
        //将最大元素伸展到根节点
        return Root=Splay(Root,t->element);
    }
    return NULL;
}

//初始化
template <class T>
void SplayTree<T>::Init(vector<T> a){
    for(int i=0;i<a.size();i++)
        InsertNode(a[i]);
}

//查找
template <class T>
SplayTreeNode<T>* SplayTree<T>::SearchNode(T& theElement){
    return Root=Splay(Root,theElement);
}

//插入
template <class T>
void SplayTree<T>::InsertNode(T& theElement){
    SplayTreeNode<T>* newNode=new SplayTreeNode<T>(theElement);
    //树为空
    if(Root==NULL){
        Root=newNode;
        Size++;
    }
    else{
        SplayTreeNode<T>* t=SearchNode(theElement);
        int PreTsz=(t==NULL)?0:t->sz,
            PreLsz=(t->LeftChild==NULL)?0:t->LeftChild->sz,
            PreRsz=(t->RightChild==NULL)?0:t->RightChild->sz;
        //已存在
        if(theElement==t->element){
            t->count++;
        }

        else if(theElement<t->element){
            newNode->LeftChild=t->LeftChild;
            newNode->RightChild=t;
            newNode->sz+=PreTsz;
            t->sz-=PreLsz;
            t->LeftChild=NULL;
            Root=newNode;
            Size++;
        }

        else{
            newNode->sz+=PreTsz;
            t->sz-=PreRsz;
            newNode->RightChild=t->RightChild;
            t->RightChild=NULL;
            newNode->LeftChild=t;
            Root=newNode;
            Size++;
        }
    }
}

//中序插入
template <class T>
void SplayTree<T>::InorderInsert(SplayTreeNode<T>* t){
    if(t!=NULL){
        //插入左子树
        InorderInsert(t->LeftChild);
        //插入t
        InsertNode(t->element);
        //插入右子树
        InorderInsert(t->RightChild);
    }
}

//删除
template <class T>
bool SplayTree<T>::EraseNode(T& theElement){
    SplayTreeNode<T>* t=SearchNode(theElement);
    if(t==NULL)
        return false;
    SplayTreeNode<T>* tRoot;
    SplayTreeNode<T>* tLeft=NULL;
    if(t->LeftChild!=NULL)
        tLeft=new SplayTreeNode<T>(t->LeftChild);
    //找到要删除的节点
    if(theElement==t->element){
        if(t->RightChild==NULL){
            tRoot=t->LeftChild;
        }
        else{
            tRoot=Splay(t->RightChild,theElement);
            tRoot->LeftChild=tLeft;
        }
        Root=tRoot;
        Size--;
        delete t;
        return true;
    }
    //删除失败
    else{
        cout<<"Delete Error:The Node not exists in the tree!"<<endl;
        return false;
    }
}

//层次遍历
template <class T>
void SplayTree<T>::LevelOrder(){
    LevelOrder(Root);
}

template <class T>
void SplayTree<T>::LevelOrder(SplayTreeNode<T>* t){
    if(t==NULL){
        cout<<"Error:The tree is empty!!!"<<endl;
        return;
    }
    queue<SplayTreeNode<T>*> q;
    q.push(t);
    while(!q.empty()){
        SplayTreeNode<T>* tmp=q.front();
        q.pop();
        cout<<tmp->element<<" "<<tmp->count<<endl;
        //左孩子入队
        if(tmp->LeftChild!=NULL)
            q.push(tmp->LeftChild);
        //右孩子入队
        if(tmp->RightChild!=NULL)
            q.push(tmp->RightChild);
    }
    cout<<endl;
}

//拆分为<=T、>T的两棵伸展树
template <class T>
vector<SplayTreeNode<T>*> SplayTree<T>::SplitTree(T& theElement){
    vector<SplayTreeNode<T>*> roots(NULL,NULL);
    if(Root==NULL){
        return roots;
    }
    SplayTreeNode<T>* t=SearchNode(theElement);
    int PreRsz=(t->RightChild==NULL)?0:t->RightChild->sz;
    roots.push_back(t->RightChild);
    t->RightChild=NULL;
    t->sz-=PreRsz;
    roots.push_back(t);
    return roots;
}


//合并两棵伸展树
template <class T>
SplayTreeNode<T>* SplayTree<T>::MergeTree(vector<SplayTreeNode<T>* > roots){
    if(roots[0]==NULL&&roots[1]==NULL)
        return NULL;
    if(roots[0]!=NULL&&roots[1]==NULL)
        return roots[0];
    if(roots[0]==NULL&&roots[1]!=NULL)
        return roots[1];
    int idx=0;
    //确定节点数目最多的那棵树
    if(roots[0]->sz>=roots[1]->sz){
        ChangeRoot(roots[0]);
        idx=1;
    }
    else{
        ChangeRoot(roots[1]);
        idx=0;
    }
    //将节点数目较小的那棵树逐个插入到大树中完成合并
    InorderInsert(roots[idx]);
    return Root;
}

//int转string
void AppendInt(string &s,int &a){
    char buf[10];
    itoa(a,buf,10);
    s+=buf;
}

//dot语言声明节点
string BNodeInfo(int e){
    string father="";
    string element="";
    AppendInt(element,e);
    father+=element;
    father+="[label=\"<f0>|<f1>";
    father+=element;
    father+="|<f2>\"]";
    return father;
}

//可视化
template <class T>
void SplayTree<T>::Visualization(vector<SplayTreeNode<T>*> roots){
    if(roots.size()==0){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Error:The tree is empty!!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    //重定向输出流到dot文件
  //  freopen("SplayTree.dot","w",stdout);
    ofstream out;
    out.open("SplayTree.dot");
    if(!out){
        QMessageBox message(QMessageBox::NoIcon, "Error", "  can not open the input file! ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
    }
    //dot语言作图
    out<<"digraph G{"<<endl;
    out<<"label=\"Splay Tree\";"<<endl;
    out<<"node[shape=record];"<<endl;
    queue<SplayTreeNode<T>*> q;
    for(int i=0;i<roots.size();i++){
        q.push(roots[i]);
    }
    //层次遍历打印节点信息
    while(!q.empty()){
        SplayTreeNode<T>* t=q.front();
        q.pop();
        //dot语言声明父节点
        string father=BNodeInfo(t->element);
        out<<father<<";"<<endl;
        //打印左孩子信息
        if(t->LeftChild!=NULL){
            string left=BNodeInfo(t->LeftChild->element);
            out<<left<<";"<<endl;
            out<<t->element<<":f0:sw->"<<t->LeftChild->element<<":f1;"<<endl;
            q.push(t->LeftChild);
        }
        //打印右孩子信息
        if(t->RightChild!=NULL){
            string right=BNodeInfo(t->RightChild->element);
            out<<right<<";"<<endl;
            out<<t->element<<":f2:se->"<<t->RightChild->element<<":f1;"<<endl;
            q.push(t->RightChild);
        }
    }
    out<<"}"<<endl;
//    fclose(stdout);
    //命令行输出图片
    string s = "";
    s += "dot -Tpng ";
    s += "SplayTree.dot";
    s += " -o ";
    s+="SplayTree.png";
    const char* cmd = s.data();
    system(cmd);
    //重新开启屏幕输出流
 //   freopen("CON","w",stdout);
}

template <class T>
void SplayTree<T>::Visualization(){
    if(Root==NULL){
        QMessageBox message(QMessageBox::NoIcon, "Error", "   Error:The tree is empty!!!  ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
        return;
    }
    //重定向输出流到dot文件
   // freopen("SplayTree.dot","w",stdout);
    ofstream out;
    out.open("SplayTree.dot");
    if(!out){
        QMessageBox message(QMessageBox::NoIcon, "Error", "  can not open the input file! ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
    }
    //dot语言作图
    out<<"digraph G{"<<endl;
    out<<"label=\"Splay Tree\";"<<endl;
    out<<"node[shape=record];"<<endl;
    queue<SplayTreeNode<T>*> q;
    SplayTreeNode<T>* tmp=Root;
    q.push(tmp);
    while(!q.empty()){
        SplayTreeNode<T>* t=q.front();
        q.pop();
        //dot语言声明父亲节点
        string father=BNodeInfo(t->element);
        out<<father<<";"<<endl;
        //打印左孩子节点
        if(t->LeftChild!=NULL){
            string left=BNodeInfo(t->LeftChild->element);
            out<<left<<";"<<endl;
            out<<t->element<<":f0:sw->"<<t->LeftChild->element<<":f1;"<<endl;
            q.push(t->LeftChild);
        }
        //打印右孩子节点
        if(t->RightChild!=NULL){
            string right=BNodeInfo(t->RightChild->element);
            out<<right<<";"<<endl;
            out<<t->element<<":f2:se->"<<t->RightChild->element<<":f1;"<<endl;
            q.push(t->RightChild);
        }
    }
    out<<"}"<<endl;
    out.close();
    //命令行输出图片
    string s = "";
    s += "dot -Tpng ";
    s += "SplayTree.dot";
    s += " -o ";
    s+="SplayTree.png";
    const char* cmd = s.data();
    system(cmd);
    //重新开启屏幕输出流
  //  freopen("CON","w",stdout);
}

//统计单词频率类
class Solve{
    public:
        //构造函数
        Solve(){
            test.Root=NULL;
            test.Size=0;
        };
        //析构函数
        ~Solve(){
            test.~SplayTree();
        }
        //预处理
        void Preprocessing(string input_file);
        //统计
        void StatisticsSolve(int K);
        //查找
        int SearchWord(string element);
    private:
        //存储单词信息的伸展树
        SplayTree<string> test;
};

//预处理
void Solve::Preprocessing(string input_file){
    const char *file_input=input_file.c_str();
    ifstream in(file_input);
    //异常处理
    if(!in){
        QMessageBox message(QMessageBox::NoIcon, "Error", "  can not open the input file! ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
    }
    ofstream out("test.txt");
    string word;
    string ttt="your's";
    char str=ttt[4];
    //去除标点符号、大写转小写
    while (in>>word)
    {
        for(int i=0;i<word.size();i++){
            if((word[i]>='a'&&word[i]<='z')||word[i]==str)
                continue;
            else if(word[i]>='A'&&word[i]<='Z')
                word[i]=word[i]+32;
            else
                word[i]=' ';
        }
        out<<word<<" ";
    }
    in.close();
    out.close();
}

//统计
void Solve::StatisticsSolve(int K){
    int WordCount=0;
    string word;
    ifstream in("test.txt");
    if(!in){
        cout<<"Error:can not open the transfered input file!"<<endl;
        exit(0);
    }
    //将各单词插入到伸展树中
    while(in>>word){
        WordCount++;
        test.InsertNode(word);
    }
    ofstream out_1;
    out_1.open("output_1.txt");
//    freopen("output_1.txt","w",stdout);
    //异常处理
    if(test.TreeRoot()==NULL){
        QMessageBox message(QMessageBox::NoIcon, "Error", "  The tree is empty! ");
        message.setIconPixmap(QPixmap("warning.png"));
        message.exec();
    }  
    maxHeap<WordFrequency> heap;
    queue<SplayTreeNode<string>*> q;
    q.push(test.TreeRoot());
    //层次遍历输出信息
    while(!q.empty()){
        SplayTreeNode<string>* tmp=q.front();
        q.pop();
        //压入大根堆
        heap.push(WordFrequency(tmp->element,tmp->count));
        out_1<<tmp->element<<" "<<tmp->count<<endl;
        if(tmp->LeftChild!=NULL)
            q.push(tmp->LeftChild);
        if(tmp->RightChild!=NULL)
            q.push(tmp->RightChild);
    }
  //  fclose(stdout);
    ofstream out_2;
    out_2.open("output_2.txt");
  //  freopen("output_2.txt","w",stdout);
    out_2<<"Total Number of the Word:"<<WordCount<<endl<<endl;
    //输出Top K
    for(int i=1;i<=K;i++){
        if(heap.empty())
            break;
        WordFrequency t=heap.top();
        heap.pop();
        out_2<<left<<setw(10)<<i<<setw(20)<<t.word<<setw(10)<<t.frequency<<setw(10)<<(double)100*t.frequency/(double)WordCount<<"%"<<endl;
    }
   // fclose(stdout);
}

//查询单词
int Solve::SearchWord(string element){
    SplayTreeNode<string> *t=test.SearchNode(element);
    //查询成功
    if(t!=NULL&&t->element==element){
        return t->count;
    }
    //查询失败
    return -1;
}

#endif // SPLAYTREE_H
