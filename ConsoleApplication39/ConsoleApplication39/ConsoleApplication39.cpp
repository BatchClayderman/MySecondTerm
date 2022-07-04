#include <iostream>
#include <Windows.h>
#define MAX 100
#define EQ(a,b) (a==b)//相等
#define LT(a,b) (a<b)//小于
typedef int ElemType;
typedef int Location;
using namespace std;

typedef struct ArrType//伪数组元素
{
	ElemType elem;
};

typedef struct Array//伪数组
{
	ArrType* elem;
	int length;
};

Array BubbleSort(Array& ST)//冒泡排序
{
	int i, j, tmp, l = ST.length;
	while (l > 1)
	{
		for (i = 1, j = 1; i < l; ++i)
		{
			if (ST.elem[i].elem > ST.elem[i + 1].elem)
			{
				tmp = ST.elem[i].elem;
				ST.elem[i].elem = ST.elem[i + 1].elem;
				ST.elem[i + 1].elem = tmp;
				j = i;
			}
		}
		l = j;
	}
	return ST;
}

ElemType GetElem(ElemType max, ElemType min)//获取整型
{
	ElemType num;
	rewind(stdin);
	while (scanf_s("%d", &num) != 1 || (max == NULL ? false : num > max) || (min == NULL ? false : num < min))
	{
		rewind(stdin);
		cout << "\a输入有误，请重新输入：";
	}
	return num;
}

Array InitArray(Array& ST, int n)//初始化
{
	ST.elem = (ArrType*)malloc((n + 1) * sizeof(ArrType));
	if (!ST.elem)
	{
		cout << "内存资源不足，请确保您的空间充足，并请按任意键退出。" << endl;
		system("pause>nul&cls");
		exit(OVERFLOW);
	}
	ST.length = n;
	for (int i = 1; i <= n; ++i)
	{
		cout << "请输入第 " << i << " 个元素：";
		ST.elem[i].elem = GetElem(NULL, NULL);
	}
	return ST;
}

Location SearchQueue(Array ST, ElemType elem)//顺序查找
{
	ST.elem[0].elem = elem;
	Location i = ST.length;
	while (!EQ(ST.elem[i].elem, elem))
		i--;
	return i;
}

Location SearchBinary(Array ST, ElemType elem)//折半查找
{
	Location high = ST.length, low = 1, mid;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);
		if (EQ(elem, ST.elem[mid].elem))
			return mid;
		else if (LT(elem, ST.elem[mid].elem))
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void PrintArray(Array ST)//打印
{
	cout << "当前顺序表打印如下：" << endl << "[ " << ST.elem[1].elem;
	for (int i = 2; i <= ST.length; ++i)
		cout << ", " << ST.elem[i].elem;
	cout << " ]" << endl;
	return;
}

int main()
{
	system("chcp 936&title 顺序与折半查找&color e&cls");
	Array ST;
	ElemType elem;
	Location location;
	int n;
	cout << "请输入元素的个数（最大值为 " << MAX << "）：";
	n = GetElem(MAX, 1);
	ST = InitArray(ST, n);
	cout << "请输入需要进行顺序查找的关键字：";
	elem = GetElem(NULL, NULL);
	cout << endl << "正在使用顺序查找法查找元素 " << elem << "，请稍候。" << endl;
	PrintArray(ST);
	location = SearchQueue(ST, elem);
	if (location == 0)
		cout << endl << "很抱歉，未能找到指定元素—“" << elem << "”。" << endl;
	else
		cout << "元素 " << elem << " 为表中的第 " << location << " 个索引。" << endl;
	cout << endl << "正在使用折半查找法查找元素 " << elem << "，请稍候。" << endl;
	cout << "排序完成，";
	PrintArray(BubbleSort(ST));
	location = SearchBinary(ST, elem);
	if (location == 0)
		cout << "很抱歉，未能找到指定元素—“" << elem << "”。" << endl;
	else
		cout << "元素 " << elem << " 位于表中的第 " << location << " 个位置。" << endl;
	MessageBox(NULL, TEXT("演示完毕，请点击“确定”退出。"), TEXT("杨淯而 2019052202"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	system("cls");
	return 0;
}