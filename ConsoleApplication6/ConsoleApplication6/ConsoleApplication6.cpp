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
}//初始化线性表

SqList createList(SqList* L, int n)
{
begin:
    for (int i = 0; i < n; i++)
    {
        L->data[i] = rand();
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (L->data[i] <= L->data[i + 1])
            goto success;
    }
    goto begin;
success:
    L->length = n;
    return *L;
}//建造线性表

Status del(SqList* L, int x, int y)
{
    int i, j = 0, New[100] = { 0 };
    for (i = 0; i < L->length; i++)
        if (L->data[i] <= x || L->data[i] >= y)
        {
            New[j] = L->data[i];
            j++;
        }
    for (i = 0; i < j; i++)
        L->data[i] = New[i];
    L->length = j;
    return OK;
}//介值移除

void showList(SqList* L)
{
    for (int i = 0; i <= L->length - 1; i++)
    {
        if (i % 10 == 9)
            printf("%d\n", L->data[i]);
        else
            printf("%d\t", L->data[i]);
    }
    printf("\n\n");
}//屏幕输出线性表

int main()
{
    system("chcp 936&title 高效介值移除&color e&cls");
    int n, x, y;
    char Ens;
    SqList L;
    initList(&L);
m:
    system("cls");
    printf("请输入线性表的元素个数（最多99个）:\n");
    if (scanf_s("%d", &n) == 1)
    {
        if (n <= 1 || n >= 100)
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
        printf("当前线性表：\n");
        showList(&L);
        printf("请输入下界x（不会删除x）:\n");
        if (scanf_s("%d", &x) != 1)
        {
            error();
            continue;
        }
        rewind(stdin);
        printf("\n请输入上界y（不会删除y）:\n");
        if (scanf_s("%d", &y) != 1)
        {
            error();
            continue;
        }
        rewind(stdin);
        system("cls");
        printf("删除前：\n");
        showList(&L);
        del(&L, x, y);
        printf("删除后：\n");
        showList(&L);
        printf("删除完成，是否继续删除？（Y/N）\n");
        scanf_s("%c", &Ens, sizeof(Ens));
        rewind(stdin);
        if (Ens == 'N' || Ens == 'n')
            break;
    }
    printf("\n\n欢迎再次使用，请按任意键退出本程序。\n");
    system("pause>nul&cls");
    return 0;
}