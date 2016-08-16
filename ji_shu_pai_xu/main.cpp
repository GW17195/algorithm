#include <iostream>
#define MAX_NUM_OF_KEY 8//表示一个数最多容纳的数字的位数，12345678，是8位数
#define RADIX 10  //表示基数的个数，如十进制基数有10个0到9
#define MAX_SPACE 1000//表示最大空间，最多有几个数参加排序
using namespace std;
typedef int ArrType[RADIX];
typedef char KeysType;
typedef struct SLCell{

    KeysType keys[RADIX];
    int next;
}SLCell;
typedef struct SLList{
    int keyNum;//表示每个数字最大有多少位_ _ _3
    int recNum;//表示表中有几个数     j计数
    SLCell r[MAX_SPACE];//r[0]为头
}SLList;
void CreateSLList(SLList *L)
{
    for(int indexi=0;indexi<MAX_SPACE;indexi++)
    {
        for(int indexj=0;indexj<RADIX;indexj++)
        {
            (*L).r[indexi].keys[indexj]='0';
        }
    }
    cout<<"请输入每个数最大的位数\n";
    cin>>(*L).keyNum;
    getchar();
    //int count_num=0;
    cout<<"你要输入几个数?\n";
    cin>>(*L).recNum;
    getchar();
    cout<<"请输入数:";
    cout<<"\n";
    (*L).r[0].next=1;////////////////////////////////头指针
    int count_num=1;
    for(int index=1;index<=(*L).recNum;index++)
    {
        char charTmp;

        cout<<"第"<<count_num++<<"个数: ";
        int arrTmp[RADIX];
        int arrTmpCount=0;//下标
        for(;(charTmp=getchar())!='\n';arrTmpCount++)
        {
            arrTmp[arrTmpCount]=charTmp;
        }
        arrTmpCount--;
        int i=0;
        while(arrTmpCount>=0)
        {
            (*L).r[index].keys[RADIX-1-i]=arrTmp[arrTmpCount];//000324
            i++;
            arrTmpCount--;
        }
        (*L).r[index].next=index+1;
    }
    (*L).r[(*L).recNum].next=0;
}

void print(SLList L)
{
    cout<<"\n";
    char tmp;
    for(int indexi=1;indexi<=L.recNum;indexi++){
        for(int indexj=0;indexj<L.keyNum;indexj++){
           if((tmp=L.r[indexi].keys[RADIX-L.keyNum+indexj])!='0')
            cout<< tmp;
        }
        cout<<"\n";
    }
}
void print_next(SLList L)
{
    char tmp;
    int cur=0;
    for(cur=L.r[cur].next;cur!=0;cur=L.r[cur].next){
        for(int indexj=0;indexj<L.keyNum;indexj++){
           if((tmp=L.r[cur].keys[RADIX-L.keyNum+indexj])!='0')
            cout<< tmp;
        }
        cout<<"\n";
    }
}
void Distribute(SLCell L[],int indexKey,ArrType f,ArrType e)
{
    int p;
    for(int i=0;i<RADIX;i++){
        f[i]=0;           //int 类型的指针
        e[i]=0;
    }
    int cur=L[0].next;//是当前处理的数据的指针

    while(cur!=0){
        p=L[cur].keys[indexKey]-'0';//cur是L的   P是f e的
        if(f[p]==0){
            f[p]=cur;
        }
        else{
           L[e[p]].next=cur;
        }
        e[p]=cur;
        cur=L[cur].next;
    }

}
void Collect1(SLCell L[],int indexKey,ArrType f,ArrType e)
{
    int indexj=0;
    int indexi=0;
    L[0].next=0;
    while(1){
        while(f[indexi]==0&&indexi<RADIX){
            indexi++;//find first index of f arry who's member is not zero
        }
        if(indexi>=RADIX){
            L[e[indexj]].next=0;
            break;
        }
        if(L[0].next==0){
            L[0].next=indexi;///////////////////////////////////有错所以不行
        }
        else{
            L[e[indexj]].next=f[indexi];
        }
        indexj=indexi+1;
        while(f[indexj]==0&&indexj<RADIX){
            indexj++;
        }
        if(indexj>=RADIX){
            L[e[indexi]].next=0;
            break;
        }
        L[e[indexi]].next=f[indexj];
        indexi=indexj+1;
    }
}
void Collect(SLCell L[],int indexKey,ArrType f,ArrType e)
{
    int indexj=0;
    int indexi=0;
    L[0].next=0;
    while(1){
        while(f[indexi]==0&&indexi<RADIX){
            indexi++;//find first index of f arry who's member is not zero
        }
        if(indexi>=RADIX){
            L[e[indexj]].next=0;
            break;
        }
        if(L[0].next==0){
            L[0].next=f[indexi];
        }
        else{
            L[e[indexj]].next=f[indexi];
        }
        indexj=indexi+1;
        while(f[indexj]==0&&indexj<RADIX){
            indexj++;
        }
        if(indexj>=RADIX){
            L[e[indexi]].next=0;
            break;
        }
        L[e[indexi]].next=f[indexj];
        indexi=indexj+1;
    }
}
void RadixSort(SLList *L)
{
    ArrType f,e;
    int keyNum=(*L).keyNum;
    for(int index=0;index<keyNum;index++){
        Distribute((*L).r,RADIX-1-index,f,e);
        Collect((*L).r,RADIX-1-index,f,e);
    }
}
int main()
{
    SLList L;
    CreateSLList(&L);
    RadixSort(&L);
    print_next(L);
    getchar();
    return 0;
}
