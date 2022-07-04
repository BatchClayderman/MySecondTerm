#include <iostream>
#include <Windows.h>
using namespace std;

long long int mod(long long int a, long long int b)//求模运算
{
	while (a < 0)
		a += b;
	while (a >= b)
		a -= b;
	return a;
}

long long int fun(long long int x, long long int n)//指数运算
{
	long long int s = 1;
	while (n--)
		s *= x;
	return s;
}

long long int gcd(long long int a, long long int b)//求最大公因数
{
	long long int k = long long int(a / b);
	long long int remainder = mod(a, b);
	while (remainder)
	{
		a = b;
		b = remainder;
		k = long long int(a / b);
		remainder = mod(a, b);
	}
	return b;
}

void _zm(long long int p1, long long int p2, bool flag)//算法函数
{
	if (p1 < 2 || p2 < 2)
	{
		cout << "\a错误：您输入的两数不全为大于 1 的自然数，请按任意键返回。" << endl;
		system("pause>nul&cls");
		return;
	}
	long long int i = 1;
	while (true)
	{
		if (mod(fun(p1, i), p2) == 1)
		{
			cout << p1 << "^" << i << "≡" << mod(fun(p1, i), p2) << "(mod " << p2 << ")" << endl << "所求指数为 " << i << endl;
			return;
		}
		else
		{
			if (flag)
				cout << p1 << "^" << i << "≡" << mod(fun(p1, i), p2) << "(mod " << p2 << ")" << endl;
			i++;
		}
	}
	return;
}

int main()//主函数
{
	system("chcp 936&title 求模指数&color e");
	long long int p1, p2;
	short int errorcontrol;
	while (true)
	{
		system("cls");
		cout << "请输入底数 a：" << endl;
		rewind(stdin);
		while (scanf_s("%lld", &p1) != 1)
			rewind(stdin);
		cout << "请输入模数 m：" << endl;
		rewind(stdin);
		while (scanf_s("%lld", &p2) != 1)
			rewind(stdin);
		rewind(stdin);
		errorcontrol = MessageBox(NULL, TEXT("显示过程吗？"), TEXT("求模指数"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
		system("cls");
		if (gcd(p1, p2) == 1)
			errorcontrol == 6 ? _zm(p1, p2, true) : _zm(p1, p2, false);
		else
			cout << "\a错误：您输入的两数不互素。" << endl;
		errorcontrol = MessageBox(NULL, TEXT("继续运算吗？"), TEXT("求模指数"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
		if (errorcontrol == 7)
			break;
	}
	MessageBox(NULL, TEXT("欢迎再次使用，点击“确定”退出本程序。"), TEXT("求模指数"), MB_OK | MB_TOPMOST);
	system("cls");
	return 0;
}