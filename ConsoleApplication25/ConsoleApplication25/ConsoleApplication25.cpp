#include <iostream>
#include <Windows.h>
#include <string.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
using namespace std;
typedef int ElemType;
typedef int Status;
extern HHOOK hHook;
extern LRESULT __stdcall CBTHookProc1(long nCode, WPARAM wParam, LPARAM lParam);
extern LRESULT __stdcall CBTHookProc2(long nCode, WPARAM wParam, LPARAM lParam);
extern LRESULT __stdcall CBTHookProc3(long nCode, WPARAM wParam, LPARAM lParam);
HHOOK hHook;

typedef struct//顺序栈的数据类型
{
	ElemType* base;
	ElemType* top;
	int stacksize;
}Stack;

Status Init(Stack& S)//初始化顺序栈
{
	S.base = new ElemType[MAXSIZE];
	if (!S.base)
		return ERROR;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

Status Push(Stack& S, ElemType x)//入栈
{
	if (S.top - S.base == S.stacksize) 
	{
		cout << "\a>> 错误：栈空间已满，压入元素 " << x << " 失败！" << endl;
		return ERROR;
	}
	*S.top++ = x;
	cout << ">> 压入元素 " << x << " 成功。" << endl;
	return OK;
}

Status Pop(Stack& S, ElemType& e)//出栈
{
	if (S.top == S.base)
	{
		cout << "\a>> 错误：栈为空！" << endl;
		return ERROR;
	}
	e = *--S.top;
	cout << ">> 元素出栈成功，该元素为 " << e << "。" << endl;
	return OK;
}

Status Show(Stack S)//打印栈
{
	cout << "栈：top—";
	while (S.base != S.top)
		cout << *--S.top << "—";
	cout << "bottom" << endl << endl;
	return OK;
}

/* 以上是栈的操作，以下是队列的操作。 */

struct node
{
	int data;
	node* next;
}; 

class linkqueue//队列结构体
{
private:
	node* front, * rear;
public:
	linkqueue();//初始化队列
	~linkqueue();//销毁原队列并初始化新队列
	Status enqueue(int x);//元素入队
	Status dequeue();//元素出队
	Status showqueue();//打印队列
};

linkqueue::linkqueue()
{
	node *s;
	s = new node;
	s->next = NULL;
	front = rear = s;
}    

linkqueue::~linkqueue() 
{
	front = rear = NULL; 
	node* s;
	s = new node;
	s->next = NULL;
	front = rear = s;
}

Status linkqueue::enqueue(int x) 
{
	node* s = new node; 
	if (s == NULL)
	{
		cout << "\a>> 错误：队列已满，元素 " << x << " 入队失败！" << endl;
		return ERROR;
	}
	s->data = x;
	s->next = NULL;
	rear->next = s;
	rear = s;//将结点s插入到队尾
	cout << ">> 元素 " << x << " 入队成功。" << endl;
	return OK;
}

Status linkqueue::dequeue()
{
	int x;
	node* p = new node;
	p = front->next;
	if (p == NULL)
	{
		cout << "\a>> 错误：队列为空，无法出队！" << endl;
		return ERROR;
	}
	x = p->data;
	front->next = p->next;
	cout << ">> 元素 " << x << " 出队成功。" << endl;
	return OK;
}

Status linkqueue::showqueue() 
{
	if (front == rear)
	{
		cout << "队列：front—rear" << endl << endl;
		return ERROR;
	}
	node* q = new node;
	q = front;
	cout << "队列：front—";
	while (q ->next)
	{
		q = q->next;
		cout << q->data << "—";
	}
	cout << "rear" << endl << endl;
	return OK;
}

/*以上是队列部分，以下是 UI 界面的处理函数。*/

LRESULT __stdcall CBTHookProc1(long nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("演示栈"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("演示队列"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("退出程序"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc2(long nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("入栈"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("出栈"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("结束演示"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc3(long nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("入队"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("出队"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("结束演示"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

Status InputBox(char *_0)//文本输入框
{
	int i, j;
	char cmd[5 * MAXSIZE] = { 0 }, runvbs[10 * MAXSIZE] = "(if exist \"";
	for (i = strlen(_0) - 1; i >= 0; i--)
		if (_0[i] == '\\')
			break;
	for (j = 0; j <= i; j++)
		cmd[j] = _0[j];
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "InputBox.txt\" (del /a /f /q \\\\?\\\"");
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "InputBox.txt\"))&start /realtime /wait \"\" \"");
	strcat_s(cmd, "InputBox.vbs");
	strcat_s(runvbs, cmd);
	strcat_s(runvbs, "\"");
	FILE* fp;
	fopen_s(&fp, cmd, "r");
	if (!fp)
	{
		fopen_s(&fp, cmd, "w+");
		if (fp)
		{
			fwrite("x = 0\nOn Error Resume Next\nx = int(inputbox(\"请输入一个整型元素：\",\"InputBox\",\"0\"))\nif err.number <> 0 Then\nx = 0\nEnd if\nSet fso = CreateObject(\"Scripting.FileSystemObject\")\nSet f = fso.CreateTextFile(\"", 202, 1, fp);
			fwrite(cmd, strlen(cmd) - 3, 1, fp);
			fwrite("txt\",True)\nf.write x\nf.close", 29, 1, fp);
			fclose(fp);
		}
		else
		{
			MessageBox(NULL, TEXT("生成脚本文件失败，请确保程序所在目录可写。"), TEXT("InputBox"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			return ERROR;
		}
	}
	system(runvbs);
	cmd[strlen(cmd) - 3] = 't';
	cmd[strlen(cmd) - 2] = 'x';
	cmd[strlen(cmd) - 1] = 't';
	fopen_s(&fp, cmd, "r");
	if (fp)
	{
		rewind(stdin);
		if (fscanf_s(fp, "%d", &i) != 1)
		{
			MessageBox(NULL, TEXT("从脚本读取的数据类型不正确，请检查您的输入。"), TEXT("InputBox"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			rewind(stdin);
			fclose(fp);
			return ERROR;
		}
		rewind(stdin);
		fclose(fp);
		return i;
	}
	else
	{
		MessageBox(NULL, TEXT("从脚本读取数据失败，请确保程序所在目录可读。"), TEXT("InputBox"), MB_OK | MB_ICONERROR | MB_TOPMOST);
		return ERROR;
	}
}

/*以上是 UI 界面的处理函数，以下是主函数。*/

int main(int argc, char* argv[])
{
	system("chcp 936&title 栈和队列演示程序暨C/C++调用vbs实现InputBox演示程序&color e");
	int errorcontrol, choice;
	bool flag;
	LPWSTR str = { 0 };
	Stack A;
	ElemType e;
	linkqueue q;
	for (;;)
	{
		system("cls");
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc1, NULL, GetCurrentThreadId());
		if (hHook)
			errorcontrol = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("栈和队列演示程序"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
		else
		{
			MessageBox(NULL, TEXT("弹出菜单失败，请确保您的内存空间足够。"), TEXT("栈和队列演示程序"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			return -1;
		}
		switch (errorcontrol)
		{
		case 6:
			if (Init(A) == ERROR)//初始化栈
			{
				MessageBox(NULL, TEXT("初始化栈失败！"), TEXT("栈和队列演示程序"), MB_OK | MB_ICONERROR | MB_TOPMOST);
				continue;
			}
			cout << "初始化栈成功，开始程序演示。" << endl;
			Show(A);
			/*元素8，9，5，4依次入栈并实现元素8，9的出栈*/
			cout << "元素8，9，5，4依次入栈并实现元素8，9的出栈：" << endl;
			Push(A, 8);
			Pop(A, e);
			Push(A, 9);
			Pop(A, e);
			Push(A, 5);
			Push(A, 4);
			Show(A);
			flag = true;
			while (flag)
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc2, NULL, GetCurrentThreadId());
				if (hHook)
					choice = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("栈演示程序"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
				else
				{
					choice = MessageBox(NULL, TEXT("弹出子菜单失败，请确保您的内存空间足够。"), TEXT("栈演示程序"), MB_OK | MB_ICONERROR | MB_TOPMOST);
					break;
				}
				switch (choice)
				{
				case 6:
					Push(A, InputBox(argv[0]));
					break;
				case 7:
					Pop(A, e);
					break;
				case 2:
					flag = false;
					continue;
				}
				Show(A);
			}
			break;
		case 7:
			q.~linkqueue();
			cout << "队列初始化成功，开始演示。" << endl;
			q.showqueue();
			cout << "元素4，5，7，6，8依次入队：" << endl;
			q.enqueue(4);
			q.enqueue(5);
			q.enqueue(7);
			q.enqueue(6);
			q.enqueue(8);
			q.showqueue();
			cout << "元素4，5出队：" << endl;
			q.dequeue();
			q.dequeue();
			q.showqueue();
			flag = true;
			while (flag)
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc3, NULL, GetCurrentThreadId());
				if (hHook)
					choice = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("队列演示程序"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
				else
				{
					choice = MessageBox(NULL, TEXT("弹出子菜单失败，请确保您的内存空间足够。"), TEXT("队列演示程序"), MB_OK | MB_ICONERROR | MB_TOPMOST);
					break;
				}
				switch (choice)
				{
				case 6:
					q.enqueue(InputBox(argv[0]));
					break;
				case 7:
					q.dequeue();
					break;
				case 2:
					flag = false;
					continue;
				}
				q.showqueue();
			}
			break;
		case 2:
			system("cls");
			return 0;
		}
		system("cls");
	}
	return -2;
}