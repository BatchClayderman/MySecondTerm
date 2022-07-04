#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define NAME_MAX 21
#define SEX_MAX 3
#define TEL_MAX 26
#define UNIVERSITY_MAX 16
#define STREET_MAX 21
#define CITY_MAX 21
#define MAIL_MAX 11
#define COUNTRY_MAX 21
#define PEOPLE_MAX 51
using namespace std;
extern HHOOK hHook;
extern LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam);
HHOOK hHook;

LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("男"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("女"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

typedef struct LINK
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tel[TEL_MAX];
	char university[UNIVERSITY_MAX];
	char street[STREET_MAX];
	char city[CITY_MAX];
	char mail[MAIL_MAX];
	char country[COUNTRY_MAX];
}linkman;

typedef struct PEOPLE{//定义结构体
	int num;
	linkman count[PEOPLE_MAX];
}*people;

int* search(people cou, char* name, int lists[PEOPLE_MAX])//确定联系人位置
{
	int i = 0, j = 1;
	for (i = 0; i < cou->num; i++)
		if (strcmp(name, (cou->count[i]).name) == 0)
		{
			lists[j] = i;
			j++;
		}
	lists[0] = j - 1;
	return lists;
}

void add_linkman(people cou)//添加联系人
{
	if (cou->num >= PEOPLE_MAX - 1)
	{
		printf("\a该通讯录已满，无法录入信息！请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	printf("请输入姓名（最多%d个字符）：\n", NAME_MAX - 1);
	fgets((cou->count[cou->num]).name, NAME_MAX, stdin);
	rewind(stdin);
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	int errorcontrol = 6;
	if (hHook)
		errorcontrol = MessageBox(NULL, TEXT("该联系人的性别是？"), TEXT("添加联系人"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	else
		errorcontrol=MessageBox(NULL, TEXT("该联系人是否为男性？"), TEXT("添加联系人"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	if (errorcontrol ==6)
		strcpy_s((cou->count[cou->num]).sex, "男");
	else
		strcpy_s((cou->count[cou->num]).sex, "女");
	printf("输入的性别：%s\n", (cou->count[cou->num]).sex);
	printf("请输入年龄：\n");
	while (scanf_s("%d", &(cou->count[cou->num]).age) != 1)
	{
		printf("\a请重新输入年龄：\n");
		rewind(stdin);
	}
	rewind(stdin);
	printf("请输入电话号码（最多%d个字符）：\n", TEL_MAX - 1);
	fgets((cou->count[cou->num]).tel, TEL_MAX, stdin);
	rewind(stdin);
	printf("请输入所在大学（最多%d个字符）：\n", UNIVERSITY_MAX - 1);
	fgets((cou->count[cou->num]).university, UNIVERSITY_MAX, stdin);
	rewind(stdin);
	printf("请输入街道（最多%d个字符）：\n", STREET_MAX - 1);
	fgets((cou->count[cou->num]).street, STREET_MAX, stdin);
	rewind(stdin);
	printf("请输入城市（最多%d个字符）：\n", CITY_MAX - 1);
	fgets((cou->count[cou->num]).city, CITY_MAX, stdin);
	rewind(stdin);
	printf("请输入邮编（最多%d个字符）：\n", MAIL_MAX - 1);
	fgets((cou->count[cou->num]).mail, MAIL_MAX, stdin);
	rewind(stdin);
	printf("请输入国家（最多%d个字符）：\n", COUNTRY_MAX - 1);
	fgets((cou->count[cou->num]).country, COUNTRY_MAX, stdin);
	rewind(stdin);
	cou->num++;
	printf("\n添加联系人成功，请按任意键返回。\n");
	system("pause>nul");
	return;
}

void delete_linkman(people cou)//删除联系人
{
	int lists[PEOPLE_MAX] = { 0 };
	char name[NAME_MAX], Ens = 'N';
	if (cou->num == 0)
	{
		printf("\a该通讯录已空，无法删除信息！请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	printf("请输入要删除人的名字：\n");
	fgets(name, NAME_MAX, stdin);
	rewind(stdin);
	int* ret = search(cou, name, lists);
	if (ret[0] == 0)
	{
		printf("\a错误：指定的联系人不存在！请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	else if (ret[0] == 1)
	{
		int Ens = MessageBox(NULL, L"确认要删除该联系人吗？", L"删除联系人", MB_YESNO | MB_ICONWARNING);
		if (Ens == 7)
			return;
		for (int j = ret[0]; j < cou->num; j++)
			cou->count[j] = cou->count[j + 1];
		cou->num--;
	}
	else
	{
		int Ens = MessageBox(NULL, L"警告：联系人不唯一，是否继续？", L"删除多个联系人", MB_YESNO | MB_ICONWARNING);
		if (Ens == 7)
			return;
		for (int i = 1; i <= ret[0]; i++)
		{
			for (int j = ret[i]; j < cou->num; j++)
				cou->count[j] = cou->count[j + 1];
			cou->num--;
		}
	}
	printf("\n删除联系人成功，请按任意键返回。\n");
	system("pause>nul");
	return;
}

void find_linkman(people cou)//查找联系人
{
	int lists[PEOPLE_MAX] = { 0 };
	char name[NAME_MAX];
	if (cou->num == 0)
	{
		printf("\a当前为空表，请按任意键返回。\n");
		system("cls");
		return;
	}
	printf("请输入要查找人的名字：\n");
	fgets(name, NAME_MAX, stdin);
	rewind(stdin);
	int* ret = search(cou, name, lists);
	if (ret[0] == 0)
		printf("\a此联系人不存在，查找失败！\n");
	else
	{
		printf("共搜索到 %d 名联系人：\n", ret[0]);
		for (int i = 1; i <= ret[0]; i++)
			printf("\n\n姓名：%s性别：%s\n年龄：%d\n电话：%s所在大学：%s街道：%s城市：%s邮编：%s国家：%s\n\n", (cou->count[ret[i]]).name, (cou->count[ret[i]]).sex, (cou->count[ret[i]]).age, (cou->count[ret[i]]).tel, (cou->count[ret[i]]).university, (cou->count[ret[i]]).street, (cou->count[ret[i]]).city, (cou->count[ret[i]]).mail, (cou->count[ret[i]]).country);
	}
	printf("\n\n枚举完成，请按任意键返回。\n");
	system("pause>nul");
}

void change_linkman(people cou)//修改指定人信息
{
	int lists[PEOPLE_MAX] = { 0 };
	if (cou->num == 0)
	{
		printf("\a当前列表为空，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	char name[NAME_MAX];
	printf("请输入要修改人的名字：\n");
	fgets(name, NAME_MAX, stdin);
	int* ret = search(cou, name, lists);
	if (ret[0] == 0)
	{
		printf("\a联系人不存在，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	else if(ret[0]==1)
	{
		printf("请输入新联系人的姓名（最多%d个字符）：\n", NAME_MAX - 1);
		fgets((cou->count[ret[1]]).name, NAME_MAX, stdin);
		rewind(stdin);
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
		int errorcontrol = 6;
		if (hHook)
			errorcontrol = MessageBox(NULL, TEXT("该联系人的性别是？"), TEXT("修改联系人"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
		else
			errorcontrol = MessageBox(NULL, TEXT("该联系人是否为男性？"), TEXT("修改联系人"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
		if (errorcontrol == 6)
			strcpy_s((cou->count[cou->num]).sex, "男");
		else
			strcpy_s((cou->count[cou->num]).sex, "女");
		printf("输入的性别：%s\n", (cou->count[cou->num]).sex);
		printf("请输入年龄：\n");
		while (scanf_s("%d", &(cou->count[ret[1]]).age) != 1)
		{
			printf("\a请重新输入年龄：\n");
			rewind(stdin);
		}
		rewind(stdin);
		printf("请输入电话号码（最多%d个字符）：\n", TEL_MAX - 1);
		fgets((cou->count[ret[1]]).tel, TEL_MAX, stdin);
		rewind(stdin);
		printf("请输入所在大学（最多%d个字符）：\n", UNIVERSITY_MAX - 1);
		fgets((cou->count[ret[1]]).university, UNIVERSITY_MAX, stdin);
		rewind(stdin);
		printf("请输入街道（最多%d个字符）：\n", STREET_MAX - 1);
		fgets((cou->count[ret[1]]).street, STREET_MAX, stdin);
		rewind(stdin);
		printf("请输入城市（最多%d个字符）：\n", CITY_MAX - 1);
		fgets((cou->count[ret[1]]).city, CITY_MAX, stdin);
		rewind(stdin);
		printf("请输入邮编（最多%d个字符）：\n", UNIVERSITY_MAX - 1);
		fgets((cou->count[ret[1]]).mail, MAIL_MAX, stdin);
		rewind(stdin);
		printf("请输入国家（最多%d个字符）：\n", COUNTRY_MAX - 1);
		fgets((cou->count[ret[1]]).country, COUNTRY_MAX, stdin);
		rewind(stdin);
	}
	else
	{
		printf("\n\n\a该联系人在列表中不唯一，不提供修改操作。\n如果重名联系人太多，建议使用自动重命名功能，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
}

void display_linkman(people cou)//显示所有联系人
{
	int i = 0;
	if (cou->num == 0)
	{
		printf("联系人列表为空，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	printf("共有 %d 位联系人，列出如下：\n\n\n", cou->num);
	for (i = 0; i < cou->num; i++)
		printf("\n姓名：%s性别：%s\n年龄：%d\n电话：%s所在大学：%s街道：%s城市：%s邮编：%s国家：%s\n\n", (cou->count[i]).name, (cou->count[i]).sex, (cou->count[i]).age, (cou->count[i]).tel, (cou->count[i]).university, (cou->count[i]).street, (cou->count[i]).city, (cou->count[i]).mail, (cou->count[i]).country);
	printf("\n\n显示完毕，请按任意键返回。\n");
	system("pause>nul");
	return;
}

void empty_linkman(people cou)//清空所有联系人
{
	system("color 4f");
	int Ens = MessageBox(NULL, L"警告：操作具有风险，确定要继续吗？", L"清空通讯录", MB_YESNO | MB_ICONWARNING);
	if (Ens == 7)
	{
		system("color e");
		return;
	}
	cou->num = 0;
	system("cls");
	printf("已清空所有通讯录，请按任意键返回。\n");
	system("pause>nul&color e");
	return;
}

void name_sort(people cou)//按名字顺序排序所有人
{
	int i = 0, j = 0;
	if (cou->num == 0)
	{
		printf("\a通讯录为空，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	for (i = 0; i < cou->num - 1; i++)
		for (j = 0; j < cou->num - i - 1; j++)
			if (strcmp(cou->count[j].name, (cou->count[j + 1]).name) > 0)
			{
				linkman tmp = cou->count[j];
				cou->count[j] = cou->count[j + 1];
				cou->count[j + 1] = tmp;
			}
	printf("操作成功结束，请按任意键返回。\n");
	system("pause>nul");
	return;
}

void name_rename(people cou)//重命名指定重复联系人
{
	int lists[PEOPLE_MAX] = { 0 };
	if (cou->num == 0)
	{
		printf("\a通讯录为空，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	char name[NAME_MAX];
	char str[NAME_MAX][3] = { { 0 } };
	printf("请输入要自动重命名重名人的名字：\n");
	fgets(name, NAME_MAX, stdin);
	if (strlen(name) >= NAME_MAX - 3)
	{
		printf("\n\n\a错误：联系人名字太长，存储空间不足，修改失败！\n您可以尝试重新新建联系人，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	int* ret = search(cou, name, lists);
	if (ret[0] == 0)
	{
		printf("\a联系人不存在，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	else if (ret[0] == 1)
	{
		printf("\a联系人唯一，无需执行自动重命名，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
	else
	{
		printf("\n\n正在执行重命名，请稍候。\n");
		for (int i = 1; i <= ret[0]; i++)
		{
			sprintf_s(str[i], "%d", i);
			(cou->count[ret[i]]).name[strlen((cou->count[ret[i]]).name) - 1] = '\0';
			strcat_s((cou->count[ret[i]]).name, "_");
			strcat_s((cou->count[ret[i]]).name, str[i]);
			strcat_s((cou->count[ret[i]]).name, "\n");
		}
		printf("\n操作成功结束，请按任意键返回。\n");
		system("pause>nul");
		return;
	}
}

int menu()//打印目录并获取选择
{
	int x = 0;
	system("cls");
	printf("**************************************\n");
	printf("********* 1 = 添加联系人信息 *********\n");
	printf("******* 2 = 删除指定联系人信息 *******\n");
	printf("******* 3 = 查找指定联系人信息 *******\n");
	printf("******* 4 = 修改指定联系人信息 *******\n");
	printf("******* 5 = 显示所有联系人信息 *******\n");
	printf("***** 6 = 清空所有联系人（风险） *****\n");
	printf("****** 7 = 以名字排序所有联系人 ******\n");
	printf("****** 8 = 重命名指定同名联系人 ******\n");
	printf("************** 0 = 退出 **************\n");
	printf("**************************************\n");
	printf("\n\n请选择一项以继续：");
	if (scanf_s("%d", &x) == 1)
	{
		if (x < 0 || x > 8)
			return menu();
		else
			return x;
	}
	else
		return menu();
}

int main()
{
	system("chcp 936&title 通讯录管理系统&color e&cls");
	int opp = 1;
	struct PEOPLE cou;
	cou.num = 0;
	while (opp)
	{
		opp = menu();
		rewind(stdin);
		system("cls");
		switch (opp)
		{
		case 0:
		{
			system("cls");
			printf("欢迎再次使用，请按任意键退出。\n");
			system("pause>nul&cls");
			exit(EXIT_FAILURE);
			break;
		}
		case 1:
		{
			add_linkman(&cou);
			break;
		}
		case 2:
		{
			delete_linkman(&cou);
			break;
		}
		case 3:
		{
			find_linkman(&cou);
			break;
		}
		case 4:
		{
			change_linkman(&cou);
			break;
		}
		case 5:
		{
			display_linkman(&cou);
			break;
		}
		case 6:
		{
			empty_linkman(&cou);
			break;
		}
		case 7:
		{
			name_sort(&cou);
			break;
		}
		case 8:
		{
			name_rename(&cou);
			break;
		}
		}
	}
	return -1;
}