#include <stdio.h>

//队列：
// 顺序方式
// 链式方式(就是只可以从表头删除,表尾插入的链表,链表加入头指针和尾指针,略)
// 双端队列 可以从头和尾进行插入和删除

// 1.D   2.B   3.D  4.A*B  5.C*D  6.C  7.B  8.B  9.?*C
// 10.A  11.A*B  12.A  13.A  14.D  15.D  16.B*A  17.?*C  18.C

/***********队列顺序实现(普通方式)**********/
#define MaxSize 10  //队列元素最大个数
typedef struct {
    int data[MaxSize];  //队列数据
    int front,rear;     //队头位置和队尾的后一位 (从0开始算)
    int length;         //队列元素个数
} SqQueue;

//初始化
void InitSqQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;     //头尾都在一起
    //所有元素都先设置为0
    for(int i=0;i<MaxSize; i++)
    {
        Q->data[i]=0;
    }
    Q->length=0;
}

void printQueue(SqQueue Q)
{
    if(Q.rear == Q.front)
    {
        return;
    }

    for(int i=0;i<MaxSize; i++)
    {
        if(Q.data[i]==0)
        {
            continue;   //默认0是空值
        }
        printf("Queue[%d]: %d\n",i,Q.data[i]);
    }
    printf("Queue front position:%d, data:%d\n",Q.front,Q.data[Q.front]);
    printf("Queue rear position:%d, data:%d\n",Q.rear,Q.data[Q.rear]);
}

//入队  循环队列的设计中，最后一个元素是要牺牲掉的，不能存储
void EnQueue(SqQueue *Q, int data)
{
    //Q->rear是位置下标，一直在最后一位的后面，+1取余看看是否和头位置相同
    if((Q->rear+1)%MaxSize==Q->front)
    {
        return;     //队列已满
    }
    Q->data[Q->rear] = data;
    Q->rear = (Q->rear+1)%MaxSize;    //循环队列，队尾都在最后一个元素的后一位，方便后面插入
    Q->length++;
}

//出队
int DeQueue(SqQueue *Q)
{
    int res;
    if(Q->front == Q->rear)
    {
        return -1; //队列为空
    }
    res = Q->data[Q->front];
    Q->data[Q->front] = 0;
    Q->front = (Q->front+1)%MaxSize;    //头位置循环往后移动
    Q->length--;
    return res;
}

void DoSqQueue()
{
    SqQueue Q;  //声明一个队列
    InitSqQueue(&Q);
    int res = 0;
    printf("*************EnQueue_start**********\n");
    EnQueue(&Q,5);
    EnQueue(&Q,2);
    EnQueue(&Q,8);
    EnQueue(&Q,43);
    EnQueue(&Q,22);
    EnQueue(&Q,17);
    EnQueue(&Q,3);
    EnQueue(&Q,88);
    EnQueue(&Q,32);
    printQueue(Q);
    printf("*************EnQueue_end**********\n");

    printf("*************DeQueue_start**********\n");
    res = DeQueue(&Q);
    printf("Dequeue data:%d\n",res);
    res = DeQueue(&Q);
    printf("Dequeue data:%d\n",res);
    res = DeQueue(&Q);
    printf("Dequeue data:%d\n",res);
    res = DeQueue(&Q);
    printf("Dequeue data:%d\n",res);
    printQueue(Q);
    printf("*************DeQueue_end**********\n");

    printf("*************EnQueue_again_start**********\n");
    EnQueue(&Q,233);
    EnQueue(&Q,666);
    EnQueue(&Q,9981);
    printQueue(Q);
    printf("*************EnQueue_again_end**********\n");
}
/***********队列顺序实现**********/

/***********队列顺序实现(tag方式)**********/
//只有删除操作，才可能使队列为空
//只有插入操作，才可能使队列变满
typedef struct {
    int data[MaxSize];
    int front,rear;
    int tag;        //最近进行 0删除/ 1插入的操作
} SqQueueTag;

void printQueueTag(SqQueueTag Q)
{
    //判断队列是否是空的
    if(Q.rear == Q.front && Q.tag==0)
    {
        printf("queue is empty, cant printf\n");
        return;
    }

    for(int i=0;i<MaxSize; i++)
    {
        if(Q.data[i]==0)
        {
            continue;   //默认0是空值
        }
        printf("Queue[%d]: %d\n",i,Q.data[i]);
    }
    printf("Queue front position:%d, data:%d\n",Q.front,Q.data[Q.front]);
    printf("Queue rear position:%d, data:%d\n",Q.rear,Q.data[Q.rear]);
}

//初始化
void InitSqQueueTag(SqQueueTag *Q)
{
    Q->front = Q->rear = 0;     //头尾都在一起
    //所有元素都先设置为0
    for(int i=0;i<MaxSize; i++)
    {
        Q->data[i]=0;
    }
    Q->tag=0;
}

//入队
void EnQueueTag(SqQueueTag *Q,int data)
{
    //判断队列是否已经满了, 只有插入操作，才可能使队列变满
    if(Q->rear==Q->front && Q->tag==1)
    {
        printf("queue is full\n");
        return;
    }
    Q->data[Q->rear] = data;
    Q->rear = (Q->rear+1)%MaxSize;
    Q->tag = 1;
}

//出队
void DeQueueTag(SqQueueTag *Q)
{
    //判断队列是否为空,只有删除操作,才可能使队列为空
    if(Q->rear==Q->front && Q->tag==0)
    {
        printf("queue is empty\n");
        return;
    }
    Q->data[Q->front] = 0;
    Q->front = (Q->front+1)%MaxSize;
    Q->tag = 0;
}

void DoSqQueueTag()
{
    SqQueueTag Q;
    InitSqQueueTag(&Q);

    printf("*************EnQueueTag_start**********\n");
    EnQueueTag(&Q,5);
    EnQueueTag(&Q,2);
    EnQueueTag(&Q,8);
    EnQueueTag(&Q,43);
    EnQueueTag(&Q,22);
    EnQueueTag(&Q,17);
    EnQueueTag(&Q,3);
    EnQueueTag(&Q,88);
    EnQueueTag(&Q,32);
    EnQueueTag(&Q,37);
    EnQueueTag(&Q,72);
    printQueueTag(Q);
    printf("*************EnQueueTag_end**********\n");

    printf("*************DeQueueTag_start**********\n");
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    DeQueueTag(&Q);
    printQueueTag(Q);
    printf("*************DeQueueTag_end**********\n");
}

/***********队列顺序实现(tag方式)**********/

int main() {
    DoSqQueueTag();
    return 0;
}



