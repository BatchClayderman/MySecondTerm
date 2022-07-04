#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <thread>
#include <time.h>
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef OK
#define OK 1
#endif
#ifndef ERROR
#define ERROR 0
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifdef TopFloor
#undef TopFloor
#endif
#define TopFloor 4
#ifdef MAXSIZE
#undef MAXSIZE
#endif
#define MAXSIZE 255//路径最大长度
#ifdef t
#undef t
#endif
#define t 1//以 0.1 秒为单位
#ifdef Tran
#undef Tran
#endif
#define Tran 100//兑换
#ifdef Move
#undef Move
#endif
#define Move 40 * t * Tran//移动耗时
#ifdef Doors
#undef Doors
#endif
#define Doors 20 * t * Tran//开关门耗时
#ifdef Walk
#undef Walk
#endif
#define Walk 25 * t * Tran//每人出入电梯耗时
#ifdef Still
#undef Still
#endif
#define Still 3 * t * Tran//静止归位时间
using namespace std;
typedef short int Status;
typedef void ThreadControl;
typedef void LiftControl;
bool isNeeded[5] = { false };
int MilliTime = 0;
int MaxTime = 31622400;//最大运行时间
char _0[MAXSIZE] = { 0 };
Status RunThread = 1;//0 = 停运  1 = 上行  2 = 下行  3 = 开始销毁  4 = 完成销毁
Status Outing = 0;//0 = 未输出  1 = 正在输出
Status Floor = 0;//所处楼层
string Floors[5] = { "地下层",	"第一层",	"第二层",	"第三层",	"第四层" };//楼层信息
string MaxLoad = "15";//最大人数
string MaxKilo = "1500";//最大负重
ThreadControl MessagesOut(string str);
HHOOK hHook;


/* Windows Hook */
LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam)//总控制
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("工程师"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("教师学生"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("退出系统"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc1(long nCode, WPARAM wParam, LPARAM lParam)//工程师
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("启用电梯"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("停用电梯"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("销毁电梯"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc2(long nCode, WPARAM wParam, LPARAM lParam)//教师学生
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("选择楼层"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("取消选择"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("重选角色"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc3(long nCode, WPARAM wParam, LPARAM lParam)//电梯
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDOK, TEXT("关门"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}


/* 文本读入工具 */
Status InputBox()//文本输入框
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
			fwrite("x = -1\nOn Error Resume Next\nx = int(inputbox(\"请输入去往的楼层数：\",\"InputBox\",\"0\"))\nif err.number <> 0 Then\nx = -1\nEnd if\nif x = vbEmpty Then\nx = -1\nEnd if\nSet fso = CreateObject(\"Scripting.FileSystemObject\")\nSet f = fso.CreateTextFile(\"", 238, 1, fp);
			fwrite(cmd, strlen(cmd) - 3, 1, fp);
			fwrite("txt\",True)\nf.write x\nf.close", 29, 1, fp);
			fclose(fp);
		}
		else
		{
			MessagesOut("错误：生成脚本文件失败，请确保程序所在目录可写。");
			return EOF;
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
			MessagesOut("错误：从脚本读取的数据类型不正确，请检查您的输入。");
			rewind(stdin);
			fclose(fp);
			return EOF;
		}
		rewind(stdin);
		fclose(fp);
		return i;
	}
	else
	{
		MessagesOut("错误：从脚本读取数据失败，请确保程序所在目录可读。");
		return EOF;
	}
}

void GetFloor(bool isSelected)//获取楼层
{
	int select = InputBox();
	if (select < ERROR || select > TopFloor)
		MessagesOut("提示：没有选中楼层。");
	else if (select == Floor)
		MessagesOut("提示：当前电梯位于目标楼层，无法操作。");
	else
	{
		if (isNeeded[select] == isSelected)
		{
			if (isSelected)
			{
				string str = "提示：" + Floors[select] + "已被选中，无需重复选择。";
				MessagesOut(str);
			}
			else
			{
				string str = "提示：" + Floors[select] + "没有被选中，无需取消选择。";
				MessagesOut(str);
			}
			return;
		}
		isNeeded[select] = isSelected;
		if (isSelected)
		{
			string str = "信息：已成功选中" + Floors[select] + "。";
			MessagesOut(str);
		}
		else
		{
			string str = "信息：已取消选择" + Floors[select] + "。";
			MessagesOut(str);
		}
	}
	return;
}


/* 电梯控制 */
bool isinRange(short int i)//是否位于界内
{
	return (i <= TopFloor && i >= 0);
}

Status NextArrival()//下一站
{
	switch (RunThread)
	{
	case 1:
		for (int i = Floor; isinRange(i); ++i)
			if (isNeeded[i])
				return i;
		for (int i = Floor; isinRange(i); --i)
			if (isNeeded[i])
			{
				RunThread = 2;
				break;
			}
		return EOF;
	case 2:
		for (int i = Floor; isinRange(i); --i)
			if (isNeeded[i])
				return i;
		for (int i = Floor; isinRange(i); ++i)
			if (isNeeded[i])
			{
				RunThread = 1;
				break;
			}
		return EOF;
	default:
		return EOF;
	}
	return EOF;
}


LiftControl MoveLift(short int count, bool force)//移动电梯
{
	if (count < 0 || count > TopFloor || count == Floor)
		return;
	if ((RunThread == 3 || RunThread == 4) && !force)
		return;
	Sleep(Move);
	if ((RunThread == 3 || RunThread == 4) && !force)
		return;
	Floor = count;
	string str = "信息：电梯抵达" + Floors[Floor] + "。";
	MessagesOut(str);
	if (Floor == TopFloor)
		RunThread = 2;
	else if (Floor == 0)
		RunThread = 1;
	return;
}

LiftControl MoveTo(short int count, bool force)//抵达目标楼层
{
	if (count < 0 || count > TopFloor || count == Floor)
		return;
	if ((RunThread == 3 || RunThread == 4) && !force)
		return;
	for (; count != Floor;)
	{
		if (Floor < count)
			MoveLift(Floor + 1, force);
		else
			MoveLift(Floor - 1, force);
	}
	isNeeded[count] = false;
	MessagesOut("信息：抵达目标楼层，电梯开门。");
	Sleep(Doors);
	if (force)
	{
		MessagesOut("信息：电梯上抵达本垒层，如有人员在电梯内，所有人员将离开电梯。");
		Sleep(Move);
	}
	else
	{
		MessagesOut("信息：门已打开，等待教师学生出入。");
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc3, NULL, GetCurrentThreadId());
		if (!hHook)
			MessagesOut("警告：电梯钩子遭到破坏！");
		MessageBox(NULL, TEXT("教师学生出入，完成后请点击“关门”。"), TEXT("电梯系统控制台"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
	}
	MessagesOut("信息：师生出入完毕，电梯关门。");
	Sleep(Doors);
	MessagesOut("信息：门已关上。");
	return;
}

LiftControl EmptyLift()//清空电梯并使之停于本垒层
{
	MoveTo(0, true);
	for (int i = 0; i <= TopFloor; ++i)
		isNeeded[i] = false;
	if (RunThread == 3)
		RunThread = 4;
	return;
}


/* 并发编程 */
ThreadControl MessagesOut(string str)//信息输出
{
	while (Outing == 1);//避免线程输出冲突导致信息混乱
	Outing = 1;
	cout << setw(10) << int(MilliTime / 10) << '.' << setw(1) << int(MilliTime % 10) << '\t' << str << endl;
	Outing = 0;
	return;
}

ThreadControl Thread1()//时间线程
{
	for (; MilliTime < MaxTime && RunThread != 4; MilliTime += t)//这样运行快些
		Sleep(t * 100);
	if (RunThread == 4)
		return;
	MessagesOut("错误：电梯运行时间太长，已自动发起销毁。");
	RunThread = 3;
	return;
}

ThreadControl Thread2()//用户线程
{
	for (; RunThread != 3 && RunThread != 4;)//快速循环
	{
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
		if (!hHook)
			MessagesOut("警告：电梯钩子遭到破坏！");
		int choice = MessageBox(NULL, TEXT("请选择您的身份："), TEXT("电梯系统控制台"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
		if (RunThread == 3)
			break;
		switch (choice)
		{
		case IDYES://工程师
			hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc1, NULL, GetCurrentThreadId());
			if (!hHook)
				MessagesOut("警告：电梯钩子遭到破坏！");
			choice = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("工程师"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
			switch (choice)
			{
			case IDYES://启用电梯
				if (RunThread == 0)
					RunThread = 1;
				MessagesOut("信息：电梯已被启用，当前电梯位于本垒层。");
				break;
			case IDNO://停用电梯
				RunThread = 0;
				MessagesOut("信息：电梯停用指令发起，正在停用电梯。");
				EmptyLift();
				MessagesOut("信息：电梯已被停用。");
				break;
			case IDCANCEL:
				RunThread = 3;
				EmptyLift();
				RunThread = 4;
				break;
			default:
				break;
			}
			break;
		case IDNO://教师学生
			if (RunThread == 0 || RunThread == 3)
				break;
			do
			{
				hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc2, NULL, GetCurrentThreadId());
				if (!hHook)
					MessagesOut("警告：电梯钩子遭到破坏！");
				choice = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("教师学生"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
				switch (RunThread)
				{
				case 0:
					MessagesOut("提示：很抱歉，电梯已停用，请联系工程师！");
					break;
				case 1:
					if (true)//只是为了可以声明变量
					{
						string str = "信息：电梯位于";
						str += Floors[Floor] + "，电梯上行（Going Up）。";
						MessagesOut(str);
					}
					break;
				case 2:
					if (true)//只是为了可以声明变量
					{
						string str = "信息：电梯位于";
						str += Floors[Floor] + "，电梯下行（Going Down）。";
						MessagesOut(str);
					}
					break;
				default:
					break;
				}
				switch (choice)
				{
				case IDYES:
					GetFloor(true);
					break;
				case IDNO:
					GetFloor(false);
					break;
				default:
					break;
				}
			} while (choice != IDCANCEL);
			break;
		case IDCANCEL://退出系统
			RunThread = 3;
			return;
		default:
			break;
		}
	}
	return;
}

ThreadControl Thread3()//电梯线程
{
	int LastStayTime = EOF;
	for (; RunThread != 3 && RunThread != 4;)
	{
		Status next = NextArrival();
		if (next == EOF)
		{
			if (LastStayTime == EOF)
				LastStayTime = MilliTime;
			else if (Floor != 0 && MilliTime - LastStayTime >= Still)
			{
				MessagesOut("信息：电梯空载时间较长，返回本垒层。");
				MoveTo(0, true);
				LastStayTime = MilliTime;
			}
			continue;
		}
		else
		{
			LastStayTime = EOF;
			switch (RunThread)
			{
			case 0://电梯暂停
				break;
			case 1://电梯上行
				MoveTo(next, false);
				break;
			case 2://电梯下行
				MoveTo(next, false);
				break;
			default:
				return;
			}
		}
	}
	return;
}


/* main 函数 */
int main(int argc, char* argv[])
{
	system("chcp 936&title 电梯系统输出流&color e&cls");
	strcpy_s(_0, argv[0]);
	thread t1(Thread1);
	thread t2(Thread2);
	thread t3(Thread3);
	cout << "   时间戳\t事件" << endl;
	cout << "============\t========================================" << endl << endl;
	MessagesOut("信息：电梯安装完成，开始运行。");
	string str = "信息：本电梯最多载人 " + MaxLoad + " 人，最大负重 " + MaxKilo + " KG。";
	MessagesOut(str);
	for (; RunThread != 3 && RunThread != 4;);//主线程死循环
	MessagesOut("信息：销毁指令发出，正在销毁电梯。");
	if (RunThread == 3)
	{
		MoveTo(0, true);
		RunThread = 4;
	}
	t1.join();
	t1.~thread();
	t2.join();
	t2.~thread();
	t3.join();
	t3.~thread();
	MessagesOut("信息：电梯已被销毁，请按任意键退出。");
	system("pause>nul&cls");
	return EXIT_SUCCESS;
}