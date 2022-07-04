#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

void error()//抛出异常
{
	system("cls");
	printf("\a错误：存在输入不合法，请按任意键重新输入。\n");
	rewind(stdin);
	system("pause>nul&cls");
	return;
}

int gcd(int m, int n)//求最大公约数
{
	int x, y, z;
	if (m < n)
	{
		z = m;
		m = n;
		n = z;
	}
	x = m;
	y = n;
	while (y != 0)
	{
		z = x % y;
		x = y;
		y = z;
	}
	return x;
}

int Fen_Add(int q, int w, int v, int h)//分数加法
{
	int o, i, l, k, j;
	o = w * h;
	i = q * h + w * v;
	l = gcd(o, i);
	j = i / l;
	k = o / l;
	if (k < 0)
	{
		j *= -1;
		k *= -1;
	}
	if (k == 1 || j == 0)
		printf("\n经计算，(%d/%d) + (%d/%d) = %d。\n\n\n", q, w, v, h, j);
	else
	{
		if (j > k)
		{
			if (j > 0)
				printf("\n经计算，(%d/%d) + (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k), j % k, k);
			else
				printf("\n经计算，(%d/%d) + (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k) - 1, k + j % k, k);
		}
		else
			printf("\n经计算，(%d/%d) + (%d/%d) = %d/%d。\n\n\n", q, w, v, h, j, k);
	}
	return 0;
}

int Add(float a, float b)//有理数加法
{
	int q, w, v, h, x, c = 0;
	float sum;
loop1:
	system("cls");
	printf("—————————————— 加 法 运 算 ——————————————\n");
	printf("1 = 整数或小数加法\t2 = 分数加法\t\t3 = 返回主面板\n\n\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 1 || x > 3)
		{
			error();
			goto loop1;
		}
	}
	else
	{
		error();
		goto loop1;
	}
	rewind(stdin);
	switch (x)
	{
	case 1:
	{
	loop1_1:
		c = 0;
		system("cls");
		printf("请输入第一个数据：");
		c += scanf_s("%f", &a);
		rewind(stdin);
		printf("请输入第二个数据：");
		c += scanf_s("%f", &b);
		rewind(stdin);
		if (c != 2)
		{
			error();
			goto loop1_1;
		}
		rewind(stdin);
		sum = a + b;
		printf("\n经计算，%f + %f = %f。\n\n\n", a, b, sum);
		system("pause");
		goto loop1;
		break;
	}
	case 2:
	{
	loop1_2:
		system("cls");
		c = 0;
		printf("输入第一个数的分子：");
		c += scanf_s("%d", &q);
		rewind(stdin);
		printf("输入第一个数的分母：");
		c += scanf_s("%d", &w);
		rewind(stdin);
		printf("输入第二个数的分子：");
		c += scanf_s("%d", &v);
		rewind(stdin);
		printf("输入第二个数的分母：");
		c += scanf_s("%d", &h);
		rewind(stdin);
		if (c == 4)
		{
			if (w == 0 || h == 0)
			{
				error();
				goto loop1_2;
			}
		}
		else
		{
			error();
			goto loop1_2;
		}
		Fen_Add(q, w, v, h);
		system("pause");
		goto loop1;
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}
	return -1;
}

int Fen_Sub(int q, int w, int v, int h)//分数减法
{
	int o, i, l, k, j;
	o = w * h;
	i = q * h - w * v;
	l = gcd(o, i);
	j = i / l;
	k = o / l;
	if (k < 0)
	{
		j *= -1;
		k *= -1;
	}
	if (k == 1 || j == 0)
		printf("\n经计算，(%d/%d) - (%d/%d) = %d。\n\n\n", q, w, v, h, j);
	else
	{
		if (j > k)
		{
			if (j > 0)
				printf("\n经计算，(%d/%d) - (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k), j % k, k);
			else
				printf("\n经计算，(%d/%d) - (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k) - 1, k + j % k, k);
		}
		else
			printf("\n经计算，(%d/%d) - (%d/%d) = %d/%d。\n\n\n", q, w, v, h, j, k);
	}
	return 0;
}

int Sub(float a, float b)//有理数减法
{
	float sum;
	int q, w, v, h, x, c = 0;
loop2:
	system("cls");
	printf("—————————————— 减 法 运 算 ——————————————\n");
	printf("1 = 整数或小数减法\t2 = 分数减法\t\t3 = 返回主面板\n\n\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 1 || x > 3)
		{
			error();
			goto loop2;
		}
	}
	else
	{
		error();
		goto loop2;
	}
	rewind(stdin);
	switch (x)
	{
	case 1:
	{
	loop2_1:
		c = 0;
		system("cls");
		printf("请输入第一个数据：");
		c += scanf_s("%f", &a);
		rewind(stdin);
		printf("请输入第二个数据：");
		c += scanf_s("%f", &b);
		rewind(stdin);
		if (c != 2)
		{
			error();
			goto loop2_1;
		}
		rewind(stdin);
		sum = a - b;
		printf("\n经计算，%f - %f = %f。\n\n\n", a, b, sum);
		system("pause");
		goto loop2;
		break;
	}
	case 2:
	{
	loop2_2:
		system("cls");
		c = 0;
		printf("输入第一个数的分子：");
		c += scanf_s("%d", &q);
		rewind(stdin);
		printf("输入第一个数的分母：");
		c += scanf_s("%d", &w);
		rewind(stdin);
		printf("输入第二个数的分子：");
		c += scanf_s("%d", &v);
		rewind(stdin);
		printf("输入第二个数的分母：");
		c += scanf_s("%d", &h);
		rewind(stdin);
		if (c == 4)
		{
			if (w == 0 || h == 0)
			{
				error();
				goto loop2_2;
			}
		}
		else
		{
			error();
			goto loop2_2;
		}
		Fen_Sub(q, w, v, h);
		system("pause");
		goto loop2;
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}
	return -1;
}

int Fen_Mul(int q, int w, int v, int h)//分数乘法
{
	int o, i, l, k, j;
	o = w * h;
	i = q * v;
	l = gcd(o, i);
	j = i / l;
	k = o / l;
	if (k < 0)
	{
		j *= -1;
		k *= -1;
	}
	if (k == 1 || j == 0)
		printf("\n经计算，(%d/%d) × (%d/%d) = %d。\n\n\n", q, w, v, h, j);
	else
	{
		if (j > k)
		{
			if (j > 0)
				printf("\n经计算，(%d/%d) × (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k), j % k, k);
			else
				printf("\n经计算，(%d/%d) × (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k) - 1, k + j % k, k);
		}
		else
			printf("\n经计算，%d/%d × %d/%d = %d/%d。\n\n\n", q, w, v, h, j, k);
	}
	return 0;
}

int Mul(float a, float b)//有理数乘法
{
	float result;
	int q, w, v, h, x, c = 0;
loop3:
	system("cls");
	printf("—————————————— 乘 法 运 算 ——————————————\n");
	printf("1 = 整数或小数乘法\t2 = 分数乘法\t\t3 = 返回主面板\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 1 || x > 3)
		{
			error();
			goto loop3;
		}
	}
	else
	{
		error();
		goto loop3;
	}
	rewind(stdin);
	switch (x)
	{
	case 1:
	{
	loop3_1:
		c = 0;
		system("cls");
		printf("请输入第一个数据：");
		c += scanf_s("%f", &a);
		rewind(stdin);
		printf("请输入第二个数据：");
		c += scanf_s("%f", &b);
		rewind(stdin);
		if (c != 2)
		{
			error();
			goto loop3_1;
		}
		rewind(stdin);
		result = a * b;
		printf("\n经计算，%f × %f = %f。\n\n\n", a, b, result);
		system("pause");
		goto loop3;
		system("pause>nul");
		break;
	}
	case 2:
	{
	loop3_2:
		system("cls");
		c = 0;
		printf("输入第一个数的分子：");
		c += scanf_s("%d", &q);
		rewind(stdin);
		printf("输入第一个数的分母：");
		c += scanf_s("%d", &w);
		rewind(stdin);
		printf("输入第二个数的分子：");
		c += scanf_s("%d", &v);
		rewind(stdin);
		printf("输入第二个数的分母：");
		c += scanf_s("%d", &h);
		rewind(stdin);
		if (c == 4)
		{
			if (w == 0 || h == 0)
			{
				error();
				goto loop3_2;
			}
		}
		else
		{
			error();
			goto loop3_2;
		}
		Fen_Mul(q, w, v, h);
		system("pause");
		goto loop3;
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}
	return -1;
}

int fen_Div(int q, int w, int v, int h)//分数除法
{
	int o, i, l, k, j;
	o = w * v;
	i = q * h;
	l = gcd(o, i);
	j = i / l;
	k = o / l;
	if (k < 0)
	{
		j *= -1;
		k *= -1;
	}
	if (k == 1 || j == 0)
		printf("\n经计算，(%d/%d) ÷ (%d/%d) = %d。\n\n\n", q, w, v, h, j);
	else
	{
		if (j > k)
		{
			if (j > 0)
				printf("\n经计算，(%d/%d) ÷ (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k), j % k, k);
			else
				printf("\n经计算，(%d/%d) ÷ (%d/%d) = %d/%d = %d + %d/%d。\n\n\n", q, w, v, h, j, k, int(j / k) - 1, k + j % k, k);
		}
		else
			printf("\n经计算，(%d/%d) ÷ (%d/%d) = %d/%d。\n\n\n", q, w, v, h, j, k);
	}
	return 0;
}

int Div(float a, float b)//有理数除法
{
	float result;
	int q, w, v, h, x, c = 0;
loop4:
	system("cls");
	printf("—————————————— 除 法 运 算 ——————————————\n");
	printf("1 = 整数或小数除法\t2 = 分数除法\t\t3 = 返回主面板\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 1 || x > 3)
		{
			error();
			goto loop4;
		}
	}
	else
	{
		error();
		goto loop4;
	}
	rewind(stdin);
	switch (x)
	{
	case 1:
	{
	loop4_1:
		c = 0;
		system("cls");
		printf("请输入第一个数据：");
		c += scanf_s("%f", &a);
		rewind(stdin);
		printf("请输入第二个数据：");
		c += scanf_s("%f", &b);
		rewind(stdin);
		if (c != 2)
		{
			error();
			goto loop4_1;
		}
		rewind(stdin);
		result = a / b;
		printf("\n经计算，%f ÷ %f = %f。\n\n\n", a, b, result);
		system("pause");
		goto loop4;
		system("pause>nul");
		break;
	}
	case 2:
	{
	loop4_2:
		system("cls");
		c = 0;
		printf("输入第一个数的分子：");
		c += scanf_s("%d", &q);
		rewind(stdin);
		printf("输入第一个数的分母：");
		c += scanf_s("%d", &w);
		rewind(stdin);
		printf("输入第二个数的分子：");
		c += scanf_s("%d", &v);
		rewind(stdin);
		printf("输入第二个数的分母：");
		c += scanf_s("%d", &h);
		rewind(stdin);
		if (c == 4)
		{
			if (w == 0 || h == 0 || v == 0)
			{
				error();
				goto loop4_2;
			}
		}
		else
		{
			error();
			goto loop4_2;
		}
		fen_Div(q, w, v, h);
		system("pause");
		goto loop4;
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}
	return -1;
}

int feng(float z)//小数与分数换算
{
	int f, i, x, q, w, c = 0;
	float j, k, l;
loop5:
	system("cls");
	printf("————————————— 小 数 与 分 数 换 算 —————————————\n");
	printf("1 = 整数或小数转分数\t2 = 分数取近似小数\t3 = 返回主面板\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 1 || x > 3)
		{
			error();
			goto loop5;
		}
	}
	else
	{
		error();
		goto loop5;
	}
	rewind(stdin);
	switch (x)
	{
	case 1:
	{
	loop5_1:
		system("cls");
		printf("请输入小数：");
		if (scanf_s("%f", &j) != 1)
		{
			error();
			rewind(stdin);
		}
		rewind(stdin);
		i = 0;
		while (j != int(j))
		{
			j *= 10;
			i++;
		}
		if (i == 0)
			printf("该数为整数：%d\n\n\n", int(j));
		else
		{
			f = gcd(j, pow(10, i));
			q = j / f;
			w = pow(10, i) / f;
			if (w < 0)
			{
				q *= -1;
				w *= -1;
			}
			if (q > w)
			{
				if (q > 0)
					printf("该小数的分数形式为：%d/%d，即 %d + %d/%d。\n\n\n", q, w, int(q / w), q % w, w);
				else
					printf("该小数的分数形式为：%d/%d，即 %d + %d/%d。\n\n\n", q, w, int(q / w) - 1, w + q % w, w);
			}
			else
				printf("该小数的分数形式为：%d/%d。\n\n\n", q, w);
		}
		system("pause");
		goto loop5;
		break;
	}
	case 2:
	{
	loop5_2:
		system("cls");
		c = 0;
		printf("请输入分子：");
		c += scanf_s("%f", &k);
		rewind(stdin);
		printf("请输入分母：");
		c += scanf_s("%f", &l);
		rewind(stdin);
		if (c == 2)
		{
			if (l== 0 || int(k) != k || int(l) != l)
			{
				error();
				goto loop5_2;
			}
		}
		else
		{
			error();
			goto loop5_2;
		}
		j = k / l;
		printf("分数 %d/%d 切换小数（约）为 %f。\n\n\n", int(k), int(l), j);
		system("pause");
		goto loop5;
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}
	return -1;
}

int main()//主程序
{
	system("chcp 936&title 有理数四则运算(姓名：杨淯而，学号：2019052202）&color e&cls");
m:
	int x;
	float a = 0, b = 0, z = 0;
	system("cls");
	printf("\n————————————— 有 理 数 四 则 运 算 —————————————\n");
	printf("1 = 加法运算\t\t\t2 = 减法运算\n");
	printf("3 = 乘法运算\t\t\t4 = 除法运算\n");
	printf("5 = 小数与分数换算\t\t6 = 退出程序\n\n\n");
	printf("请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x <= 0 || x >= 7)
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
	switch (x)
	{
	case 1:
	{
		Add(a, b);
		break;
	}
	case 2:
	{
		Sub(a, b);
		break;
	}
	case 3:
	{
		Mul(a, b);
		break;
	}
	case 4:
	{
		Div(a, b);
		break;
	}
	case 5:
	{
		feng(z);
		break;
	}
	case 6:
	{
		system("cls");
		printf("欢迎再次使用，请按任意键退出本程序。\n");
		system("pause>nul&cls");
		exit(0);
		break;
	}
	}
	goto m;
	return -1;
}