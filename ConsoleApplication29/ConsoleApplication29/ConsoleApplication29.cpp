#include <iostream>
#include <Windows.h>
#include <cmath>
#define MAX 100//运算的最大次数
using namespace std;
long long int ints[MAX] = { 0 };

long long int mod(long long int a, long long int b)//求模运算
{
	while (a < 0)
		a += b;
	while (a >= b)
		a -= b;
	return a;
}

bool isprime(long long int m)//判断是否为素数
{
	if (m == 2 || m == 3)
		return true;
	for (long long int i = 2; i <= long long int(sqrt(double(m))); ++i)
		if (mod(m, i) == 0)
			return false;
	return true;
}

long long int ksm(long long int a, long long int c, long long int b)
{
	long long int re = 1;
	long long int t = a;
	while (c)
	{
		if (c & 1)
			re = mod(re, b) * mod(t, b);
		t = mod(t, b) * mod(t, b);
		c >>= 1;
	}
	return re;
}

long long int pd(long long int x, long long int o, long long int p)
{
	for (long long int i = 1; i <= o; ++i)
		if (mod(ksm(x, (p - 1) / ints[i], p), p) == 1)
			return 0;
	return 1;
}

long long int fun(long long int x, long long int n)//指数运算
{
	long long int s = 1;
	while (n--)
		s *= x;
	return s;
}

bool isP(long long int p)//判断是否有原根
{
	if (p == 1)
		return false;
	else if (p == 2)
		return true;
	else if (p == 4)
		return true;
	else if (isprime(p))
		return true;
	else if (mod(p, 2) == 0)//判断2p
	{
		if (isprime(long long int(p / 2)))
			return true;
	}
	else//判断p^n
	{
		long long int tmp1 = 3;//底数
		long long int tmp2 = 1;//指数
		while (true)
		{
			if (!isprime(tmp1))
				if (tmp1 < sqrt(p))
					tmp1++;
				else
					break;
			if (fun(tmp1, tmp2) == p)
			{
				if (isprime(tmp1))
					return true;
			}
			if (fun(tmp1, tmp2) > p)
			{
				tmp1++;
				tmp2 = 0;
				continue;
			}
			tmp2++;
		}
	}
	return false;
}

int main()
{
	long long int pp = 0;
	long long int j = 2;
	long long int o = 0;
	long long int p = 0;
	system("chcp 936&title 求原根&color e&cls");
	while (true)
	{
		j = 2;
		o = 0;
		cout << "请输入p：";
		rewind(stdin);
		if (scanf_s("%lld", &p) != 1 || p < 1)
			cout << "输入的值不是正整数。" << endl << endl;
		else if (p == 1 || p == 2)
			cout << "经判断，" << p << " 无原根或无意义" << "。" << endl << endl;
		else if (isP(p))
		{
			pp = p;
			p--;
			for (long long int i = 2; i <= sqrt(p); ++i)
			{
				if (p == 1)
					break;
				if (mod(p, i) == 0)
				{
					o++;
					ints[o] = i;
					while (mod(p, i) == 0)
						p /= i;
				}
			}
			if (p != 1)
			{
				o++;
				ints[o] = p;
			}
			p = pp;
			for (j = 2; j < p; j++)
				if (pd(j, o, p))
				{
					cout << "经计算，" << pp << " 的原根为 " << j << "。" << endl << endl;
					break;
				}
		}
		else
			cout << "经判断，" << p << " 无原根或无意义" << "。" << endl << endl;
		rewind(stdin);
		if (MessageBox(NULL, TEXT("继续运算吗？"), TEXT("求原根"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST) == 7)
			break;
	}
	MessageBox(NULL, TEXT("欢迎再次使用，点击“确定”退出本程序。"), TEXT("求原根"), MB_OK | MB_TOPMOST);
	system("cls");
	return 0;
}