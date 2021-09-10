#include <stdio.h>

/****************直接插入排序start*****************/
//直接插入排序,将元素插入到已排好序的序列中  6,2,12,4,9,7
void InsertSort(int A[],int n)
{
    int i,j,temp;
    for(i=1;i<n;i++)    //从第一个开始往前比较
    {
        if(A[i]<A[i-1]) //如果当前元素比前一个大
        {
            temp = A[i];    //临时保存当前元素
            j=i-1;
            //从当前元素的前一个元素开始，一直往前比较，如果比当前元素大，就往前移动一位
            for(; j>=0 && A[j]>temp; )
            {
                A[j+1] = A[j];
                j--;    //下标往前挪动s
            }
            //到这里，j的位置是就是比当前元素小的元素
            // j=-1 : 当前元素是最小的，放到第0个位置
            // j>=0 : 当前元素不是最小的，放在比它小的元素后面
            A[j+1] = temp;
        }
    }

    for(int k=0;k<n;k++)
    {
        printf(" %d",A[k]);
    }
    printf("\n");
}

//再写一遍
void testInsert(int A[],int len)
{
    int i,j,temp;
    for(i=1;i<len;i++)
    {
        if(A[i-1]>A[i])
        {
            temp = A[i];
            j=i-1;
            for(;j>=0 && A[j]>temp;)
            {
                A[j+1] = A[j];
                j--;
            }
            A[j+1] = temp;
        }
    }

    for(int k=0;k<len;k++)
    {
        printf(" %d",A[k]);
    }
    printf("\n");
}
/****************直接插入排序end*****************/

/****************折半插入排序start*****************/
//第0个元素是哨兵,用于存放要排序的元素
void InsertSortHalf(int A[],int len)
{
    int i,j,high,low,mid;
    for(i=2;i<len;i++) //第0个元素是哨兵,从第2个元素开始往前比较
    {
        A[0] = A[i];    //存放要排序的元素
        low=1;high=i-1; //设置折半查找的范围
        while(low<=high)    //折半查找，i之前的数据都应该是有序的
        {
            mid=(low+high)/2;
            if(A[mid]>A[0])
            {
                high = mid-1;
            } else{
                // A[mid]==A[0] low也要在mid后面一位，保证数据稳定性
                low = mid+1;
            }
        }
        //找到了要插入的位置 high+1, 把该位置之前的元素到位置i的元素都后移一位
        for(j=i-1;j>=high+1;)
        {
            A[j+1] = A[j];
            j--;
        }
        A[high+1] = A[0];   //插进去..
        for(int k=0;k<len;k++)
        {
            printf(" %d",A[k]);
        }
        printf("\n");
    }
    A[0] = 0;  //最后要给哨兵数据归零
    for(int k=0;k<len;k++)
    {
        printf(" %d",A[k]);
    }
    printf("\n");
}
/****************折半插入排序end*****************/


/****************希尔排序start*****************/
void ShellSort(int A[],int len)
{
    int d,i,j;  //d是增量
    //A[0]进行元素暂存
    for(d=len/2; d>=1; d=d/2)   //每一次d都是自身除2
    {
        //当d==1时候，就是全部进行直接插入排序，但是这个时候数组已经相对有序，所以时间复杂度低
        for(i=d+1; i<len;i++) //d+1的下标是子表的末尾元素
        {
            if(A[i] < A[i-d])   //i-d的下标是子表的开头元素
            {
                //只有后面小于前面，才需要移动
                A[0]=A[i];  //保存要排序的元素
                //遍历子表，进行移动
                //A[0]<A[j]要排序的元素小于当前元素，把当前元素移动到子表的末尾
                for(j=i-d; j>0 && A[0]<A[j];)
                {
                    A[j+d] = A[j];
                    j-=d;
                }
                A[j+d]=A[0];    //注意，这里j的位置是负数了，j+d为当前子表的开头元素
            }
        }
    }
    A[0] = 0;  //最后要给元素暂存位置的数据归零
    for(int k=0;k<len;k++)
    {
        printf(" %d",A[k]);
    }
    printf("\n");
}
/****************希尔排序end*****************/

int main() {
    int A[7] = {0,6,4,2,14,3,33};
    ShellSort(A,7);
    return 0;
}
