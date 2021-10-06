#ifndef FORESTANDBTREE_H
#define FORESTANDBTREE_H
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//int转string
void AppendInt(string &s,int &a){
    char buf[10];
    itoa(a,buf,10);
    s+=buf;
}

//dot语言声明二叉树结点
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

//二叉树结点
struct binaryTreeNode
{
    //所存储元素
    int element;
    //左孩子、右孩子
    binaryTreeNode *leftChild,
                     *rightChild;
    //构造函数
    binaryTreeNode() {leftChild = rightChild = NULL;}
    binaryTreeNode(int& theElement):element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(int& theElement,
                  binaryTreeNode *theLeftChild,
                  binaryTreeNode *theRightChild)
                  :element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

//森林结点
struct ForestNode
{
    //所存储元素
    int element;
    //指向孩子或兄弟的指针
    ForestNode *next;
    //构造函数
    ForestNode() {element=0;next=NULL;}
    ForestNode(int& theElement):element(theElement)
    {
        next=NULL;
    }
    ForestNode(int& theElement,ForestNode *thenext)
                  :element(theElement)
    {
        next=thenext;
    }
};

//链表类
class chain
{
    public:
        friend class Forest;
        //构造函数
        chain(){firstnode=NULL;csize=0;}
        //析构函数
        ~chain();
        //返回链表元素个数
        int size(){return csize;}
        //插入操作
        void insert(int key);
        //删除操作
        bool erase(int key);
    private:
        ForestNode* firstnode;//头节点
        int csize;//链表元素个数
};

//析构函数
chain::~chain()
{
    while(firstnode!=NULL)
    {
        ForestNode *p=firstnode->next;
        delete firstnode;
        firstnode=p;
    }
}
//插入操作
void chain::insert(int key)
{
    ForestNode *p=firstnode;
    ForestNode *q=NULL;
    //查找插入的位置
    //移动指针q，使得新元素可以插在q的后面
    while(p!=NULL&&p->element<key)
    {
        q=p;
        p=p->next;
    }
    //链表中存在所要插入的元素
    if(p!=NULL&&p->element==key){}
    //找到插入位置则在q之后插入新节点
    else
    {
        ForestNode *t=new ForestNode(key,p);
        //插入位置为头节点
        if(q==NULL)
            firstnode=t;
        //插入位置不在头节点
        else
            q->next=t;
        csize++;
    }
}
//删除操作
bool chain::erase(int key)
{
    ForestNode *p=firstnode;
    ForestNode *q=NULL;
    //搜索数据域为key的节点
    while(p!=NULL&&p->element<key)
    {
        q=p;
        p=p->next;
    }
    //找到匹配的节点
    if(p!=NULL&&p->element==key)
    {
        //删除头节点
        if(q==NULL)
            firstnode=p->next;
        //删除头节点之后的节点
        else
            q->next=p->next;
        delete p;
        csize--;
        return true;
    }
    //未找到要删除节点
    else{return false;}
}
class linkedBinaryTree;
//森林类
class Forest
{
    public:
        friend class linkedBinaryTree;
        //构造函数
        Forest(int n);
        Forest(){NodeSize=0;tree=new chain[5500];}
        //析构函数
        ~Forest(){}
        //初始化
        void Initialize(int m,int n);
        //插入结点
        void InsertNode(int father,int node);
        //插入边
        int InsertEdge(int a,int b);
        //删除结点
        bool EraseNode(int father,int node);
        //森林转二叉树
        binaryTreeNode* ForestToBinaryTree(int root);
        void Transform(linkedBinaryTree& change1);
        //显示森林（遍历森林元素）
        void ShowForest();
        int ShowLevel(int root);
        //森林可视化
        void Visualition();
    protected:
        //孩子链表
        chain *tree;
        //根节点
        vector<int> root;
        //森林结点个数
        int NodeSize;
};

class linkedBinaryTree
{
    public:
        friend class Forest;
        //构造函数
        linkedBinaryTree() {root = NULL;}
        ~linkedBinaryTree(){erase(root);root = NULL;};
        //判断是否为空
        bool empty() const {return root == NULL;}
        //前序遍历
        int preOrder(binaryTreeNode *t);
        //删除结点
        void erase(binaryTreeNode *t);
        //插入结点
        void InsertNode(int pos,int father,int node);
        //初始化
        void Initialize(int n);
        //查找指定元素所对应的位置
        binaryTreeNode* find(int element);
        //前序遍历
        int PreOrder(){return preOrder(root);}
        //层次遍历
        void levelorder(binaryTreeNode *t);
        void LevelOrder(){levelorder(root);cout<<endl;}
        //改变根结点
        void ChangeRoot(binaryTreeNode *t){erase(root);root=t;};
        //二叉树转森林
        void BiNodeToFNode(binaryTreeNode *t,Forest &f);
        void BTreeToForest(Forest &t);
        //二叉树可视化
        void Visualition();
    protected:
        //根结点
        binaryTreeNode *root;
};

void linkedBinaryTree::Visualition(){
    //重定向输出流到dot文件
    freopen("binarytree.dot","w",stdout);
    //dot语言作图
    cout<<"digraph G{"<<endl;
    cout<<"label=\"Binary Tree\";"<<endl;
    cout<<"node[shape=record];"<<endl;
    queue<binaryTreeNode *> q;
    binaryTreeNode *tmp=root;
    q.push(tmp);
    while(!q.empty()){
        binaryTreeNode *t=q.front();
        q.pop();
        string father=BNodeInfo(t->element);
        cout<<father<<";"<<endl;
        if(t->leftChild!=NULL){
            string left=BNodeInfo(t->leftChild->element);
            cout<<left<<";"<<endl;
            cout<<t->element<<":f0:sw->"<<t->leftChild->element<<":f1;"<<endl;
            q.push(t->leftChild);
        }
        if(t->rightChild!=NULL){
            string right=BNodeInfo(t->rightChild->element);
            cout<<right<<";"<<endl;
            cout<<t->element<<":f2:se->"<<t->rightChild->element<<":f1;"<<endl;
            q.push(t->rightChild);
        }
    }
    cout<<"}"<<endl;
    fclose(stdout);
    //命令行输出图片
    string s = "";
    s += "dot -Tpng ";
    s += "binarytree.dot";
    s += " -o ";
    s+="binarytree.png";
    const char* cmd = s.data();
    system(cmd);
    //重新开启屏幕输出流
    freopen("CON","w",stdout);
}
//二叉树层次遍历
void linkedBinaryTree::levelorder(binaryTreeNode *t){
    queue<binaryTreeNode *> q;
    q.push(t);
    while(!q.empty()){
        binaryTreeNode *p=q.front();
        cout<<p->element<<" ";
        q.pop();
        //扩展左子树
        if(p->leftChild!=NULL)
            q.push(p->leftChild);
        //扩展右子树
        if(p->rightChild!=NULL)
            q.push(p->rightChild);
    }
}
//查找指定元素所在的位置
binaryTreeNode* linkedBinaryTree::find(int element){
    queue<binaryTreeNode*> q;
    binaryTreeNode* tmp=root;
    q.push(tmp);
    while(!q.empty()){
        binaryTreeNode* t=q.front();
        q.pop();
        if(t->element==element)
            return t;
        //查找左子树
        if(t->leftChild!=NULL)
            q.push(t->leftChild);
        //查找右子树
        if(t->rightChild!=NULL)
            q.push(t->rightChild);
    }
    return NULL;
}
//二叉树初始化
void linkedBinaryTree::Initialize(int n){
    //指定根节点
    int rr;
    cin>>rr;
    binaryTreeNode* nodes[n+10];
    for(int i=1;i<=n;i++){
        nodes[i]=new binaryTreeNode(i);
    }
    int A,l,r;
    //输入结点信息并插入
    for(int i=0;i<n;i++){
        cin>>A>>l>>r;
        //插入左孩子
        if(l!=-1)
            nodes[A]->leftChild=nodes[l];
        //插入右孩子
        if(r!=-1)
            nodes[A]->rightChild=nodes[r];
    }
    root=nodes[rr];
}
//插入结点
void linkedBinaryTree::InsertNode(int pos,int father,int node){
    queue<binaryTreeNode*> q;
    binaryTreeNode* tmp=root;
    q.push(tmp);
    while(!q.empty()){
        binaryTreeNode* t=q.front();
        q.pop();
        //找到对应的位置
        if(t->element==father){
            //插入右孩子
            if(pos==0){
                t->rightChild=new binaryTreeNode(node);
            }
            //插入左孩子
            else{
                t->leftChild=new binaryTreeNode(node);
            }
            return;
        }
        //扩展查找子树
        if(t->leftChild!=NULL)
            q.push(t->leftChild);
        if(t->rightChild!=NULL)
            q.push(t->rightChild);
    }
}
//删除结点
void linkedBinaryTree::erase(binaryTreeNode *t)
{
    if (t != NULL)
    {
        //删除左子树
        erase(t->leftChild);
        //删除右子树
        erase(t->rightChild);
        //释放结点空间
        delete t;
    }
}
//前序遍历
int linkedBinaryTree::preOrder(binaryTreeNode *t)
{
    int sum=0;
    if (t != NULL)
    {
        //访问父结点
        sum^=t->element;
        //前序遍历左子树
        sum^=preOrder(t->leftChild);
        //前序遍历右子树
        sum^=preOrder(t->rightChild);
    }
    return sum;
}
//二叉树转树
void linkedBinaryTree::BiNodeToFNode(binaryTreeNode *t,Forest &f)
{
    binaryTreeNode* r=t;
    binaryTreeNode* p=r;
    //沿左孩子方向进行转换
    while(r!=NULL){
        int father=r->element;
        p=r->leftChild;
        while(p!=NULL){
            f.tree[father].insert(p->element);
            p=p->rightChild;
            //递归转换右子树
            BiNodeToFNode(p,f);
        }
        r=r->leftChild;
    }
}
//二叉树转森林
void linkedBinaryTree::BTreeToForest(Forest &t)
{
    vector<binaryTreeNode*> ROOT;
    binaryTreeNode *tmp=root;
    //分离根结点
    while(tmp!=NULL){
        binaryTreeNode *rroot=new binaryTreeNode(tmp->element);
        rroot->leftChild=tmp->leftChild;
        ROOT.push_back(rroot);
        tmp=tmp->rightChild;
    }
    int size=ROOT.size();
    //对分离后的根结点执行转换操作
    for(int i=0;i<size;i++){
        t.root.push_back(ROOT[i]->element);
        binaryTreeNode* r=ROOT[i];
        BiNodeToFNode(r,t);
    }
}

void Forest::Visualition(){
    //重定向输出流到dot文件
    freopen("forest.dot","w",stdout);
    //dot语言作图
    cout<<"digraph G{"<<endl;
    cout<<"label=\"Forest\";"<<endl;
    cout<<"node[shape=circle];"<<endl;
    sort(root.begin(),root.end());
    int size=root.size();
    for(int i=0;i<size;i++){
        queue<int> q;
        q.push(root[i]);
        cout<<root[i]<<";"<<endl;
        while(!q.empty()){
            int tmp=q.front();
            q.pop();
            ForestNode *p=tree[tmp].firstnode;
            while(p!=NULL){
                cout<<p->element<<";"<<endl;
                cout<<tmp<<"->"<<p->element<<";"<<endl;
                q.push(p->element);
                p=p->next;
            }
        }
    }
    cout<<"}"<<endl;
    fclose(stdout);
    //命令行输出图片
    string s = "";
    s += "dot -Tpng ";
    s += "forest.dot";
    s += " -o ";
    s+="forest.png";
    const char* cmd = s.data();
    system(cmd);
    //重新开启屏幕输出流
    freopen("CON","w",stdout);
}
//构造函数
Forest::Forest(int n){
    NodeSize=n;
    tree=new chain[n+200];
}
//森林初始化
void Forest::Initialize(int m,int n){
    int NodeElement;
    //输入根结点
    for(int i=1;i<=m;i++){
        int rootnode;
        cin>>rootnode;
        root.push_back(rootnode);
    }
    int father,num;
    //根据输入信息插入结点
    for(int i=1;i<=n;i++){
        cin>>father>>num;
        while(num--){
            cin>>NodeElement;
            tree[father].insert(NodeElement);
        }
    }
}
//层次遍历树
int Forest::ShowLevel(int root){
    int sum=0;
    queue<int> q;
    q.push(root);
    sum^=root;
    while(!q.empty()){
        int tmp=q.front();
        q.pop();
        ForestNode *p=tree[tmp].firstnode;
        //按层扩展
        while(p!=NULL){
            sum^=p->element;
            q.push(p->element);
            p=p->next;
        }
    }
    return sum;
}
//层次遍历森林
void Forest::ShowForest(){
    //对根结点从小到大排序
    sort(root.begin(),root.end());
    int size=root.size();
    //遍历森林中的每一颗树
    for(int i=0;i<size;i++)
        cout<<ShowLevel(root[i])<<" ";
    cout<<endl;
}
//插入结点
void Forest::InsertNode(int father,int node){
    //插入根节点
    if(father==-1){
        root.push_back(node);
    }
    //插入子结点
    else{
        tree[father].insert(node);
    }
    NodeSize++;
}
//删除结点
bool Forest::EraseNode(int father,int node){
    bool flag=false;
    //删除根结点
    if(father==-1){
        vector<int>::iterator iter=root.begin();
        while(iter!=root.end()){
            if(*iter==node){
                flag=true;
                root.erase(iter);
                break;
            }
            iter++;
        }
        ForestNode *p=tree[node].firstnode;
        while(p!=NULL){
            root.push_back(p->element);
            ForestNode *q=p->next;
            delete p;
            p=q;
        }
    }
    //删除的不是根结点
    else{
        flag=tree[father].erase(node);
        ForestNode *p=tree[node].firstnode;
        while(p!=NULL){
            root.push_back(p->element);
            ForestNode *q=p->next;
            delete p;
            p=q;
        }
    }
    NodeSize--;
    return flag;
}
//插入边
int Forest::InsertEdge(int a,int b){
    bool flaga=0;
    bool flagb=0;
    vector<int>::iterator iter=root.begin();
    //首先判断输入的a、b是否为根结点并将b从根结点数组中删除
    while(iter!=root.end()){
        if(*iter==a){
            flaga=true;
        }
        if(*iter==b){
            flagb=true;
            root.erase(iter);
        }
        iter++;
    }
    //a、b连接
    if(flaga&&flagb){
        tree[a].insert(b);
        return 0;
    }
    else if(flaga&&!flagb){
        return 2;
    }
    else if(!flaga&&flagb){
        return 1;
    }
    else
        return 3;
}
//树转二叉树
binaryTreeNode* Forest::ForestToBinaryTree(int root)
{
    binaryTreeNode* binaryRoot=new binaryTreeNode(root);
    if (tree[root].size()<=0){
        return binaryRoot;
    }
    //递归转换左子树
    binaryRoot->leftChild=ForestToBinaryTree(tree[root].firstnode->element);
    //兄弟结点变右子树
    binaryTreeNode *brotherChild=binaryRoot->leftChild;
    ForestNode *p=tree[root].firstnode->next;
    while(p!=NULL)
    {
        brotherChild->rightChild=ForestToBinaryTree(p->element);
        brotherChild=brotherChild->rightChild;
        p=p->next;
    }
    return binaryRoot;
}
//森林转二叉树
void Forest::Transform(linkedBinaryTree& change1){
    //对根结点进行排序
    sort(root.begin(),root.end());
    binaryTreeNode* t=ForestToBinaryTree(root[0]);
    binaryTreeNode* tmp=t;
    int size=root.size();
    //对森林中的每颗树进行转换并连接
    for(int i=1;i<size;i++){
        tmp->rightChild=ForestToBinaryTree(root[i]);
        tmp=tmp->rightChild;
    }
    change1.ChangeRoot(t);
}

#endif // FORESTANDBTREE_H
