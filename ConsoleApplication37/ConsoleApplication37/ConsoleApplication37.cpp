#include <iostream>
#include <string>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 0
#endif
#ifndef MAX
#define MAX 1000
#endif
typedef void SortType;
using namespace std;

struct StudentNode
{
	string Name;
	int Score = 0;//成绩
	int ID = 0;//排名
};

struct Students
{
	StudentNode Stu[MAX];
	int Count = 0;
};
Students St;


/* 堆排序 */
SortType BigSort(int s, int length)
{
	int left, right, max;
	StudentNode t;
	while (s <= ((length >> 1) - 1))
	{
		left = (s << 1) + 1;
		right = (s + 1) << 1;
		if (right < length)
			max = St.Stu[left].Score > St.Stu[right].Score ? left : right;
		else
			max = left;
		if (St.Stu[max].Score >= St.Stu[s].Score)
		{
			t = St.Stu[max];
			St.Stu[max] = St.Stu[s];
			St.Stu[s] = t;
			s = max;
		}
		else
			s = length;
	}
	return;
}

SortType HeapSort()
{
	if (St.Count <= 0)
		return;
	for (int i = (St.Count >> 1) - 1; i >= 0; --i)
		BigSort(i, St.Count);
	int cou = St.Count - 1;
	StudentNode t = St.Stu[0];
	St.Stu[0] = St.Stu[cou];
	St.Stu[St.Count - 1] = t;
	while (cou > 0)
	{
		BigSort(0, cou);
		t = St.Stu[cou - 1];
		St.Stu[cou - 1] = St.Stu[0];
		St.Stu[0] = t;
		cou--;
	}
	for (int i = 0; i < St.Count >> 1; ++i)
	{
		t = St.Stu[i];
		St.Stu[i] = St.Stu[St.Count - 1 - i];
		St.Stu[St.Count - 1 - i] = t;
	}
	return;
}

SortType Mark()
{
	if (St.Count <= 0)
		return;
	int ID = 1, Score = St.Stu[0].Score;
	St.Stu[0].ID = 1;//排除第一个
	for (int i = 1; i < St.Count; ++i)
	{
		if (St.Stu[i].Score != St.Stu[i - 1].Score)//分数不相等时
		{
			ID = i + 1;
			Score = St.Stu[i].Score;
		}
		St.Stu[i].ID = ID;
	}
	return;
}


/* 主函数 */
int main()
{
	system("chcp 936&title 学生成绩统计系统——排序&color e&cls");
	cout << "请输入学生个数：";
	rewind(stdin);
	while (scanf_s("%d", &St.Count) != 1 || St.Count <= 0 || St.Count > MAX)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	for (int i = 0; i < St.Count; ++i)
	{
		cout << "请输入第 " << i + 1 << " 个学生的姓名：";
		rewind(stdin);
		getline(cin, St.Stu[i].Name);
		cout << "请输入第 " << i + 1 << " 个学生的成绩：";
		rewind(stdin);
		while (scanf_s("%d", &St.Stu[i].Score) != 1 || St.Stu[i].Score < 0 || St.Stu[i].Score > 100)
		{
			cout << "\a输入有误，请重新输入：";
			rewind(stdin);
		}
	}
	HeapSort();
	Mark();
	system("cls");
	cout << "排名\t\t成绩\t\t姓名" << endl;
	cout << "==========\t==========\t==========" << endl << endl;
	for (int i = 0; i < St.Count; ++i)
		cout << St.Stu[i].ID << "\t\t" << St.Stu[i].Score << "\t\t" << St.Stu[i].Name << endl;
	cout << endl << endl << endl << "杨淯而 2019052202" << endl;
	system("pause>nul&cls");
	return EXIT_SUCCESS;
}