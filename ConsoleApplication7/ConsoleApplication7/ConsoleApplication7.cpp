#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define ERROR 0
#define OK 1
typedef char ElemType;
typedef int NumType;
using namespace std;

typedef struct Node
{
    ElemType data;
    NumType length;
    struct Node* next;
}Node, * head;//head为结构指针类型，用来说明头指针变量，对应到链表A、B中为heada和headb

void inithead(head* L)//初始化单链表
{
    *L = (head)malloc(sizeof(Node));
    return;
}

int Create(head L)//建立单链表
{
    Node* s, * r;
    int count = 0;
    char c;
    r = L;
    while (true)
    {
        c = getchar();
        if (c != '#')//当输入#时建表结束
        {
            s = (Node*)malloc(sizeof(Node));
            if (s == NULL)
            {
                free(L);
                return ERROR;
            }
            s->data = c;
            r->next = s;
            r = s;
            count++;
        }
        else
        {
            r->next = NULL;
            break;
        }
    }
    if (count == 0)
    {
        free(L);
        return ERROR;
    }
    else
    {
        L->length = count;
        return OK;
    }
}

int DelAndSub(head LA, head LB, int i, int j, int len)//移动元素
{
    Node* p, * q, * prev, * s;
    if (i < 1 || j < 1 || len < 0)
        return ERROR;
    if (len == 0)
        return OK;
    p = LA;
    prev = NULL;
    int k = 1;
    while (p && k <= i)
    {
        prev = p;
        p = p->next;
        k++;
    }
    if (!p)
        return ERROR;
    q = p;
    k = i;
    while (q && k < i + len - 1)
    {
        q = q->next;
        k++;
    }
    if (!q)
        return ERROR;
    if (!prev)
        LA = q->next;
    else
        prev->next = q->next;
    s = LB;
    k = 1;
    while (s && k < j)
    {
        s = s->next;
        k++;
    }
    if (!s)
        return ERROR;
    q->next = s->next;
    s->next = p;
    return OK;
}

void print(head L)//打印链表
{
    Node* p;
    p = L->next;
    while (p != NULL)
    {
        printf("%c", p->data);
        p = p->next;
    }
}

void error(void)//抛出异常
{
    system("cls");
    printf("\a错误：输入不合法，请按任意键重新输入。\n");
    rewind(stdin);
    system("pause>nul&cls");
    return;
}

int main()
{
    system("chcp 936&title 双链表移动元素&color e&cls");
    head LA, LB;
    int i, len, j;
la:
    inithead(&LA);
    system("cls");
    printf("请创建链表A，以“#”结束创建：\n");
    if (not Create(LA))
    {
        rewind(stdin);
        system("cls");
        printf("\a链表A创建失败，请按任意键重试。\n");
        system("pause>nul");
        goto la;
    }
    rewind(stdin);
lb:
    inithead(&LB);
    system("cls");
    printf("请创建链表B，以“#”结束创建：\n");
    if (not Create(LB))
    {
        rewind(stdin);
        system("cls");
        printf("\a链表B创建失败，请按任意键重试。\n");
        system("pause>nul");
        goto lb;
    }
    rewind(stdin);
    system("cls");
    printf("链表 A 打印如下：\n");
    print(LA);
    printf("\n\n链表 B 打印如下：\n");
    print(LB);
    printf("\n\n\n打印完毕，请按任意键继续。\n");
    system("pause>nul");
a:
    system("cls");
    printf("请输入需要从 A 中移走的首个元素在 A 中的位置 i (有效值为 1 到 %d )：\n", LA->length);
    if (scanf_s("%d", &i) == 1)
    {
        if (i < 1 || i > LA->length)
        {
            error();
            goto a;
        }
    }
    else
    {
        error();
        goto a;
    }
    rewind(stdin);
b:
    system("cls");
    printf("请输入 A 中需要移走的个数 len （有效值为 0 到 %d ）：\n", LA->length + 1 - i);
    if (scanf_s("%d", &len) == 1)
    {
        if (len < 0 || len > LA->length + 1 - i)
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
c:
    system("cls");
    printf("请输入即将在 B 中之前插入的位置 j （有效值为 1 到 %d ）：\n", LB->length);
    if (scanf_s("%d", &j) == 1)
    {
        if (j < 1 || j > LB->length)
        {
            error();
            goto c;
        }
    }
    else
    {
        error();
        goto c;
    }
    rewind(stdin);
    system("cls");
    if (DelAndSub(LA, LB, i, j, len))
        printf("操作成功结束，");
    else
        printf("\a操作失败，");
    printf("当前链表 A 、 B 如下：\n\n\n————————链表 A ————————\n");
    print(LA);
    printf("\n\n————————链表 B ————————\n");
    print(LB);
    printf("\n\n\n\n演示结束，请按任意键退出本程序。\n");
    system("pause>nul&cls");
    return 0;
}