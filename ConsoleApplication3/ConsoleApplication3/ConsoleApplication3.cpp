#include <stdio.h>
#include <stdlib.h>

void error(void)
{
    system("cls");
    printf("\a错误：所输入的整数不合法，请按任意键重新输入。\n");
    rewind(stdin);
    system("pause>nul&cls");
    return;
}

int* exgcd(int p, int q, int result[3])
{
    if (p == 0 && q != 0)
        result[0] = q, result[1] = 0, result[2] = 1;
    else if (q == 0 && p != 0)
        result[0] = p, result[1] = 1, result[2] = 0;
    else if (p == 0 && q == 0)
        result[0] = 0, result[1] = 0, result[2] = 0;
    else
    {
        int m, n, z = 0;
        m = abs(p) >= abs(q) ? abs(p) : abs(q);
        n = abs(p) >= abs(q) ? abs(q) : abs(p);
        int x = 1, j = 1, y = 0, i = 0, c = m, d = n, o = int(c / d), r = c % d;
        while (r)
        {
            c = d;
            d = r;
            z = x;
            x = i;
            i = z - o * i;
            z = y;
            y = j;
            j = z - o * j;
            o = int(c / d);
            r = c % d;
        }
        result[0] = d;
        if (abs(p) >= abs(q))
        {
            result[1] = p >= 0 ? i : -i;
            result[2] = q >= 0 ? j : -j;
        }
        else
        {
            result[1] = p >= 0 ? j : -j;
            result[2] = q >= 0 ? i : -i;
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    int* re;
    int res[3] = { 0 };
    int a, b;
    if (argc == 3)
    {
        if (sscanf_s(argv[1], "%d", &a) != 1 || sscanf_s(argv[2], "%d", &b) != 1)
        {
            printf("\a错误：命令行参数无效。\n");
            exit(-1);
        }
        re = exgcd(a, b, res);
        printf("a = %d\tb = %d\t\t（a，b）= %d\ts = %d\tt = %d\n", a, b, re[0], re[1], re[2]);
        exit(0);
    }
    system("chcp 936&title 拓展欧几里得除法&color e&cls");
    char Ens = 'Y';
a:
    system("cls");
    printf("请输入整数a：");
    if (scanf_s("%d", &a) != 1)
    {
        error();
        goto a;
    }
    rewind(stdin);
b:
    system("cls");
    printf("请输入整数b：");
    if (scanf_s("%d", &b) != 1)
    {
        error();
        goto b;
    }
    rewind(stdin);
    system("cls");
    printf("正在运行计算，请稍候。\n");
    re = exgcd(a, b, res);
    system("cls");
    printf("运行完成，%d 和 %d 的最大公因数为 %d，s = %d，t = %d。\n输入“E”或“e”回车可退出程序，直接回车可运行新的运算。\n",a,b,re[0],re[1],re[2]);
    scanf_s("%c", &Ens, sizeof(Ens));
    rewind(stdin);
    if (Ens == 'E' || Ens == 'e')
    {
        system("cls");
        exit(0);
    }
    else
    {
        rewind(stdin);
        goto a;
    }
    return -1;
}