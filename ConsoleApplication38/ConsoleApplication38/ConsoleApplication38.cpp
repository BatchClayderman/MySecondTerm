#include <iostream>
#include <Windows.h>
#include <time.h>

#ifndef _ForceCV_H
#define _ForceCV_H
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif
#ifndef OK
#define OK 1
#endif
#ifndef ERROR
#define ERROR 0
#endif
#ifndef VOID
#define VOID void
#endif
#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef MAXSIZE
#define MAXSIZE 8000
#endif
#ifndef DefaultTime
#define DefaultTime 5
#endif
#ifndef MaxRandTime
#define MaxRandTime 10
#endif
#ifndef MaxTime
#define MaxTime 30
#endif
#endif//_ForceCV_H

using namespace std;
typedef char ElemType;
typedef int Status;
typedef void Function;
typedef void SendKeyFunc;
bool Reverse = false;
int DDLtime = DefaultTime;


/* 栈 */
typedef struct//顺序栈的数据类型
{
	ElemType* base;
	ElemType* top;
	int stacksize;
}Stack;
Stack A;

Status Init(Stack& S)//初始化顺序栈
{
	S.base = new ElemType[MAXSIZE];
	if (!S.base)
		return ERROR;
	*S.base = 0;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

Status Push(Stack& S, ElemType x)//入栈
{
	if (S.top - S.base == S.stacksize)
	{
		//cout << "\a>> 错误：栈空间已满，压入元素 " << x << " 失败！" << endl;
		return ERROR;
	}
	*S.top++ = x;
	//cout << ">> 压入元素 " << x << " 成功。" << endl;
	return OK;
}

Status Pop(Stack& S, ElemType& e)//出栈
{
	if (S.top == S.base)
	{
		//cout << "\a>> 错误：栈为空！" << endl;
		e = 0;
		return ERROR;
	}
	e = *--S.top;
	//cout << ">> 元素出栈成功，该元素为 " << e << "。" << endl;
	return OK;
}

Status Top(Stack S, ElemType& e)//获取栈顶元素
{
	if (S.top == S.base)
	{
		//cout << "\a>> 错误：栈为空！" << endl;
		e = 0;
		return ERROR;
	}
	e = *(S.top - 1);
	return OK;
}

/*
Status Show(Stack S)//打印栈
{
	cout << "栈：top—";
	while (S.base != S.top)
		cout << *--S.top << "—";
	cout << "bottom" << endl << endl;
	return OK;
}
*/

Status isEmpty(Stack S)//判断是否为空栈
{
	if (S.base == S.top)
		return OK;
	else
		return ERROR;
}

Status Destroy(Stack& S)//销毁栈
{
	if (!S.base)
		return ERROR;
	delete[] S.base;
	S.base = NULL;
	S.top = NULL;
	S.stacksize = 0;//归零
	if (S.base)
		return ERROR;
	return OK;
}


/* 虚拟按键的实现部分 */
SendKeyFunc CapitalUp()//大写
{
	if (!(GetKeyState(VK_CAPITAL) & 0x1))
	{
		keybd_event(VK_CAPITAL, 0, 0, 0);
		keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
	}
	return;
}

SendKeyFunc CapitalDown()//小写
{
	if (GetKeyState(VK_CAPITAL) & 0x1)
	{
		keybd_event(VK_CAPITAL, 0, 0, 0);
		keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
	}
	return;
}

SendKeyFunc SendKey(const char a)//发送字母或数字
{
	Sleep(rand() % MaxRandTime);//随机延迟
	keybd_event(a, 0, 0, 0);
	keybd_event(a, 0, KEYEVENTF_KEYUP, 0);
	return;
}

SendKeyFunc SendSpecial(BYTE key)//发送特殊字符
{
	Sleep(rand() % MaxRandTime);//随机延迟
	keybd_event(key, 0, 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	return;
}

SendKeyFunc ShiftSendSpecial(BYTE key)//发送需要上档的特殊字符
{
	keybd_event(VK_SHIFT, 0, 0, 0);
	SendSpecial(key);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	return;
}

SendKeyFunc post(ElemType key)
{
	if ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))//大写字母和数字
	{
		CapitalUp();
		SendKey(key);
	}
	else if (key >= 'a' && key <= 'z')//小写字母
	{
		CapitalDown();
		SendKey(key - 32);
	}
	else if (key == ' ')
		SendSpecial(VK_SPACE);
	else if (key == ';')
		SendSpecial(VK_OEM_1);
	else if (key == ':')
		ShiftSendSpecial(VK_OEM_1);
	else if (key == '=')
		SendSpecial(VK_OEM_PLUS);
	else if (key == '+')
		ShiftSendSpecial(VK_OEM_PLUS);
	else if (key == ',')
		SendSpecial(VK_OEM_COMMA);
	else if (key == '-')
		SendSpecial(VK_OEM_MINUS);
	else if (key == '_')
		ShiftSendSpecial(VK_OEM_MINUS);
	else if (key == '.')
		SendSpecial(VK_OEM_PERIOD);
	else if (key == '?')
		SendSpecial(VK_OEM_2);
	else if (key == '[')
		SendSpecial(VK_OEM_4);
	else if (key == '{')
		ShiftSendSpecial(VK_OEM_4);
	else if (key == '\\')
		SendSpecial(VK_OEM_5);
	else if (key == '|')
		ShiftSendSpecial(VK_OEM_5);
	else if (key == ']')
		SendSpecial(VK_OEM_6);
	else if (key == '}')
		ShiftSendSpecial(VK_OEM_6);
	else if (key == '\'')
		SendSpecial(VK_OEM_7);
	else if (key == '\"')
		ShiftSendSpecial(VK_OEM_7);
	else if (key == '!')
		ShiftSendSpecial('1');
	else if (key == '@')
		ShiftSendSpecial('2');
	else if (key == '#')
		ShiftSendSpecial('3');
	else if (key == '$')
		ShiftSendSpecial('4');
	else if (key == '%')
		ShiftSendSpecial('5');
	else if (key == '^')
		ShiftSendSpecial('6');
	else if (key == '&')
		ShiftSendSpecial('7');
	else if (key == '*')
		ShiftSendSpecial('8');
	else if (key == '(')
		ShiftSendSpecial('9');
	else if (key == ')')
		ShiftSendSpecial('0');
	return;
}

SendKeyFunc SetKeyboard()//设置键盘
{
	if (DDLtime == EOF)
	{
		cout << endl << "获取数据完毕，请切换输入法为英文输入法，然后点击您需要输入的窗口。" << endl;
		cout << "就绪后，请在本窗口按下任意键，并于 " << DefaultTime << " 秒内切回目标窗口。" << endl;
	}
	else
		cout << endl << "获取数据完毕，请在 " << DDLtime << " 秒内切换输入法为英文输入法，然后点击您需要输入的窗口。" << endl;
	cout << "请勿触碰键盘，并保证输入过程中目标窗口不会失去焦点。" << endl;
	if (DDLtime == EOF)
	{
		system("pause>nul");
		cout << endl << "任意键被按下，请于 " << DefaultTime << " 秒内切回目标窗口。" << endl;
		Sleep(DefaultTime * 1000);
	}
	else
		Sleep(DDLtime * 1000);
	cout << "开始执行输入，请稍候。请务必保持目标窗口不会失去焦点，并且不要触碰键盘。" << endl;
	return;
}


/* 功能区 */
Function Function1()//直接发送
{
	if (Reverse && Init(A) != OK)
	{
		cout << "\a错误：初始化栈失败，请按任意键返回。" << endl;
		system("pause>nul");
		return;
	}
	char buffer[MAXSIZE] = { 0 };
	cout << "请输入一段文字（不自动发送回车）：" << endl;
	rewind(stdin);
	fgets(buffer, MAXSIZE, stdin);
	rewind(stdin);
	if (Reverse)
	{
		for (int i = 0; buffer[i] != '\n'; ++i)
			Push(A, buffer[i]);
		SetKeyboard();
		ElemType e;
		while (!isEmpty(A))
		{
			Pop(A, e);
			post(e);
		}
	}
	else
	{
		SetKeyboard();
		for (int i = 0; buffer[i] != '\n'; ++i)
			post(buffer[i]);
	}
	MessageBox(NULL, TEXT("自动输入完毕，点击“确定”返回。"), TEXT("强制复制输入"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	return;
}

Function Function2()//文件读入发送
{
	FILE* fp;
	char path[MAX_PATH] = { 0 }, buffer[MAXSIZE] = { 0 };
	cout << "请输入文件路径，或在非管理员模式下将文件拖拽至此：" << endl;
	rewind(stdin);
	fgets(path, sizeof(path), stdin);
	rewind(stdin);
	if (strlen(path) < 4)
	{
		cout << endl << "\a错误：文件路径有误，请按任意键退出。" << endl;
		system("pause>nul");
		return;
	}
	path[strlen(path) - 1] = 0;//去除回车
	if (path[strlen(path) - 1] == '\"')
		path[strlen(path) - 1] = 0;
	if (path[0] == '\"')
	{
		for (unsigned int i = 0; i < strlen(path) - 1; ++i)
			path[i] = path[i + 1];
		path[strlen(path) - 1] = 0;
	}
	fopen_s(&fp, path, "r");
	if (fp == NULL)
	{
		cout << endl << "\a错误：打开文件失败，请按任意键返回。" << endl;
		system("pause>nul");
		return;
	}
	SetKeyboard();
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		if (Reverse)
		{
			if (Init(A) != OK)
			{
				cout << "\a错误：初始化栈失败，请按任意键返回。" << endl;
				system("pause>nul");
				return;
			}
			for (unsigned int i = 0; i < strlen(buffer); ++i)
				Push(A, buffer[i]);
			ElemType e;
			while (!isEmpty(A))
			{
				Pop(A, e);
				post(e);
			}
		}
		else
			for (unsigned int i = 0; i < strlen(buffer); ++i)
				post(buffer[i]);
		keybd_event(VK_RETURN, 0, 0, 0);//换行
		keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);//记得抬起
	}
	fclose(fp);
	MessageBox(NULL, TEXT("自动输入完毕，点击“确定”返回。"), TEXT("强制复制输入"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	return;
}


/* main 函数 */
int main()
{
	system("chcp 936&title 强制粘贴（仅支持英语字符）&color e");
	short int choice = 2;
	for (;;)
	{
		system("cls");
		cout << "    我们通常喜欢在 WPS 或 word 中写好英语作文再复制，但有些不太友好的英语作文网站或程序拒绝复制粘贴，同时也拒绝了“Shift + 方向键”的选定，这给作文编辑带来了诸多不便。为此，我们开发此程序以供强制粘贴输入。" << endl << endl;
		cout << "\t1 = 直接输入并转录" << endl;
		cout << "\t2 = 从文件输入并转录" << endl;
		cout << (Reverse ? "\t3 = 停用逆序（当前已启用）" : "\t3 = 启用逆序（当前未启用）") << endl;
		cout << "\t4 = 修改倒计时" << endl;
		cout << "\t0 = 退出程序" << endl;
		cout << endl << endl << "请选择一项以继续：";
		rewind(stdin);
		while (scanf_s("%hd", &choice) != 1 || choice < 0 || choice > 4)
		{
			rewind(stdin);
			cout << "\a错误：输入有误，请重新输入：";
		}
		rewind(stdin);
		system("cls");
		switch (choice)
		{
		case 0:
			return EXIT_SUCCESS;
		case 1:
			Function1();
			break;
		case 2:
			Function2();
			break;
		case 3:
			Reverse = !Reverse;
			break;
		case 4:
			if (DDLtime == EOF)
				cout << "当前启用了暂停模式。请指定一个不高于 " << MaxTime << " 秒的新值：";
			else
				cout << "当前倒计时值：" << DDLtime << " 秒，请指定一个不高于 10 秒的新值：";
			rewind(stdin);
			if (scanf_s("%d", &DDLtime) != 1)
				DDLtime = DefaultTime;
			if (DDLtime > MaxTime || DDLtime <= NULL)
				DDLtime = EOF;
			break;
		default:
			continue;
		}
	}
	system("cls");
	return EXIT_FAILURE;
}