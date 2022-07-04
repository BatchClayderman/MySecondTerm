#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
char Alpha[N] = "abcdefghijklmnopqrstuvwxyz";
char Num[N] = "0123456789";

int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

char* V(char n1[N], char n2[N], char* result, int option)
{
	char text1[N] = { 0 }, text2[N] = { 0 };
	int i = 0, j = 0, r = 0, s = 0;
	for (i = 0; i < N; i++)
	{
		if (n1[i] >= 'a' && n1[i] <= 'z')
		{
			text1[j] = n1[i];
			j++;
		}
		else if (n1[i] >= 'A' && n1[i] <= 'Z')
		{
			text1[j] = n1[i] + 32;
			j++;
		}
	}
	j = 0;
	for (i = 0; i < N; i++)
	{
		if (n2[i] >= '0' && n2[i] <= '9')
		{
			text2[j] = n2[i];
			j++;
		}
	}
	printf("处理后的字符串：\n>> %s\n>> %s\n", text1, text2);
	if (strlen(text1) == 0 || strlen(text2) == 0)
	{
		printf("\a错误：输入的字符串非法。");
		return result;
	}
	for (i = 0; i < max(strlen(text1),strlen(text2)); i++)
	{
		for (j = 0; j < 26; j++)
			if (Alpha[j] == text1[i % strlen(text1)])
				s = j;
		for (j = 0; j < 10; j++)
			if (Num[j] == text2[i % strlen(text2)])
			{
				if (option == 1)
					s += j;
				else
					s -= j;
			}
		s = (s + 260) % 26;
		result[i] = Alpha[s];
	}
	return result;
}

int main()
{
	system("chcp 936&title 维吉尼亚算法&color e");
	char n1[N] = { 0 }, n2[N] = { 0 }, result[N] = { 0 }, Ens = 'Y';
	int option;
	rewind(stdin);
m:
	for (int i = 0; i < N; i++)
		result[i] = { '\0' };
	system("cls");
	printf("1 = 加密\t\t2 = 解密\t\t0 = 退出\n请选择一项以继续：");
	if (scanf_s("%d", &option) == 1)
	{
		system("cls");
		rewind(stdin);
		if (option == 1)
			goto encode;
		else if (option == 2)
			goto decode;
		else if (option == 0)
			return 0;
		else
			goto m;
	}
	else
	{
		rewind(stdin);
		goto m;
	}
encode:
	printf("请输入明文（最多 %d 位）：", N - 1);
	fgets(n1, N, stdin);
    rewind(stdin);
    printf("请输入数字密钥（最多 %d 位）：", N - 1);
	fgets(n2, N, stdin);
    rewind(stdin);
    system("cls");
	V(n1, n2, result, option);
	if (strlen(result) != 0)
		printf("\n输出密文：\n%s\n", result);
	goto end;
decode:
	printf("请输入密文（最多 %d 位）：", N - 1);
	fgets(n1, N, stdin);
	rewind(stdin);
	printf("请输入数字密钥（最多 %d 位）：", N - 1);
	fgets(n2, N, stdin);
	rewind(stdin);
	system("cls");
	V(n1, n2, result, option);
	if (result[0] != '\0')
		printf("\n输出明文：\n%s\n", result);
	goto end;
end:
	printf("\n\n\n输入“E”或“e”退出程序，输入其它回车继续。\n");
    scanf_s("%c", &Ens, sizeof(Ens));
    rewind(stdin);
    if (Ens == 'E' || Ens == 'e')
    {
        system("cls");
        exit(0);
    }
    else
    {
		rewind(stdin);
		goto m;
    }
    return -1;
}