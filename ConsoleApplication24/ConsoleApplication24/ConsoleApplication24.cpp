#include <iostream>
using namespace std;

double method1(int n, double* tmp)//矩形法
{
	double result = 0;
	int i;
	for (i = 0; i <= n; i++)
		result += tmp[i];
	return result / i;
}

double method2(int n, double* tmp)//梯形法
{
	double result = tmp[0] / 2 + tmp[n] / 2;
	for (int i = 1; i < n; i++)
		result += tmp[i];
	return result / n;
}

double method3(int n, double* tmp)//抛物线法
{
	double result = tmp[0] + tmp[2 * n];
	for (int i = 1; i <= 2 * n - 1; i += 2)
		result += 4 * tmp[i];
	for (int i = 2; i <= 2 * n - 2; i += 2)
		result += 2 * tmp[i];
	return result / 6 / n;
}

int main()
{
	system("chcp 936&title 近似计算&color e&cls");
	int n = 12;
	double y[13] = { 25.8,23.0,24.1,25.6,27.3,30.2,33.4,35.0,33.8,31.1,28.2,27.0,25.0 };
	cout << "{ 25.8,23.0,24.1,25.6,27.3,30.2,33.4,35.0,33.8,31.1,28.2,27.0,25.0 }" << endl;
	cout << "矩形法：" << method1(n, y) << endl;
	cout << "梯形法：" << method2(n, y) << endl;
	cout << "抛物线法：" << method3(n >> 1, y) << endl;
	cout << endl << endl << "运算完毕，请按任意键退出本程序。" << endl;
	system("pause>nul&cls");
	return 0;
}