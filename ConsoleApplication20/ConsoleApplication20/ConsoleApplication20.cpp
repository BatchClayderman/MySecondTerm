#include <iostream>
#include <time.h>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef Cut
#define Cut 3
#endif
#ifndef Count
#define Count 10
#endif
using namespace std;
typedef int ElemType;
typedef int Location;

void SwapElem(ElemType* a, ElemType* b)//交换元素
{
	ElemType tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void InsertionSort(ElemType A[], Location N)
{
	Location i, j, tmp;
	for (i = 1; i < N; i++)
	{
		tmp = A[i];
		for (j = i; j > 0 && A[j - 1] > tmp; j--)
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}

ElemType Matches(ElemType A[], Location Left, Location Right)
{
	Location Center = (Left + Right) >> 1;
	if (A[Left] > A[Center])
		SwapElem(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		SwapElem(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		SwapElem(&A[Center], &A[Right]);
	SwapElem(&A[Center], &A[Right - 1]);
	return A[Right - 1];
}

void QuickSelect(ElemType A[], int k, int Left, int Right)
{
	ElemType Pivot;
	int i, j;
	if (Left + Cut <= Right)
	{
		Pivot = Matches(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				SwapElem(&A[i], &A[j]);
			else
				break;
		}
		SwapElem(&A[i], &A[Right - 1]);
		if (k <= i)
			QuickSelect(A, k, Left, i - 1);
		else if (k > i + 1)
			QuickSelect(A, k, i + 1, Right);
	}
	else
		InsertionSort(A + Left, Right - Left + 1);//元素少于 Cut 个，可用直接插入排序
}

int main()
{
	system("chcp 936&title 快速选择&color e&cls");
	ElemType data[Count];
	srand((unsigned int)time_t(0));
	for (int i = 0; i < Count; ++i)
		data[i] = rand();
	cout << "随机生成数据如下：" << endl << "[ ";
	for (int i = 0; i < Count; i++)
		cout << data[i] << ", ";
	cout << "]" << endl << endl;
	int k;
	cout << "请输入您想要的第 k 小元素的 k 值：";
	rewind(stdin);
	while (scanf_s("%d", &k) != 1 || k > Count || k <= 0)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	rewind(stdin);
	QuickSelect(data, k, 0, Count - 1);
	cout << endl << "部分排序后数据如下：" << endl << "[ ";
	for (int i = 0; i < Count; i++)
		cout << data[i] << ", ";
	cout << "]" << endl << endl;
	cout << "原序列中第 " << k << " 小的元素的值为 " << data[k - 1] << "。" << endl;
	system("pause>nul&cls");
	return EXIT_SUCCESS;
}