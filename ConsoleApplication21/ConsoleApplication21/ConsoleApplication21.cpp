#include <stdio.h>
#include <stdlib.h>

struct gcdstruct
{
	long long int d;
	long long int x;
	long long int y;
};

gcdstruct EXTENDED_EUCLID(long long int a, long long int b)
{
	gcdstruct aa, bb;
	if (b == 0)
	{
		aa.d = a;
		aa.x = 1;
		aa.y = 0;
		return aa;
	}
	else
	{
		bb = EXTENDED_EUCLID(b, a % b);
		aa.d = bb.d;
		aa.x = bb.y;
		aa.y = bb.x - bb.y * (a / b);
	}
	return aa;
}

long long int GCD(long long int a, long long int b)
{
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

void error(void)
{
    system("cls");
    printf("\a错误：所输入的整数不合法，请按任意键重新输入。\n");
    rewind(stdin);
    system("pause>nul&cls");
    return;
}

long long int inverse(long long int a, long long int m)
{
	gcdstruct aa;
	aa = EXTENDED_EUCLID(a, m);
    while (aa.x < 0)
        aa.x += m;
	return aa.x;
}

void course(long long int a, long long int m)
{
    if (GCD(a, m) == 1)
    {
        printf("a = %lld\n", a);
        printf("m = %lld\n", m);
        printf("x = %lld\n\n", inverse(a, m));
    }
    else
    {
        printf("a = %lld\n", a);
        printf("m = %lld\n", m);
        printf("（a，m） = %lld\n\n", GCD(a, m));
    }
}

int main(int argc, char* argv[])
{
    long long int a, m;
    if (argc == 3)
    {
        if (sscanf_s(argv[1], "%lld", &a) != 1 || sscanf_s(argv[2], "%lld", &m) != 1)
        {
            printf("\a错误：命令行参数无效。\n");
            exit(-1);
        }
        printf("\n");
        course(a, m);
        exit(0);
    }
    system("chcp 936&title 第十三例 求模逆元&color e&cls");
    char Ens = 'Y';
a:
    system("cls");
    printf("请输入系数 a：");
    rewind(stdin);
    if (scanf_s("%lld", &a) != 1)
    {
        error();
        goto a;
    }
    rewind(stdin);
b:
    system("cls");
    printf("a = %lld\n", a);
    printf("请输入模数 m：");
    if (scanf_s("%lld", &m) != 1)
    {
        error();
        goto b;
    }
    rewind(stdin);
    system("cls");
    course(a, m);
    printf("\n输入“E”或“e”回车可退出程序，直接回车可运行新的运算。\n");
    scanf_s("%c", &Ens, sizeof(Ens));
    rewind(stdin);
    if (Ens == 'E' || Ens == 'e')
    {
        system("cls");
        return 0;
    }
    else
    {
        rewind(stdin);
        goto a;
    }
    return -1;
}