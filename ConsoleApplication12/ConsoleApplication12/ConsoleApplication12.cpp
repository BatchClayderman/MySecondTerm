#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 900
#define sqr 30
int x[MAX] = { 0 };

void DisplayBoard(char(*board)[sqr], int n)//打印棋盘
{
	int i = 0, j = 0;
	printf("     ");
	for (i = 0; i < n; ++i)
	{
		if (i >= 9)
			printf(" %d ", i + 1);
		else
			printf("  %d  ", i + 1);
	}
	printf("\n");
	for (j = 0; j < n + 1; ++j)
		printf("----|");
	printf("\n");
	for (i = 0; i < n; ++i)
	{
		if (i >= 9)
			printf(" %d |", i + 1);
		else
			printf("  %d |", i + 1);
		for (j = 0; j < n; j++)
			printf("  %c |", board[i][j]);
		printf("\n");
		printf("----|");
		for (j = 0; j < n; j++)
			printf("----|");
		printf("\n");
	}
	printf("\n\n");
}

bool place(int k)//判断能不能放置第i个皇后
{
	int i = 1;
	while (i < k)
	{
		if (x[i] == x[k] || abs(x[i] - x[k]) == abs(i - k))
			return false;
		i++;
	}
	return true;
}

long long int queen(int n)//回溯法
{
	char board[sqr][sqr] = { 0 };
	int i, k = 1, sulotion = 0; //k为当前行号
	x[1] = 0;//x[k]为第k行皇后所放的列号
	while (k > 0)
	{
		x[k]++;
		while (x[k] <= n && !place(k))//该行不符合，则放入下一行
			x[k]++;
		if (x[k] <= n)
		{
			if (k == n)//输出x[]
			{
				for (i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
						board[i][j] = ' ';
					board[i][x[i + 1] - 1] = 'Q';
				}
				sulotion++;//增加计数
				printf("方案 %d：\n", sulotion);
				for (i = 1; i <= n; i++)
				{
					if (i % 5 != 0)
						printf("Q%d：%d\t\t", i, x[i]);
					else
						printf("Q%d：%d\n", i, x[i]);
				}
				printf("\n\n");
				DisplayBoard(board, n);
			}
			else//判断下一行
			{
				k++;
				x[k] = 0;
			}
		}
		else
			k--;//没找到，则回溯
	}
	return sulotion;
}

int main(int argc, char* argv[])//提供命令行接口
{
	int n = 0;
	rewind(stdin);
	if (argc == 2)
	{
		if (sscanf_s(argv[1], "%d", &n) == 1)
		{
			rewind(stdin);
			if (n < 1 || n > sqr)
			{
				printf("\a错误：参数不合法。\n");
				exit(-1);
			}
			else
			{
				printf("\n");
				long long int x = queen(n);
				printf("\n\n%d 个皇后排列方案共有 %lld 个。\n\n\n", n, x);
				exit(0);
			}
		}
		else
		{
			printf("\a错误：命令行参数无效。\n");
			exit(-1);
		}
	}
	else if (argc > 2)
	{
		int count = 0;
		for (int i = 1; i < argc; i++)
		{
			rewind(stdin);
			if (sscanf_s(argv[i], "%d", &n) == 1)
			{
				if (n >= 1 && n <= int(sqrt(MAX)))
				{
					printf("\n%d 个皇后排列方案列举如下：\n", n);
					long long int x = queen(n);
					printf("\n\n%d 个皇后排列方案共有 %lld 个。\n\n\n", n, x);
					count++;
				}
			}
		}
		rewind(stdin);
		if (count == 0)
		{
			printf("\a命令行所有参数均被和谐。\n");
			return -1;
		}
		else
			return count;
	}
	system("chcp 936&title N皇后问题&color e&cls");
	for (;;)
	{
		system("cls");
		rewind(stdin);
		printf("请输入皇后的个数 N（ N 介于 1 - %d，输入其它数字退出）：", sqr);
		if (scanf_s("%d", &n) == 1)
		{
			rewind(stdin);
			if (n > int(sqrt(MAX)) || n < 1)
				break;
		}
		else
		{
			rewind(stdin);
			printf("\a");
			continue;
		}
		rewind(stdin);
		system("cls");
		printf("%d 个皇后排列方案列举如下：\n\n\n", n);
		long long int x = queen(n);
		if (x == 0)
		{
			system("cls");
			printf("很抱歉，%d 个皇后无可用方案，请按任意键返回。\n", n);
		}
		else
			printf("\n\n%d 个皇后排列方案共有 %lld 个，请按任意键返回。\n", n, x);
		system("pause>nul");
	}
	system("cls");
	printf("欢迎再次使用，请按任意键退出。\n");
	system("pause>nul&cls");
	return 0;
}