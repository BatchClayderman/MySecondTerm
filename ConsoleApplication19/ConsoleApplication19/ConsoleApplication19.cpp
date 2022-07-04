#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mod(int x, int m)//实数通用的求模运算
{
	int _x = x;
	while (_x < 0)
		_x += m;
	return _x % m;
}

int lrd(int p1, int p2)//勒让德符号
{
	if (p1 == 0)
		return 0;
	int count = 0;
	for (int i = 0; i < p2; i++)
		if (mod(i * i, p2) == mod(p1, p2))
			count++;
	return count ? count : -1;
}

int main(int argc, char* argv[])//主程序
{
	int p1, p2, result;
	char Ens = 'Y';
	if (argc == 3)//处理命令行参数
	{
		rewind(stdin);
		if (sscanf_s(argv[1], "%d", &p1) == 1 && sscanf_s(argv[2], "%d", &p2) == 1)
		{
			printf("%d\n", lrd(p1, p2));
			return 0;
		}
		else
		{
			printf("\a错误：所输入的参数不合法。\n");
			return -1;
		}
	}
	else if (argc != 1)
	{
		printf("\a错误：命令行参数数目不正确。\n");
		return -1;
	}
	system("chcp 936&title 勒让德符号&color e");
	while (true)
	{
		system("cls");
		printf("请输入p1：");
		rewind(stdin);
		if (scanf_s("%d", &p1) != 1)
			continue;
		printf("请输入p2：");
		rewind(stdin);
		if (scanf_s("%d", &p2) != 1)
			continue;
		result = lrd(p1, p2);
		if (result == -1)
			printf("\nlrd(p1|p2) = -1\n解数：0\n");
		else
			printf("\nlrd(p1|p2) = 1\n解数：%d\n", result);
		printf("\n\n输入“E”或“e”退出程序，输入其它或直接回车运行新运算。\n");
		rewind(stdin);
		scanf_s("%c", &Ens, sizeof(Ens));
		if (Ens == 'E' || Ens == 'e')
			break;
	}
	rewind(stdin);
	system("cls");
	return 0;
}