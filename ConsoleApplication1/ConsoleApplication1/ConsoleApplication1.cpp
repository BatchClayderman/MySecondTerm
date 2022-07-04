#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
typedef ElemType* Triplet;
using namespace std;

void error(void)
{
	system("cls");
	printf("\a错误：所输入的整数不合法，请按任意键重新输入。\n");
	rewind(stdin);
	system("pause>nul&cls");
	return;
}

Status InitTriplet(Triplet& T, int v1, int v2, int v3)
{
	T = (ElemType*)malloc(3 * sizeof(ElemType));//申请内存
	if (!T)return ERROR;
	T[0] = v1;
	T[1] = v2;
	T[2] = v3;
	return OK;
}

Status GetElem(Triplet T, int i, ElemType& e)
{
	if (i < 1 || i > 3)
		return ERROR;
	e = T[i - 1];
	return OK;
}

Status Destroy(Triplet& T)
{
	free(T);//释放内存
	T = NULL;
	return OK;
}

Status SetElem(Triplet& T, int i, ElemType e)
{
	if (i < 1 || i > 3)
		return ERROR;
	T[i - 1] = e;
	return OK;
}

Status Max(Triplet T, ElemType& e)
{
	e = T[0] > T[1] ? T[0] : T[1];
	e = e > T[2] ? e : T[2];
	return OK;
}

Status Min(Triplet T, ElemType& e)
{
	e = T[0] < T[1] ? T[0] : T[1];
	e = e < T[2] ? e : T[2];
	return OK;
}

Status show(Triplet& T)
{
	printf("T = (%d, %d, %d)\n", T[0], T[1], T[2]);
	return 0;
}

int main()
{
	system("chcp 936&title 三元组（姓名：杨淯而，学号：2019052202）&color e&cls");
	printf("现在我们将使用C语言建立一个三元组，请按任意键开始。\n");
	system("pause>nul");
	Triplet T;
	ElemType v1, v2, v3;
a:
	system("cls");
	printf("请输入第一个整数：");
	if (scanf_s("%d", &v1) != 1)
	{
		error();
		goto a;
	}
	rewind(stdin);
b:
	system("cls");
	printf("请输入第二个整数：");
	if (scanf_s("%d", &v2) != 1)
	{
		error();
		goto b;
	}
	rewind(stdin);
c:
	system("cls");
	printf("请输入第三个整数：");
	if (scanf_s("%d", &v3) != 1)
	{
		error();
		goto c;
	}
	rewind(stdin);
	system("cls");
	if (not (InitTriplet(T, v1, v2, v3)))
	{
		printf("\a建立三元组失败！请按任意键退出程序。\n");
		system("pause>nul");
		exit(-1);
	}
	int i;
	ElemType e;
d:
	system("cls");
	show(T);
	printf("现在我们将获取三元组的数值，请输入位置（1/2/3）：");
	if (scanf_s("%d", &i) != 1)
	{
		error();
		goto d;
	}
	rewind(stdin);
	if (GetElem(T, i, e))
		printf("获取成功，位置 %d 上的值为 %d，", i, e);
	else
		printf("\a获取失败！");
	printf("请按任意键继续。\n");
	system("pause>nul");
e:
	system("cls");
	printf("现在我们将修改三元组的值，请输入位置（1/2/3）：");
	if (scanf_s("%d", &i) != 1)
	{
		error();
		goto e;
	}
	rewind(stdin);
f:
	system("cls");
	printf("请为位置为%d的元素指定一个值：", i);
	if (scanf_s("%d", &e) != 1)
	{
		error();
		goto f;
	}
	rewind(stdin);
	system("cls");
	if (SetElem(T, i, e))
		printf("修改成功！\n");
	else
		printf("\a修改失败！\n");
	show(T);
	printf("三元组T中的最大值为 %d，最小值为 %d。\n", Max(T, e), Min(T, e));
	printf("实验结束，请按下任意键，销毁三元组。\n");
	system("pause>nul");
	system("cls");
	if (Destroy(T))
		printf("销毁成功！");
	else
		printf("\a销毁失败！");
	printf("请按任意键退出本程序。\n");
	system("pause>nul&cls");
	return 0;
}