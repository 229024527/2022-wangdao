#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//栈和队列的应用

#define MaxSize 20

/******顺序表（数组）存储*****/
typedef struct{
    char data[MaxSize];  //静态数组存放栈中元素
    int top;    //栈顶游标,就是数组下标，从0开始算
} SqStack;

//初始化化顺序栈
SqStack InitSqStack()
{
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
        printf("stack data[%d] = %c\n",i,s->data[i]);
        i--;
    }
    printf("stack top is: %c\n",s->data[s->top]);
}

//入栈
void PushSqStack(SqStack *s, char data)
{
    if(s->top == MaxSize-1)
    {
        //栈满了
        return;
    }
    s->top++;
    s->data[s->top] = data;
}

//出栈  返回'k' 表示栈空
char PopSqStack(SqStack *s)
{
    char res;
    if(s->top==-1)
    {
        res = 'k';
        return res;
    }
    res = s->data[s->top];  //拿到要出栈的数据
    s->top--;
    return res;
}

//读取栈顶数据
char GetSqStackTop(SqStack *s)
{
    char res;
    if(s->top==-1)
    {
        return 'k';
    }
    res = s->data[s->top];
    return res;
}
/******顺序表（数组）存储*****/

/**********栈在括号中的应用**********/
//1.遍历扫描括号
//2.遇到左括号入栈
//3.遇到右括号出栈，与右括号配对
//4.配对不成功，报错
//5.遇到右括号，栈是空的，说明这个右括号是单身，报错
//6.括号已经扫描完了，栈不是空的，说明有单身的左括号，报错

//0:成功，-1:失败
int bracketCheck(char str[],int length)
{
    int res = 0;
    char resChar;

    SqStack s;  //声明顺序栈，分配空间
    s = InitSqStack();
    //printf("after init SqStack.top = %d\n",s.top);

    //1.遍历扫描括号
    for(int i=0;i<length;i++)
    {
        if(str[i]=='(' || str[i]=='[' || str[i]=='{')
        {
            //2.遇到左括号入栈
            PushSqStack(&s,str[i]);
        } else{
            //扫描到右括号,出栈
            resChar = PopSqStack(&s);
            if(resChar=='k')
            {
                //5.遇到右括号，栈是空的，说明这个右括号是单身，报错
                res = -1;
                break;
            }
            //3.遇到右括号出栈，与右括号配对
            if(str[i]==')' && resChar!='(')
            {
                //4.配对不成功，报错
                res = -1;
                break;
            }
            if(str[i]==']' && resChar!='[')
            {
                //4.配对不成功，报错
                res = -1;
                break;
            }
            if(str[i]=='}' && resChar!='{')
            {
                //4.配对不成功，报错
                res = -1;
                break;
            }
        }
    }

    //6.括号已经扫描完了，栈不是空的，说明有单身的左括号，报错
    if(s.top!=-1)
    {
        res = -1;
    }

    printfSqStack(&s);
    return res;
}

void DoKuoHao()
{
    char str[6] = "[(())]";
    printf("str:%s\n",str);
    int res = bracketCheck(str,6);
    if(res==-1)
    {
        printf("fail\n");
    } else{
        printf("success\n");
    }
}
/**********栈在括号中的应用**********/

/**********栈在表达式中的应用**********/
/*
一.用栈把中缀表达式,转化为后缀表达式
例: 2+4*(6-3)-8/4  ---->  2463-*+84/-
从左到右扫描各个元素
 1.遇到操作数，直接加入后缀表达式
 2.遇到界限符，如果是'('直接入栈，如果是')'则依次弹出栈内运算符并加入后缀表达式，直到弹出'('为止，'('不加后缀表达式
 3.遇到运算符，依次弹出栈中优先级高于或等于当前运算符得所有运算符，并加入后缀表达式，遇到'('或栈空则停止，然后把当前运算符入栈

*/
void SuffixOperation(char str[],int length)
{
    char suffix[20];    //后缀表达式
    int j=0;    //进入后缀表达式游标
    char resChar;   //接受出栈数据
    SqStack s;  //声明顺序栈，分配空间
    s = InitSqStack();

    for(int i=0;i<length;i++)
    {
        //遇到操作数，直接放入后缀表达式
        if(isdigit(str[i]))
        {
            suffix[j] = str[i];
            j++;
        }
        //遇到界限符
        if(str[i]=='(' || str[i]==')')
        {
            //如果是'('直接入栈
            if(str[i]=='(')
            {
                PushSqStack(&s,str[i]);
            }else if(str[i]==')')
            {
                //如果是')'则依次弹出栈内运算符并加入后缀表达式
                int isLoop = 1;
                //直到弹出'('为止 或者 栈空为止
                while(isLoop==1)
                {
                    resChar = PopSqStack(&s);
                    if(resChar=='(' || resChar=='k')
                    {
                        isLoop=0;
                    } else{
                        //加入后缀表达式
                        suffix[j] = resChar;
                        j++;
                    }
                }
            }
        }
        //遇到运算符
        if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/')
        {
            //看下栈顶元素是否是'(',空栈，或者优先级低于当前运算符
            resChar = GetSqStackTop(&s);
            //遇到'('或栈空则停止
            if(resChar=='(' || resChar=='k')
            {

            }else if(str[i]=='*' || str[i]=='/')
            {
                // + 和 - 不用弹出栈
                if(resChar=='+'||resChar=='-')
                {

                } else{
                    //加入后缀表达式
                    resChar = PopSqStack(&s);
                    suffix[j] = resChar;
                    j++;
                }
            }else if(str[i]=='+' || str[i]=='-')
            {
                //所有运算符都要
                //加入后缀表达式
                resChar = PopSqStack(&s);
                suffix[j] = resChar;
                j++;
            }
            //然后把当前运算符入栈
            PushSqStack(&s,str[i]);
        }
    }

    printf("suffix is: %s\n",suffix);
}

/**********栈在表达式中的应用**********/


void test()
{
    char s[20];

    for(int j=0;j<10;j++)
    {
        s[j] = ')';
    }
    printf("sss: %s\n",s);
}

int main() {
    char suffix[20] = {"2+4*(6-3)-8/4"};
    SuffixOperation(suffix,13);
    return 0;
}