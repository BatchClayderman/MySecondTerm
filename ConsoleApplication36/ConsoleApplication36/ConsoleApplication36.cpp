#include <iostream>
#define MAX 400
using namespace std;

int Getint(int max_num, int min_num)//获取整型元素值
{
	rewind(stdin);
	int num = 0;
	while (scanf_s("%d", &num) != 1 || (max_num == NULL ? false : num > max_num) || num < min_num)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	rewind(stdin);
	return num;
}

void InitList(int data[], int length, int Step)//初始化
{
	for (int i = 0; i < length; ++i)
		data[i] = i * Step;
	return;
}

void PrintList(int data[], int length)//打印
{
	cout << "当前数组打印如下：" << endl << "[ " << data[0];
	for (int i = 1; i < length; ++i)
		cout << ", " << data[i];
	cout << " ]" << endl << endl;
	return;
}

int BinarySearch(int array[], int length, int elem)//二分查找插入位置
{
	int low = 0, high = length - 1, mid = 0;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);
		if (array[mid] == elem)
			return -1;//重复元素返回-1
		else if (array[mid] > elem)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

bool InsertSort(int data[], int length, int elem)//插入元素
{
	if (data == NULL || length <= 0 || length >= MAX || elem < 0)
		return false;
	int index = BinarySearch(data, length, elem), i = length;
	if (index == -1)
	{
		cout << "\a错误：元素 " << elem << " 已存在，无需插入。" << endl << endl;
		return false;
	}
	for (i = length; i > index; i--)
		data[i] = data[i - 1];
	data[i] = elem;
	return true;
}

int main()
{
	system("chcp 936&title 二分查找实现元素插入&color e&cls");
	int data[MAX] = { 0 }, length, Step, x;
	cout << "请输入长度（最大值为 " << MAX << "）：";
	length = Getint(MAX, 1);
	cout << "请输入步长（最大值为 " << MAX << "）：";
	Step = Getint(MAX, 2);
	cout << endl;
	InitList(data, length, Step);
	PrintList(data, length);
	cout << "请输入待插入的元素：";
	x = Getint(NULL, 0);
	cout << endl;
	PrintList(data, (InsertSort(data, length, x) ? ++length : length));
	cout << "演示完毕，请按任意键退出本程序。" << endl;
	system("pause>nul&cls");
	return 0;
}