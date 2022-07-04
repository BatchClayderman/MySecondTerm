#include <stdio.h>
#include <stdlib.h>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif// EXIT_SUCCESS
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif// EXIT_FAILURE
#ifndef EOF
#define EOF (-1)
#endif// EOF
#ifndef EEOF
#define EEOF (-2)
#endif// EEOF


void error()
{
	system("cls");
	printf("\a错误：所输入的整数不合法，请按任意键重新输入。\n");
	rewind(stdin);
	fflush(stdin);
	system("pause>nul&cls");
	return;
}

long long int mod(long long int a, long long int b)// 将 C 语言里的 % 改造成真正意义上的模
{
	if (b <= 0)
	{
		printf("\a错误：发生零除错误，为了防止更严重的错误，请按任意键退出程序。");
		rewind(stdin);
		fflush(stdin);
		system("pause>nul&cls");
		exit(EEOF);
	}
	if (a >= 0)
		return a % b;
	else
		return b - (-a) % b;
}

long long int powerModRec(long long int b, long long int n, long long int m)//递归实现
{
	if (0 == n)
		return 1;
	return mod(b * mod(powerModRec(b, n - 1, m), m), m);//再模一次以防止出现负数结果
}

long long int powerMod(long long int b, long long int n, long long int m)//递推实现
{
	long long int a = 1, k = 0, num = n;// a 存放计算结果，初始化为 1。
	while (num)
	{
		num = num >> 1;
		++k;
	}
	for (long long int i = 0; i < k; ++i)
	{
		if ((n >> i) & 1)//取 n 的二进制的第 i 位，判断是否为 1。
			a = mod(a * b, m);
		b = mod(b * b, m);
	}
	return a;
}

int main(int argc, char* argv[])
{
	long long int b, n, m;
	char Ens = 'Y';
	if (4 == argc)
	{
		if (sscanf_s(argv[1], "%lld", &b) == 1 && sscanf_s(argv[2], "%lld", &n) == 1 && sscanf_s(argv[3], "%lld", &m) == 1)
		{
			if (n < 0)
			{
				printf("\a错误：指数不能为负数。\n");
				return EOF;
			}
			if (0 == b && 0 == n)
			{
				printf("\a错误：底数和指数同时为0，运算无意义。\n");
				return EOF;
			}
			if (m < 2)
			{
				printf("\a错误：模只能为大于 2 的正数。\n");
				return EOF;
			}
		}
		else
		{
			printf("\a错误：命令行参数无效。\n");
			return EOF;
		}
		printf("\nb = %lld\t\tn = %lld\t\tm = %lld\n递归实现：%lld，递推实现：%lld。\n\n", b, n, m, powerModRec(b, n, m), powerMod(b, n, m));
		return EXIT_SUCCESS;
	}
	else if (argc != 1)
	{
		printf("\a错误：命令行参数数目不正确。\n");
		return EOF;
	}
	system("chcp 936&title 模重复平方算法&color e");
	rewind(stdin);//清空键盘缓冲区
	fflush(stdin);
b:
	system("cls");
	printf("请输入底数b：");
	if (scanf_s("%lld", &b) != 1)
	{
		error();
		goto b;
	}
	rewind(stdin);
	fflush(stdin);
n:
	system("cls");
	printf("请输入指数n（自然数且当底数为 0 时不能为 0）：");
	if (scanf_s("%lld", &n) == 1)
	{
		if (n < 0)
		{
			error();
			goto n;
		}
		if (0 == b && 0 == n)
		{
			error();
			goto n;
		}
	}
	else
	{
		error();
		goto n;
	}
	rewind(stdin);
	fflush(stdin);
m:
	system("cls");
	printf("请输入模m（大于 2 的正整数）：");
	if (scanf_s("%lld", &m) == 1)
	{
		if (m < 2)
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
	fflush(stdin);
	system("cls");
	printf("输入的底数 b = %lld，指数 n = %lld，模 m = %lld。\n", b, n, m);
	long long int result = powerModRec(b, n, m);
	printf("递归实现：b^n (mod m) = %lld\n", result);
	result = powerMod(b, n, m);
	printf("非递归实现：b^n (mod m) = %lld\n", result);
	printf("\n\n运算完成，输入“E”或“e”回车可退出程序，直接回车可运行新的运算。\n");
	scanf_s("%c", &Ens, sizeof(Ens));
	rewind(stdin);
	fflush(stdin);
	if ('E' == Ens || 'e' == Ens)
	{
		system("cls");
		return EXIT_SUCCESS;
	}
	else
	{
		rewind(stdin);
		fflush(stdin);
		goto b;
	}
	return EOF;
}
//b = 188，n = 47，m = 590，result = 82。