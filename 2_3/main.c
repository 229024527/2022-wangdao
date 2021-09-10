#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define random(x) (rand()%x)

//链表的链式表示

//单链表结构, 头结点是空的，不存数据
typedef struct LNode{
    int data;   //数据域
    struct LNode *next; //下一个节点指针
}LNode, *OneLink;   //强调一个节点用LNode，强调一个单链表用 OneLink, OneLink为指向结构体LNode的指针类型，这里OneLink与LNode*等价

/*************单链表**************/
/*
  功能 : 初始化单链表   暂时不用
  参数 : L - 头结点
  返回 : -1错误，0成功
 */
OneLink InitOneLink()
{
    OneLink L;
    L = (LNode *)malloc(sizeof(LNode));
    if(L==NULL)
    {
        printf("init_one_link error\n");
        return NULL;
    }
    L->data=0;
    L->next=NULL;

    return L;
}

/*
  功能 : 打印链表,包含头结点
  参数 : L - 头结点
  返回 :
 */
void printfOneLink(OneLink L)
{
    if(L->next==NULL)
    {
        printf("link is null\n");
        return;
    }
    int i = 1;
    LNode *cur;
    cur = L;  //头结点的下一个
    while(cur!=NULL)
    {
        if(cur->next!=NULL)
        {
            printf("position:%d, data:%d, next_data:%d\n",i,cur->data,cur->next->data);
        }else{
            printf("position:%d, data:%d, next is NULL\n",i,cur->data);
        }

        cur = cur->next;
        i++;
    }
    printf("list len:%d\n",i-1);
}

/*
  功能 : 头部插入
  参数 : L - 头结点
  返回 : 链表或NULL
 */
OneLink InsertFromHead(OneLink L)
{
    //创建头结点
    L = (OneLink)malloc(sizeof(LNode));
    if(L==NULL){
        printf("out of memory,operation failed!\n");
        return NULL;
    }
    L->data = 0;
    L->next = NULL;    //初始为空链表

    int data;
    LNode *newNode;
    srand((int)time(0));    //随机因子
    for(int i=0;i<6;i++)
    {
        data = random(17);
        newNode = (LNode *)malloc(sizeof(LNode));
        if(newNode==NULL){
            printf("out if memory,operation failed!\n");
            return NULL;
        }
        newNode->data = data;
        newNode->next = L->next;
        L->next = newNode;
    }
    printfOneLink(L);
    return L;
}

/*
  功能 : 尾部插入
  参数 : L - 头结点
  返回 : 链表或NULL
 */
void InsertFromTail(OneLink L)
{
    //接收数据
    int data;
    LNode *newNode;
    srand((int)time(0));    //随机因子
    for(int i=6;i>0;i--)
    {
        data = random(10);
        //data = i;
        newNode = (LNode *)malloc(sizeof(LNode));
        if(newNode==NULL){
            printf("out if memory,operation failed!\n");
            return ;
        }
        newNode->data = data;
        newNode->next = NULL;

        //如果链表只有头结点，先插入
        if(L->next==NULL)
        {
            L->next = newNode;
        } else{
            //尾部插入
            LNode *cur;
            cur = L->next;
            //遍历到尾结点
            while(cur->next!=NULL)
            {
                cur = cur->next;
            }
            cur->next = newNode;
        }

    }
    printfOneLink(L);
}

/*
 功能 : 按序号查找结点值
 参数 : L->链表的头节点, index->位置(从1开始)
 返回 : -1错误，0-没找到，其他-找到的值
 */
int GetValueFromIndex(OneLink L,int index)
{
    //判断位置i是否合法,位序是从1开始
    if(index<1){
        printf("the position you entered is wrongful!\n");
        return -1;
    }
    int i = 1;
    LNode *cur = L->next;
    while(cur!=NULL)
    {
        if(i==index)
        {
            return cur->data;
        }
        i++;
        cur = cur->next;
    }
    return 0;
}

/*
 功能 : 按值查找结点
 参数 : L->链表的头节点, value->数值
 返回 : 找到的结点，或NULL
 */
LNode *GetNodeByValue(OneLink L,int value)
{
    //链表为空，返回空
    if(L->next==NULL)
    {
        return NULL;
    }
    LNode *cur = L->next;
    while(cur!=NULL)
    {
        if(cur->data == value)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

/*
 功能 : 在指定的位序位置插入数据,位序从1开始
 参数 : L->链表的头节点, index->位置,从1开始, data->要插入的数据
 返回 : -1错误，0成功
 */
int OneLinkInsert(OneLink L,int index,int data)
{
    //判断位置i是否合法,位序是从1开始
    if(index<1){
        printf("the position you entered is wrongful!\n");
        return -1;
    }

    LNode *cur = L;
    //构建新结点
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = data;
    newNode->next = NULL;
    int i=1;
    while(cur->next!=NULL)
    {
        if(index==i)     //找到了要插入的位置
        {
           newNode->next = cur->next;
           cur->next = newNode;
           printf("OneLinkInsert success!\n");
           return 0;
        } else{
            i++;
            cur = cur->next;
        }
    }
    //到这里还没结束，再看一下是否要插入最后一个结点
    if(index==i)
    {
        newNode->next = cur->next;
        cur->next = newNode;
        printf("OneLinkInsert success!\n");
    }
    printf("index error!\n");

    return 0;
}

/*
 功能 : 删除第index个结点
 参数 : L->链表的头节点, index->位置
 返回 : -1错误，0成功
 */
void DeleteNode(OneLink L, int index)
{
    if(index<1)
    {
        printf("the position you entered is wrongful!\n");
        return;
    }
    LNode *cur=L;
    int i=1;
    while(cur->next!=NULL)
    {
        if(index==i)    //找到了
        {
            cur->next = cur->next->next;
            printf("delete success!\n");
            return;
        }
        i++;
        cur = cur->next;
    }
    //到这里还没结束，再看一下是否要删除最后一个结点
    if(index == i)
    {
        cur = NULL;
        printf("delete success!\n");
    }
}

/*************单链表**************/

/*************单循环链表**************/
/*
  功能 : 初始化单循环链表
  参数 : L - 头结点
  返回 : 链表或者null
 */
OneLink InitLoopOneLink()
{
    OneLink L;
    L = (LNode *)malloc(sizeof(LNode));
    if(L==NULL)
    {
        printf("init_one_loop_link error\n");
        return NULL;
    }
    L->data = 0;
    L->next = L;
    printf("init_one_loop_link success\n");
    return L;
}

//打印单向循环链表
void printfOneLoopLink(OneLink L)
{
    if(L->next==L)
    {
        printf("link is null\n");
        return;
    }
    int i = 1;
    LNode *cur;
    cur = L->next;  //头结点的下一个
    printf("position:%d, data:%d, next_data:%d\n",i-1,L->data,L->next->data);
    while(cur!=L)
    {
        printf("position:%d, data:%d, next_data:%d\n",i,cur->data,cur->next->data);
        cur = cur->next;
        i++;
    }
    printf("list len:%d\n",i-1);
}

/*
  功能 : 头部插入
  参数 : L - 链表头结点
  返回 :
 */
void InsertOneLoopLinkFromHead(OneLink L)
{
    LNode *newNode;
    for(int i=6;i>0;i--)
    {
        newNode = (LNode*)malloc(sizeof(LNode));
        if(newNode==NULL)
        {
            printf("init newNode error\n");
            return;
        }
        newNode->data = i;
        newNode->next = L->next;
        L->next = newNode;
    }
}

/*
  功能 : 尾部插入
  参数 : L - 头结点
  返回 :
 */
void InsertOneLoopLinkFromTail(OneLink L)
{
    LNode *newNode;
    for(int i=0;i<6;i++)
    {
        newNode = (LNode*)malloc(sizeof(LNode));
        if(newNode==NULL)
        {
            printf("init newNode error\n");
            return;
        }
        newNode->data = i+3;
        newNode->next = NULL;
        if(L->next==L)
        {
            L->next = newNode;
            newNode->next = L;
        } else{
            LNode *cur=L->next;
            //遍历到链表尾部
            while(cur->next!=L)
            {
                cur=cur->next;
            }
            cur->next = newNode;
            newNode->next = L;
        }

    }
}

/*
 功能 : 按序号查找结点值
 参数 : L->链表的头节点, index->位置(从1开始)
 返回 : -1错误，0-没找到，其他-找到的值
 */
int GetValueByIndexOneLoopLink(OneLink L,int index)
{
    if(index<1)
    {
        return -1;
    }
    if(L->next==L)
    {
        return -1;
    }

    LNode *cur=L->next;
    int i = 1;
    while(cur!=L)
    {
        if(index==i)
        {
            return cur->data;
        }
        cur=cur->next;
        i++;
    }

    return 0;
}

/*
 功能 : 按值查找结点
 参数 : L->链表的头节点, value->数值
 返回 : 节点或NULL
 */
OneLink GetIndexByValueOneLoopLink(OneLink L, int value)
{
    LNode *cur = L->next;
    while(cur!=L)
    {
        if(value==cur->data)
        {
            return cur;
        }
        cur=cur->next;
    }
    return NULL;
}

/*
 功能 : 在指定的位序位置插入数据,位序从1开始
 参数 : L->链表的头节点, index->位置,从1开始, data->要插入的数据
 返回 :
 */
void InsertOLLByIndex(OneLink L,int index, int data)
{
    if(index<1)
    {
        return;
    }
    if(L->next==L)
    {
        return;
    }

    LNode *newNode;
    newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data=data;
    newNode->next=NULL;
    int i=1;
    LNode *cur=L;   //从头节点开始，index从第一个节点开始
    while(cur->next!=L)
    {
        if(index==i)
        {
            newNode->next=cur->next;
            cur->next=newNode;
            printf("InsertOLLByIndex success\n");
            return;
        }
        i++;
        cur=cur->next;
    }
    //到这里还没结束，看看index要插在最后一个
    if(index==i)
    {
        cur->next = newNode;
        newNode->next = L;  //连上头节点
    }
}

/*
 功能 : 删除第index个结点
 参数 : L->链表的头节点, index->位置
 返回 :
 */
void DeleteNodeOLL(OneLink L, int index)
{
    if(index<1)
    {
        return;
    }
    int i=1;
    LNode *cur=L;   //从头节点开始，index从第一个节点开始
    LNode *pre; //记录一下前一个节点
    while(cur->next!=L)
    {
        if(index==i)
        {
            cur->next = cur->next->next;
            return;
        }
        i++;
        pre = cur;
        cur=cur->next;
    }
    //到这里还没结束，看看index要否是最后一个
    if(index==i)
    {
        pre->next=L;
    }
}

/*************单循环链表**************/

/*************双循环链表**************/
//头节点不存数据
typedef struct Dnode{
    int data;
    struct Dnode *next;
    struct Dnode *pre;
}Dnode, *DLink;    //强调一个节点用Dnode，强调一个链表用 DLink, DLink为指向结构体Dnode的指针类型，这里DLink与Dnode*等价

/*
  功能 : 初始化单循环链表
  参数 : L - 头结点
  返回 : 链表或者null
 */
DLink InitDoubleLoopList()
{
    DLink D = (Dnode *)malloc(sizeof(Dnode));
    D->data=0;
    D->next = D;
    D->pre = D;
    printf("InitDoubleLoopList success...\n");
    return D;
}

//打印单向循环链表
void printfDoubleLoopLink(DLink D)
{
    if(D->next==D)
    {
        printf("link is null\n");
        return;
    }
    int i = 1;
    Dnode *cur;
    cur = D;  //头结点的下一个
    printf("position:%d, data:%d, next_data:%d, pre_data:%d\n",i-1,D->data,D->next->data,D->pre->data);
    cur = cur->next;
    while(cur!=D)
    {
        printf("position:%d, data:%d, next_data:%d, pre_data:%d\n",i,cur->data,cur->next->data, cur->pre->data);
        cur = cur->next;
        i++;
    }
    printf("list len:%d\n",i-1);
}

/*
  功能 : 头部插入
  参数 : D - 链表头结点
  返回 :
 */
void InsertHeadDoubleLoopList(DLink D)
{
    for(int i=0; i<6; i++)
    {
        Dnode *newNode;
        newNode = (Dnode *)malloc(sizeof(Dnode));
        newNode->data = i+1;
        newNode->next = D->next;
        D->next = newNode;
        newNode->pre = D;
        newNode->next->pre = newNode;
    }
    printfDoubleLoopLink(D);
}

/*
 功能 : 按序号查找结点值
 参数 : D->链表的头节点, index->位置(从1开始)
 返回 : -1错误，0-没找到，其他-找到的值
 */
int FindValueByIndexDL(DLink D,int index)
{
    int res = 0;

    if(D->next==D)
    {
        return res;
    }

    Dnode *cur;
    cur=D->next;
    int i=1;
    while(cur!=D)
    {
        if(i==index)
        {
            return cur->data;
        }
        i++;
        cur = cur->next;
    }

    return res;
}

/*
 功能 : 按值查找节点位置
 参数 : D->链表的头节点, value->数值
 返回 : 位置-从1开始算, -1错误，0-没找到，
 */
int FindIndexByValue(DLink D,int value)
{
    int res = 0;
    if(D->next==D)
    {
        return res;
    }

    Dnode *cur;
    cur = D->next;
    int i=1;
    while(cur!=D)
    {
        if(cur->data==value)
        {
            res = i;
        }
        i++;
        cur = cur->next;
    }

    return res;
}

/*
 功能 : 在指定的位序位置插入数据,位序从1开始
 参数 : D->链表的头节点, index->位置,从1开始, data->要插入的数据
 返回 :
 */
void InsertByIndexDL(DLink D,int index, int data)
{
    if(D->next==D)
    {
        return;
    }

    int i=1;
    Dnode *cur;
    cur = D->next;
    while(cur!=D)
    {
        if(index==i)
        {
            //找到要插入的地方，这里有pre指针，事情简单多了
            Dnode *newNode = (Dnode *)malloc(sizeof(Dnode));
            newNode->data = data;
            cur->pre->next = newNode;
            newNode->next = cur;
            newNode->pre = cur->pre;
            cur->pre = newNode;
            return;
        }
        i++;
        cur=cur->next;
    }
}

/*
 功能 : 删除第index个结点
 参数 : D->链表的头节点, index->位置,从1开始
 返回 :
 */
void DeleteNodeDL(DLink D,int index)
{
    if(D->next==D)
    {
        return;
    }

    int i=1;
    Dnode *cur;
    cur = D->next;
    while(cur!=D)
    {
        if(i==index)
        {
            //删除
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
        }
        i++;
        cur=cur->next;
    }
}

/*************双循环链表**************/

//单链表操作
void OneLinkOp()
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");

    printf("***********GetValueFromIndex***********\n");
    int res = 0;
    res = GetValueFromIndex(L,1);
    printf("found value:%d\n",res);
    printf("***********GetValueFromIndex***********\n");

    printf("***********GetNodeByValue***********\n");
    int value = 4;
    LNode *p;
    p = GetNodeByValue(L,value);
    if(p!=NULL)
    {
        printf("p's value=%d\n",p->data);
    }
    printf("***********GetNodeByValue***********\n");

    printf("***********OneLinkInsert***********\n");
    OneLinkInsert(L,4,33);
    printfOneLink(L);
    printf("***********OneLinkInsert***********\n");

    printf("***********OneLinkInsert***********\n");
    DeleteNode(L,6);
    printfOneLink(L);
    printf("***********OneLinkInsert***********\n");
}

//单循环链表操作
void OneLoopLinkOp()
{
    OneLink L;
    int res = 0;
    printf("***********InitLoopOneLink_start***********\n");
    L=InitLoopOneLink();
    printfOneLoopLink(L);
    printf("***********InitLoopOneLink_end***********\n");

//    printf("***********InsertOneLoopLinkFromHead_start***********\n");
//    InsertOneLoopLinkFromHead(L);
//    printfOneLoopLink(L);
//    printf("***********InsertOneLoopLinkFromHead_end***********\n");

    printf("***********InsertOneLoopLinkFromTail_start***********\n");
    InsertOneLoopLinkFromTail(L);
    printfOneLoopLink(L);
    printf("***********InsertOneLoopLinkFromTail_end***********\n");

    printf("***********GetValueByIndexOneLoopLink_start***********\n");
    int index = 4;
    res = GetValueByIndexOneLoopLink(L,index);
    printf("index is:%d, value=%d\n",index,res);
    printf("***********GetValueByIndexOneLoopLink_end***********\n");

    printf("***********GetIndexByValueOneLoopLink_start***********\n");
    int value=5;
    LNode *r;
    r = GetIndexByValueOneLoopLink(L,value);
    printf("value=%d\n",r->data);
    printf("***********GetIndexByValueOneLoopLink_end***********\n");

    printf("***********InsertOLLByIndex_start***********\n");
    InsertOLLByIndex(L,7,43);
    printfOneLoopLink(L);
    printf("***********InsertOLLByIndex_end***********\n");

    printf("***********DeleteNodeOLL_start***********\n");
    DeleteNodeOLL(L,8);
    printfOneLoopLink(L);
    printf("***********DeleteNodeOLL_end***********\n");
}

//双循环链表操作
void DoubleLoopLinkOp()
{
    DLink D;
    int res;
    printf("***********InitDoubleLoopList_start***********\n");
    D=InitDoubleLoopList();
    InsertHeadDoubleLoopList(D);
    printf("***********InitDoubleLoopList_end***********\n");

    printf("***********FindValueByIndexDL_start***********\n");
    res = FindValueByIndexDL(D,1);
    printf("position 1 value: %d\n",res);
    printf("***********FindValueByIndexDL_end***********\n");

    printf("***********FindIndexByValue_start***********\n");
    res = FindIndexByValue(D,4);
    printf("value 4 position: %d\n",res);
    printf("***********FindIndexByValue_end***********\n");

    printf("***********InsertByIndexDL_start***********\n");
    InsertByIndexDL(D,4,33);
    printfDoubleLoopLink(D);
    printf("***********InsertByIndexDL_end***********\n");

    printf("***********DeleteNodeDL_start***********\n");
    DeleteNodeDL(D,4);
    printfDoubleLoopLink(D);
    printf("***********DeleteNodeDL_end***********\n");
}

/*************例题**************/

void process_func_2(OneLink L,int x)
{
    LNode *cur = L;
    while(cur->next!=NULL)
    {
        if(cur->next->data == x)
        {
            cur->next = cur->next->next;
            //free(cur->next);
        }else{
            cur=cur->next;
        }
    }
    printfOneLink(L);
}
//第二题, 第一题和这个一样，跳过
void func_2()
{
    OneLink L;
    L = InitOneLink();

    LNode *newNode1 = (LNode *)malloc(sizeof(LNode));
    newNode1->data = 1;
    newNode1->next = NULL;
    L->next= newNode1;

    LNode *newNode2 = (LNode *)malloc(sizeof(LNode));
    newNode2->data = 2;
    newNode2->next = NULL;
    newNode1->next= newNode2;

    LNode *newNode3 = (LNode *)malloc(sizeof(LNode));
    newNode3->data = 2;
    newNode3->next = NULL;
    newNode2->next= newNode3;

    LNode *newNode4 = (LNode *)malloc(sizeof(LNode));
    newNode4->data = 4;
    newNode4->next = NULL;
    newNode3->next= newNode4;

    printfOneLink(L);
    process_func_2(L,2);
    free(L);
}

void func_3_process(OneLink L)
{
    if(L->next!=NULL)
    {
        func_3_process(L->next);
    }
    if(L!=NULL)
    {
        printf("data: %d\n",L->data);
    }
}
//第三题
void func_3()
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");

    if(L!=NULL)
    {
        func_3_process(L);
    }
    free(L);
}

//第四题
void func_4()
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");

    LNode *pre = L;         //工作指针的前驱节点
    LNode *p = pre->next;   //工作指针
    LNode *minp = p;        //指向最小节点的指针
    LNode *minpre = pre;    //最小节点的前驱节点
    while(p!=NULL)
    {
        if(p->data<minp->data)
        {
            minp=p;     //保存最小的节点指针
        }
        pre=p;
        p=p->next;
    }
    minpre->next = minp->next;
    free(minp);
    printf("***********over***********\n");
    printfOneLink(L);
    printf("***********over***********\n");
    free(L);
}

//第5题
void func_5()
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");
    //把头节点拿出来，剩余节点用头插法放入链表，就实现了链表逆置

    LNode *cur,*r;  //cur为工作指针, r为cur的后继指针,遍历用
    cur=L->next;
    L->next=NULL;
    while(cur!=NULL)
    {
        //把当前节点插入链表头部
        r=cur->next;
        cur->next=L->next;
        L->next = cur;
        cur=r;
    }
    printf("***********over***********\n");
    printfOneLink(L);
    printf("***********over***********\n");
    free(L);
}

//第6题
void func_6()
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");

    //先构建只包含一个数据节点的有序单链表
    LNode *p=L->next, *pre;    // p是工作指针, pre 是 p 的前驱节点
    LNode *r=p->next;   //保存p后面链表的数据，不要段了
    p->next = NULL;     //构建包含节点p的有序表 到这里 L->next = p, p后面就没有节点了
    //让 p 指向保存住的 r 后面的节点(第三个节点)，下面第一轮就是第二个节点和第三个节点比较（因头节点不存数据）
    p=r;
    while(p!=NULL)
    {
        r=p->next;  //保存p后面链表的数据，不要段了
        pre=L;
        //p为较大的节点，pre是较小的节点
        while(pre->next!=NULL && pre->next->data < p->data)
        {
            pre=pre->next;  //pre是较小的节点
        }
        // p节点较大，往pre后面放
        p->next = pre->next;
        pre->next=p;    //pre指向前面保存住的链表

        p=r;    //对比完一次，指针往后移动
    }

    printf("***********over***********\n");
    printfOneLink(L);
    printf("***********over***********\n");
    free(L);
}

//第7题 介于bData - eData之间
void func_7(int bData,int eData)
{
    OneLink L;
    L = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L);
    printf("***********InsertFromTail***********\n");

    LNode *cur = L->next;
    LNode *pre = L;
    while(cur!=NULL)
    {
        if(cur->data > bData && cur->data < eData)
        {
            pre->next = cur->next;
            cur = pre->next;
        } else{
            pre=pre->next;
            cur=cur->next;
        }
    }
    printf("***********over***********\n");
    printfOneLink(L);
    printf("***********over***********\n");

    free(L);
}

//第8题
void func_8()
{
    OneLink L1,L2;
    L1 = InitOneLink();
    L2 = InitOneLink();
    printf("***********InsertFromTail***********\n");
    InsertFromTail(L1);
    InsertFromHead(L2);
    printf("***********InsertFromTail***********\n");

    free(L1);
    free(L2);
}

/*************例题**************/


int main() {
    printf("let's go!\n");

    func_8(3,6);

    return 0;
}