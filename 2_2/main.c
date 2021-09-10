
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//链表的线性表示
/************************静态方式************************/
#define MaxSize 10
//静态顺序表结构
typedef struct {
    int data[MaxSize];  //顺序表长度
    int length;         //当前顺序表大小
}SqList;
//初始化 静态顺序表
void InitList(SqList *L)
{
    //清空脏数据
    for(int i=0;i<MaxSize;i++)
    {
        L->data[i] = 0;
    }
    L->length = 0;
}

//通过元素位置（从1开始）获取值, return -1:查询失败
int sGetValueByIndex(SqList *L,int index)
{
    if(index > L->length || index < 1)
    {
        return -1;
    }
    return L->data[index-1];
}

//通过元素值返回位置（从1开始）
int sGetIndexByData(SqList *L,int data)
{
    for(int i=0; i<L->length;i++)
    {
        if(L->data[i]==data){
            return i+1;
        }
    }
    return -1;
}

//插入数据 在第index个位序(从1开始算) 插入数据data
//return -1:失败，0-成功
int sListInsert(SqList *L,int index,int data)
{
    //判断index的合法性
    if (index > L->length+1 || index < 1)
    {
        return -1;
    }
    //判断静态顺序表是否已经满了
    if (L->length >= MaxSize)
    {
        return -1;
    }
    for(int i=L->length;i>=index;i--)
    {
        L->data[i] = L->data[i-1];
    }
    L->data[index-1] = data;
    L->length++;

    return 0;
}

//删除指定位置index(从1开始算)的值
int sDelete(SqList *L,int index)
{
    //判断index的合法性
    if(index > L->length || index <1)
    {
        return -1;
    }
    //删除,index后面的每一位往前诺
    for(int i=index; i<L->length;i++)
    {
        L->data[i-1] = L->data[i];
    }
    L->data[L->length-1] = 0;       //最后一位已经忘前挪了,或者要删除的就是最后一位,置空
    L->length--;
    return 0;
}

void printfList(SqList *L)
{
    printf("List:");
    for(int i=0;i<L->length;i++){
        printf(" %d",L->data[i]);
    }
    printf("\n");
    printf("length:%d\n",L->length);
}
void staticList()
{
    SqList L;
    InitList(&L);   //初始化静态数组

    //增
    sListInsert(&L,1,1);
    sListInsert(&L,2,2);
    sListInsert(&L,3,3);
    sListInsert(&L,4,4);
    sListInsert(&L,2,132);

    printf("List:");
    printfList(&L);

    int value = sGetValueByIndex(&L,2);
    printf("index-%d,value:%d\n",2,value);

    int index = sGetIndexByData(&L,132);
    printf("value-%d,index:%d\n",132,index);

    sDelete(&L,3);
    printf("delete\n");
    printfList(&L);
}

/************************静态方式************************/

/************************动态方式************************/
#define InitSize 10         //初始化是默认长度
//动态顺序表结构
typedef struct{
    int *data;      //指向动态数组的指针,指向头元素
    int Maxsize;    //顺序表最大容量
    int length;     //顺序表当前容量
}SeqList;
//初始化 动态数组
void InitSeqList(SeqList *L)
{
    L->data = (int *)malloc(InitSize*sizeof(int));
    L->length = 0;
    L->Maxsize = InitSize;
}

//动态数组增加长度
void seqIncrease(SeqList *L,int len)
{
    int *p = L->data;   //存储原来的数据
    //申请新的空间,把最大容量加大
    L->data = (int *)malloc((L->Maxsize+len)*sizeof(int));
    //把原来数据拷贝到新的空间,有内存开销
    for(int i=0;i<L->length;i++){
        L->data[i] = p[i];
    }
    L->Maxsize = L->Maxsize+len;
    free(p);
}

//动态顺序表插入  index从1开始算
void seqInsert(SeqList *L,int index,int data)
{
    if(index > L->length+1 || index<1)
    {
        return;
    }
    if(L->length>=L->Maxsize)
    {
        seqIncrease(L,L->Maxsize);
    }

    for(int i=L->length;i>=index;i--)
    {
        L->data[i] = L->data[i-1];
    }
    L->data[index-1] = data;
    L->length++;
}

void printfSeqList(SeqList *L)
{
    printf("List:");
    for(int i=0;i<L->length;i++){
        printf(" %d",L->data[i]);
    }
    printf("\n");
    printf("length:%d\n",L->length);
}

//动态顺序表入口
void dynamic()
{
    SeqList L;
    InitSeqList(&L);    //初始化动态数组

    for(int i=0;i<L.length;i++){
        printf("sss:%d\n",L.data[i]);
    }
    printf("Maxsize: %d, length:%d\n",L.Maxsize,L.length);
    seqIncrease(&L,5);
    printf("Maxsize: %d, length:%d\n",L.Maxsize,L.length);
}
/************************动态方式************************/

/************************题目************************/

//第一题
int deleteMin_1(SqList *L)
{
    if(L->length == 0)
    {
        printf("list is null");
        return -1;
    }
    int min = L->data[0];
    int index = 0;  //要删除的值的位置
    for(int i = 0;i<L->length;i++)
    {
        if(L->data[i]<min)
        {
            min = L->data[i];
            index = i;
        }
    }
    L->data[index] = L->data[L->length-1];
    L->length--;
    return min;
}

//第二题
void reverse_2(SqList *L)
{
    if(L->length == 0)
    {
        printf("list is null");
        return;
    }
    int temp = 0;
    for(int i=0;i<L->length/2;i++)
    {
        temp = L->data[i];
        L->data[i] = L->data[L->length-i-1];
        L->data[L->length-i-1] = temp;
    }
}

//第三题
void deleteData_3(SqList *L,int x)
{
    if(L->length==0)
    {
        printf("list is null");
        return;
    }
    int k = 0;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i]!=x)
        {
            //不是要删除的值，保留
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//第4题
void deleteBetween_4(SqList *L,int s, int t)
{
    if(L->length == 0 || s>=t)
    {
        printf("list is null or s>=t");
        return;
    }
    int k=0;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i]<=s || L->data[i]>=t)
        {
            //删除的范围之外,保留
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//第5题
void deleteBetween_5(SqList *L,int s,int t)
{
    if(L->length == 0 || s>=t)
    {
        printf("list is null or s>=t");
        return;
    }
    int k=0;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i]<s || L->data[i]>t)
        {
            //删除的范围之外,保留
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//第6题
void deleteRepeat_6(SqList *L)
{
    if(L->length == 0)
    {
        printf("list is null");
        return;
    }
    int k = 0;
    for(int i=0;i<L->length;i++)
    {
        if(L->data[i] != L->data[i+1])
        {
            //不重复,保存
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

//第7题
void mergeSeqList(SeqList A, SeqList B, SeqList *C)
{
    //长度判断, 静态顺序表需要,这里是动态顺序表，所以不需要
    int i=0,j=0,k=0;
    while(i<A.length && j<B.length)
    {
        //两两比较，小的存入结果表
        if(A.data[i]<=B.data[j])
        {
            C->data[k]=A.data[i];
            i++;
            k++;
        } else{
            C->data[k]=B.data[j];
            j++;
            k++;
        }
    }
    //把剩余的存入表
    while(i<A.length)
    {
        C->data[k] = A.data[i];
        i++;
        k++;
    }
    while(j<B.length)
    {
        C->data[k] = B.data[j];
        j++;
        k++;
    }
    C->length = k;
}

//第8题  n-顺序表an的长度，m=顺序表bm的长度,len-原来数组的长度, newArray[]-转换之后的数组
void reverse_8(int old[],int n, int m,int len)
{
    int newArray[len],arrN[n],arrM[m];

    //把原来数组分成两个数组，分别存放an和bm
    for(int i =0;i<len;i++)
    {
        if(i<n)
        {
            arrN[i] = old[i];
        } else{
            arrM[i-n] = old[i]; //第一次当i==n时，i-n=0
        }
    }

    for(int j=0;j<len;j++)
    {
        if(j<m)
        {
            //先放bm,完了再放an
            newArray[j] = arrM[j];
        } else{
            newArray[j] = arrN[j-m];    //第一次当j==m时，j-m=0
        }
    }

    printf("newArray:");
    for (int k = 0; k < len; ++k) {
        printf("%d ",newArray[k]);
    }
    printf("\n");
}

//第9题   data就是要查找的元素,找不到插入
void func9(int arr[],int len,int data)
{
    //查找,折半查找，最快
    int low=0;
    int mid=0;
    int isFound = 0;    //默认没找到
    int high=len-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(arr[mid]==data)
        {
            printf("found number:%d, index is:%d\n",arr[mid],mid);
            //判断是否是最后一个元素
            if(low==high && high!=0)
            {
                //最后一个元素就不用交换了
            } else{
                //不是最后一个,与后面一个元素交换
                int tmp=0;
                tmp = arr[mid];
                arr[mid] = arr[mid+1];
                arr[mid+1] = tmp;
            }
            isFound = 1;
            break;
        }else if(arr[mid]<data)
        {
            low = mid+1;
        }else if(arr[mid]>data)
        {
            high = mid-1;
        }
    }
    if(isFound==0)  //没找到
    {
        printf("cant found\n");
    }

    printf("newArray:");
    for (int k = 0; k < len; ++k) {
        printf("%d ",arr[k]);
    }
    printf("\n");
}

/*
第10题 arrlen是数组长度，从1开始算，p是分界位也是从1开始算
 可看成数组ab逆转为ba的原理, 例如原数组 [5,2,8,6,3,9], 分界点是3，也就是3-1=2，就是元素8
 数组 a=[5,2], 数组 b=[8,6,3,9]
 先把ab转为 a^-1b = [2,5,8,6,3,9]
 再把a^-1b 转为 a^-1b^-1 = [2,5,9,3,6,8]
 最后a^-1b^-1 转为 (a^-1b^-1)^-1 = [9,3,6,8,2,5]
 时间复杂度：O(n), 空间复杂度: O(1)
 */
void func_10_reverse(int R[],int from,int to)
{
    //from,to下标从0开始
    int i,temp;
    for(i=0;i<=(to-from)/2;i++)
    {
        temp = R[from+i];
        R[from+i] = R[to-i];
        R[to-i] = temp;
    }
}
void func_10(int arr[],int len,int p)
{
    printf("oldArray:");
    for (int k = 0; k < len; ++k) {
        printf("%d ",arr[k]);
    }
    printf("\n");

    func_10_reverse(arr,0,p-1);     //ab转为 a^-1b
    func_10_reverse(arr,p,len-1);   //a^-1b 转为 a^-1b^-1
    func_10_reverse(arr,0,len-1);   //a^-1b^-1 转为 (a^-1b^-1)^-1

    printf("newArray:");
    for (int k = 0; k < len; ++k) {
        printf("%d ",arr[k]);
    }
    printf("\n");
}

/*第11题
 分别求两个升序序列A,B的中位数,设为a,b，然后：
 1.若 a=b，则a或者b即为中位数, done.
 2.若 a<b, 则舍弃序列A中较小的一半,同时舍弃序列B中较大的一半，两次舍弃的长度相等.
 3.若 a>b, 则舍弃序列A中较大的一半,同时舍弃序列B中较小的一半，两次舍弃的长度相等.
 在保留的两个升序序列中，重复1,2,3, 直到两个序列中均只含一个元素为止，较小者即为所求中位数.
 算法时间复杂度为 O(log2N), 空间复杂度为 O(1)
*/
int func_11_searchMiddle(int A[],int B[],int len)
{
    int res=0;
    int sA=0,sB=0;  //序列A,B的首位
    int dA=len-1,dB=len-1;  //序列A,B的末位
    int mA,mB;  //序列A,B的中位
    while(sA!=dA || sB!=dB)
    {
        //求中位
        mA = (sA+dA)/2;
        mB = (sB+dB)/2;
        if(A[mA]==B[mB])
        {
            res = A[mA];
        }
        if(A[mA]<B[mB])
        {
            if((sA+dA)%2==0)    //若元素个数为奇数
            {
                sA = mA;    //舍弃A序列中位之前的数，保留中位
                dB = mB;    //舍弃B序列中位之后的数，保留中位
            } else{          //若元素个数为偶数
                sA = mA+1;  //舍弃A序列中位和中位之前的数
                dB = mB;    //舍弃B序列中位之后的数，保留中位
            }
        } else{
            if((sB+dB)%2==0)     //若元素个数为奇数
            {
                sB = mB;    //舍弃B序列中位之前的数，保留中位
                dA = mA;    //舍弃A序列中位之后的数，保留中位
            } else{
                sB = mB+1;  //舍弃B序列中位和中位之前的数
                dB = mB;    //舍弃A序列中位之后的数，保留中位
            }
        }
    }
    res = A[sA]<B[sB] ? A[sA]:B[sB];
    return res;
}

/* 第12题
 * 思路：从前往后扫描数组元素，标记出一个可能成为主元素的元素c，然后计数，确认num是否是主元素
 * 1. 扫描数组，把第一个遇到的整数标记为主元素c, 计数器num标记为1, 如果下一个数还是c,num加1, 如果不是，num减1
 * 当num为0的时候，把下一个整数标记为主元素c,计数器num重新标记为1, 从当前位置开始重复上述过程，直到扫描完整个数组.
 * 2. 判断 主元素c的出现次数 count 是否大于数组长度(从1开始算) len/2, 大于就是主元素返回之，否则就不是，返回-1
 */
int func_12(int arr[],int len)
{
    int res = 0, c=0, num=0, count=0;
    c=arr[0];
    num=1;
    for(int i=1;i<len;i++)
    {
        if(arr[i]==c)
        {
            num++;
        } else{
            if(num>0)
            {
                num--;
            } else{
                c=arr[i];
                num=1;
            }
        }
    }
    //计算主元素出现的次数
    if(num>0)
    {
        for(int i=0;i<len;i++)
        {
            if(c == arr[i])
            {
                count++;
            }
        }
    }
    if(count > len/2)
    {
        res = c;
    } else{
        res = -1;
    }

    return res;
}

/* 第13题
 *
 */
int func_13(int arr[],int len)
{
    int i,*B;    //标记数组
    B=(int *)malloc(sizeof(int)*len);   //分配空间
    memset(B,0,sizeof(int)*len);
    for(i=0;i<len;i++)
    {
        if(arr[i]>0 && arr[i]<=len)
        {
            B[arr[i]-1] = 1;
        }
    }
    for(i=0;i<len;i++)
    {
        if(B[i]==0)
        {
            break;
        }
    }
    return i+1;
}

//题目调用
void test()
{

//    SqList L;
//    InitList(&L);   //初始化静态数组
//
//    //增
//    sListInsert(&L,1,2);
//    sListInsert(&L,2,3);
//    sListInsert(&L,3,4);
//    sListInsert(&L,4,5);
//    sListInsert(&L,5,6);
//    sListInsert(&L,6,6);
//    sListInsert(&L,7,7);
//    printf("***********init***********\n");
//    printfList(&L);
//    printf("***********init***********\n");

//    SeqList L1;
//    SeqList L2;
//    InitSeqList(&L1);   //初始化动态顺序表
//    InitSeqList(&L2);
//
//    //动态顺序表增加
//    seqInsert(&L1,1,1);
//    seqInsert(&L1,2,2);
//    seqInsert(&L1,3,3);
//    seqInsert(&L1,4,4);
//    seqInsert(&L1,5,5);
//    seqInsert(&L1,6,6);
//    seqInsert(&L1,7,9);
//    seqInsert(&L1,8,10);
//    seqInsert(&L1,9,15);
//    seqInsert(&L1,10,18);
//    seqInsert(&L1,11,22);
//    seqInsert(&L1,12,27);
//    seqInsert(&L1,13,33);
//    printf("***********init L1***********\n");
//    printfSeqList(&L1);
//    printf("***********init L1***********\n");
//
//    seqInsert(&L2,1,4);
//    seqInsert(&L2,2,7);
//    seqInsert(&L2,3,12);
//    seqInsert(&L2,4,23);
//    printf("***********init L2***********\n");
//    printfSeqList(&L2);
//    printf("***********init L2***********\n");

//    printf("***********test_1***********\n");
//    int res = 0;
//    res = deleteMin_1(&L);
//    printf("delete data is:%d\n",res);
//    printfList(&L);
//    printf("***********test_1***********\n");

//    printf("***********test_2***********\n");
//    reverse_2(&L);
//    printfList(&L);
//    printf("***********test_2***********\n");

//    printf("***********test_3***********\n");
//    deleteData_3(&L,7);
//    printfList(&L);
//    printf("***********test_3***********\n");

//    printf("***********test_4***********\n");
//    deleteBetween_4(&L,1,9);
//    printfList(&L);
//    printf("***********test_4***********\n");

//    printf("***********test_5***********\n");
//    deleteBetween_5(&L,4,8);
//    printfList(&L);
//    printf("***********test_5***********\n");

//    printf("***********test_6***********\n");
//    deleteRepeat_6(&L);
//    printfList(&L);
//    printf("***********test_6***********\n");

//    printf("***********test_7***********\n");
//    SeqList L3;
//    InitSeqList(&L3);
//    mergeSeqList(L1,L2,&L3);
//    printfSeqList(&L3);
//    printf("***********test_7***********\n");

//    printf("***********test_8***********\n");
//    int array[7] = {1,2,3,4,5,6,7,8,9};
//    reverse_8(array,3,6,9);
//    printf("***********test_8***********\n");

//    printf("***********test_9***********\n");
//    int array[8] = {1,3,4,6,7,9,10,15};
//    func9(array,8,1);       //插入功能TODO
//    printf("***********test_9***********\n");

//    printf("***********test_10***********\n");
//    int array[8] = {1,3,4,6,7,9,10,15};
//    func_10(array,8,4);       //插入功能TODO
//    printf("***********test_10***********\n");

//    printf("***********test_11***********\n");
//    int A[6]= {2,4,6,8,20,22};
//    int B[6]= {11,13,15,17,19,20};
//    int res = func_11_searchMiddle(A,B,6);
//    printf("res:%d\n",res);
//    printf("***********test_11***********\n");

//    printf("***********test_12***********\n");
//    int A[6]= {0,1,1,2,1,1};
//    int res = func_12(A,6);
//    printf("res:%d\n",res);
//    printf("***********test_12***********\n");

    printf("***********test_13***********\n");
    int A[3]= {6,5,9};
    int res = func_13(A,3);
    printf("res:%d\n",res);
    printf("***********test_13***********\n");

}
/************************题目************************/



int main() {
    //staticList();
    //dynamic();
    test();
    return 0;
}