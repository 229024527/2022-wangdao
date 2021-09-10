#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10

//栈：顺序方式和链式方式

/******顺序表（数组）存储*****/
typedef struct{
    int data[MaxSize];  //静态数组存放栈中元素
    int top;    //栈顶游标,就是数组下标，从0开始算
}SqStack;

//初始化化顺序栈
SqStack InitSqStack(){
    SqStack s;  //分配空间
    s.top = -1; //刚开始没有数据，为-1
    return s;
}

void printfSqStack(SqStack *s)
{
    if(s->top==-1)
    {
        return;
    }
    int i=s->top;
    while(i>=0)
    {
        printf("stack data[%d] = %d\n",i,s->data[i]);
        i--;
    }
    printf("stack top is: %d\n",s->data[s->top]);
}

//入栈
void PushSqStack(SqStack *s, int data)
{
    if(s->top == MaxSize-1)
    {
        //栈满了
        return;
    }
    s->top++;
    s->data[s->top] = data;
}

//出栈
int PopSqStack(SqStack *s)
{
    int res;
    if(s->top==-1)
    {
        return -2;
    }
    res = s->data[s->top];
    s->top--;
    return res;
}

//读取栈顶数据
int GetSqStackTop(SqStack *s)
{
    int res;
    if(s->top==-1)
    {
        return -2;
    }
    res = s->data[s->top];
    return res;
}

void DoSqStack()
{
    SqStack s;  //声明顺序栈，分配空间
    int res;
    s = InitSqStack();
    printf("after init SqStack.top = %d\n",s.top);

    printf("***********PushSqStack_start***********\n");
    PushSqStack(&s,2);
    PushSqStack(&s,35);
    PushSqStack(&s,8);
    PushSqStack(&s,3);
    PushSqStack(&s,26);
    PushSqStack(&s,12);
    printfSqStack(&s);
    printf("***********PushSqStack_end***********\n");

    printf("***********PopSqStack_start***********\n");

    res = PopSqStack(&s);
    printf("stack top:%d\n",res);
    printf("***********PopSqStack_end***********\n");

    printf("***********PopSqStack_start***********\n");
    res = PopSqStack(&s);
    printf("stack top:%d\n",res);
    printf("***********PopSqStack_end***********\n");

    printf("***********GetSqStackTop_start***********\n");
    res = GetSqStackTop(&s);
    printf("read stack top:%d\n",res);
    printf("***********GetSqStackTop_end***********\n");

    printfSqStack(&s);

}
/******顺序表（数组）存储*****/

/**************栈的链式存储***************/
typedef struct LinkNode{
    int data;       //数据
    struct LinkNode *next;  //指针域
}LinkNode,*ListStack;

//初始化链式栈,头节点不存数据
ListStack InitListStack()
{
    ListStack L;
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->data = 0;
    L->next = NULL;

    return L;
}

/*
  功能 : 打印链表,包含头结点
  参数 : L - 头结点
  返回 :
 */
void printfLinkNode(ListStack L)
{
    if(L->next==NULL)
    {
        printf("link is null\n");
        return;
    }
    int i = 1;
    LinkNode *cur;
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

//入栈
void PushLinkNode(ListStack L,int data)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
    newNode->data = data;
    newNode->next = L->next;
    L->next = newNode;
}

//出栈
void PopListStack(ListStack L)
{
    if(L->next==NULL)
    {
        return;
    }
    LinkNode *cur = L->next;
    L->next = cur->next;
    free(cur);
}

//读取栈顶数据
int GetListStackTop(ListStack L)
{
   int res = 0;

   if(L->next==NULL)
   {
       res = -1;
   } else{
       res = L->next->data;
   }

   return res;

}

void DoListStack()
{
    ListStack L;
    L=InitListStack();

    printf("***********PushLinkNode_start***********\n");
    PushLinkNode(L,23);
    PushLinkNode(L,36);
    PushLinkNode(L,4);
    PushLinkNode(L,16);
    PushLinkNode(L,12);
    PushLinkNode(L,9983);
    printfLinkNode(L);
    printf("***********PushLinkNode_end***********\n");

    printf("***********PopListStack_start***********\n");
    PopListStack(L);
    printfLinkNode(L);
    printf("***********PopListStack_end***********\n");

    printf("***********PopListStack_start***********\n");
    PopListStack(L);
    printfLinkNode(L);
    printf("***********PopListStack_end***********\n");

    int res;
    res = GetListStackTop(L);
    printf("stack top data: %d\n",res);

    free(L);
}
/**************栈的链式存储***************/

int main() {
    DoListStack();
    return 0;
}