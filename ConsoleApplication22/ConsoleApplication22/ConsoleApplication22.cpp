#include <iostream>
#include <Windows.h>
#include <time.h>
#include <atltime.h>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 0
#endif
#ifndef random
#define random(x) (rand() % x)
#endif
#ifndef len
#define len 69
#endif
#ifndef MAX
#define MAX 5203344
#endif
typedef void SortType;
using namespace std;

struct MethodsNode
{
	__int64 RunTime = 0;
	string Name;
};

__int64 TimeDiff(SYSTEMTIME right, SYSTEMTIME left)//计时函数
{
	CTime tmLeft(left.wYear, left.wMonth, left.wDay, 0, 0, 0);
	CTime tmRight(right.wYear, right.wMonth, right.wDay, 0, 0, 0);
	CTimeSpan sp = tmLeft - tmRight;
	long MillisecondsL = (left.wHour * 3600 + left.wMinute * 60 + left.wSecond) * 1000 + left.wMilliseconds;
	long MillisecondsR = (right.wHour * 3600 + right.wMinute * 60 + right.wSecond) * 1000 + right.wMilliseconds;
	return (__int64)sp.GetDays() * 86400000 + ((__int64)MillisecondsL - (__int64)MillisecondsR);//返回毫秒
}

SortType PrintArrays(int Arrays[], int length)//打印
{
	if (length <= 0)
		return;
	cout << "[ " << Arrays[0];
	for (int i = 0; i < length; ++i)
		cout << ", " << Arrays[i];
	cout << " ]" << endl;
	return;
}

SortType InitArrays(int Arrays[], int length)//初始化
{
	srand((unsigned)time(0));//每次运行之间不一样，运行之内一样
	for (int i = 0; i < length; ++i)
		Arrays[i] = random(len);
	return;
}


/* 快速排序 */
int sort(int d[], int s, int e)
{
	int i = s, j = e - 1, t = d[s];
	while (i < j)
	{
		while (i < j && d[j] >= t)
			j--;
		if (i < j)
			d[i++] = d[j];
		while (i < j && d[i] < t)
			i++;
		if (i < j)
			d[j--] = d[i];
	}
	d[i] = t;
	return i;
}

SortType DgSort(int Arrays[], int s, int e)
{
	int m;
	if (s < e)
	{
		m = sort(Arrays, s, e);
		DgSort(Arrays, s, m);
		DgSort(Arrays, m + 1, e);
	}
	return;
}

SortType QuickSort(int* d, int length)
{
	DgSort(d, 0, length);
	PrintArrays(d, length);
	return;
}


/* 希尔排序 */
SortType InsertSort(int d[], int start, int step, int length)
{
	int i, j, t;
	for (i = start; i < length; i += step)
	{
		t = d[i];
		for (j = i - step; j >= 0 && t < d[j]; j -= step)
			d[j + step] = d[j];
		d[j + step] = t;
	}
	return;
}

SortType ShellSort(int d[], int length)
{
	int step = length >> 1, i;
	while (step)
	{
		for (i = 0; i < step; i++)
			InsertSort(d, i, step, length);
		step /= 2;
	}
	PrintArrays(d, length);
	return;
}


/* 堆排序 */
SortType BigSort(int* d, int s, int length)
{
	int left, right, max, t;
	while (s <= ((length >> 1) - 1))
	{
		left = (s << 1) + 1;
		right = (s + 1) << 1;
		if (right < length)
			max = d[left] > d[right] ? left : right;
		else
			max = left;
		if (d[max] >= d[s])
		{
			t = d[max];
			d[max] = d[s];
			d[s] = t;
			s = max;
		}
		else
			s = length;
	}
	return;
}

SortType HeapSort(int d[], int length)
{
	for (int i = (length >> 1) - 1; i >= 0; --i)
		BigSort(d, i, length);
	int cou = length - 1, t = d[0];
	d[0] = d[cou];
	d[length - 1] = t;
	while (cou > 0)
	{
		BigSort(d, 0, cou);
		t = d[cou - 1];
		d[cou - 1] = d[0];
		d[0] = t;
		cou--;
	}
	PrintArrays(d, length);
	return;
}

int main()
{
	system("chcp 936&title 排序&color e&cls");
	MethodsNode Methods[3] = { NULL }, tmp;
	Methods[0].Name.assign("快速排序");
	Methods[1].Name.assign("希尔排序");
	Methods[2].Name.assign("堆排序");
	SYSTEMTIME start_time, end_time;//声明计时变量
	int Arrays[len] = { 0 };
	for (int i = 0; i < len; ++i)
		Arrays[i] = rand() % MAX;
	InitArrays(Arrays, len);
	cout << "初始化序列：" << endl;
	PrintArrays(Arrays, len);
	cout << endl << "快速排序的序列为：" << endl;
	GetSystemTime(&start_time);//获得初始时间
	QuickSort(Arrays, len);
	GetSystemTime(&end_time);//获得结束时间
	Methods[0].RunTime = TimeDiff(start_time, end_time);
	cout << "耗时：" << Methods[0].RunTime << " 毫秒" << endl << endl;
	InitArrays(Arrays, len);//重新初始化
	cout << "希尔排序的序列为：" << endl;
	GetSystemTime(&start_time);
	ShellSort(Arrays, len);
	GetSystemTime(&end_time);
	Methods[1].RunTime = TimeDiff(start_time, end_time);
	cout << "耗时：" << Methods[1].RunTime << " 毫秒" << endl << endl;
	InitArrays(Arrays, len); 
	cout << "堆排序的序列为：" << endl;
	GetSystemTime(&start_time);
	HeapSort(Arrays, len);
	GetSystemTime(&end_time);
	Methods[2].RunTime = TimeDiff(start_time, end_time);
	cout << "耗时：" << Methods[2].RunTime << " 毫秒" << endl << endl;
	for (int i = 0; i < 3; ++i)
		for (int j = i; j < 3; ++j)
			if (Methods[i].RunTime > Methods[j].RunTime)
			{
				tmp = Methods[i];
				Methods[i] = Methods[j];
				Methods[j] = tmp;
			}
	cout << endl << "本次实验中，排序方式：" << Methods[0].Name << " 优于 " << Methods[1].Name << " 优于 " << Methods[2].Name << "。" << endl;
	system("pause>nul&cls");
	return EXIT_SUCCESS;
}