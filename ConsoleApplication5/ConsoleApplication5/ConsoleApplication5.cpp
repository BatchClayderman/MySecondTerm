#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#define MaxSize 100
#define ElemType int
#define Status int
#define OK 1
#define ERROR 0
using namespace std;

void error(void)
{
    system("cls");
    printf("\a错误：所输入的整数不合法，请按任意键重新输入。\n");
    rewind(stdin);
    system("pause>nul&cls");
    return;
}//抛出异常

typedef struct
{
    ElemType data[MaxSize];
    int length;
} SqList; //定义结构体

Status initList(SqList* L)
{
    L->length = 0;
    return 0;
}//初始化顺序表

SqList createList(SqList* L, int n)
{
    int startNumber, step;
a:
    system("cls");
    printf("请输入初始值：\n");
    if (scanf_s("%d", &startNumber) != 1)
    {
        error();
        goto a;
    }
    rewind(stdin);
b:
    system("cls");
    printf("请输入步长（步长应该是个正整数）：\n");
    if (scanf_s("%d", &step) == 1)
    {
        if (step <= 0)
        {
            error();
            goto b;
        }
    }
    else
    {
        error();
        goto b;
    }
    rewind(stdin);
    for (int i = 0; i < n; i++)
        L->data[i] = startNumber + (i)*step;
    L->length = n;
    return *L;
}//建造顺序表

Status locateList(SqList* L, ElemType e)
{
    if (e <= L->data[0])
        return 0;
    if (e >= L->data[L->length - 1])
        return L->length;
    else
        for (int i = 0; i < L->length - 1; i++)
            if (e > L->data[i] && e <= L->data[i + 1])
                return i + 1;
}//定位某元素在数据表中的位置

Status inorderList(SqList* L, ElemType location, ElemType e)
{
    if (L->length >= 99)
        return ERROR;
    for (int i = L->length - 1; i >= location; i--)
        L->data[i + 1] = L->data[i];
    L->data[location] = e;
    L->length++;
    return OK;
}//插入指定位置的数据

void showList(SqList* L)
{
    printf("顺序表输出如下：\n");
    for (int i = 0; i <= L->length - 1; i++)
    {
        if (i % 10 == 9)
            printf("%d\n", L->data[i]);
        else
            printf("%d\t", L->data[i]);
    }
    printf("\n\n");
}//屏幕输出顺序表

int main()
{
    system("chcp 936&title 有序递增链表与数据插入&color e&cls");
    int n, InputNumber, sure;
    char Ens;
    SqList L;
    initList(&L);
m:
    system("cls"); 
    printf("请输入顺序表的元素个数（最大值为%d）:\n", MaxSize - 1);
    if (scanf_s("%d", &n) == 1)
    {
        if (n <= 0 || n >= MaxSize)
        {
            error();
            goto m;
        }
    }
    else
    {
        error();
        goto m;
    }
    rewind(stdin);
    createList(&L, n);
    while (true)
    {
        system("cls");
        showList(&L);
        printf("请输入插入的元素e:\n");
        if (scanf_s("%d", &InputNumber) != 1)
        {
            error();
            continue;
        }
        rewind(stdin);
        int Location = locateList(&L, InputNumber);
        sure = inorderList(&L, Location, InputNumber);
        system("cls");
        showList(&L);
        rewind(stdin);
        if (sure)
            printf("插入成功，是否继续插入？（Y/N）\n");
        else
            printf("\a插入失败，可能是因为内存已满，是否重试？（Y/N）\n");
        scanf_s("%c", &Ens, sizeof(Ens));
        rewind(stdin);
        if (Ens == 'N' || Ens == 'n')
            break;
    }
    system("cls");
    showList(&L);
    printf("欢迎再次使用，请按任意键退出本程序。\n");
    system("pause>nul&cls");
    return 0;
}