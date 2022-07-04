#include <stdio.h>
#include <Windows.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAX 5203344
extern HHOOK hHook;
extern LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam);
typedef int qelemType;
HHOOK hHook;

typedef struct queue
{
	qelemType data;
	struct queue* next;
}queue, * linkqueue;

typedef struct
{
	linkqueue rear;
	int length;
}sqqueue;

void initQueue(sqqueue& queue)//初始化队列
{
	queue.rear = (linkqueue)malloc(sizeof(queue));
	if (queue.rear)
		queue.rear->next = queue.rear;
	queue.length = 0;
}

int emptyQueue(sqqueue& queue)//判队列是否为空
{
	if (queue.length == 0)
		return OK;
	else
		return ERROR;
}

void printQueue(sqqueue& queue)//打印队列
{
	printf("front->");
	if (emptyQueue(queue))
		printf("rear\n\n"); 
	else
	{
		linkqueue q = queue.rear->next->next;
		while (q != queue.rear)
		{
			printf(" %d ->", q->data);
			q = q->next;
		}
		printf(" %d ->rear\n\n", q->data);
	}
}

int enqueue(sqqueue& queue, qelemType e)//元素入队
{
	linkqueue p;
	p = (linkqueue)malloc(sizeof(queue));
	if (!p)
		return OVERFLOW;
	p->data = e;
	p->next = queue.rear->next;
	queue.rear->next = p;
	queue.rear = p;
	queue.length++;
	return OK;
}

int delqueue(sqqueue& queue, qelemType& e)//元素出队
{
	linkqueue p;
	if (emptyQueue(queue))
		return ERROR;//若队列为空返回ERROR
	p = queue.rear->next->next;//链表队列队尾指针下一结点(也即头结点)的下一结点(即队头指针)
	e = p->data;
	queue.rear->next->next = p->next;
	free(p);
	queue.length--;
	if (queue.length == 0)
		initQueue(queue);
	return OK;
}

LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("入队"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("出队"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("退出程序"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

int main()
{
	sqqueue queue2;
	qelemType num;
	initQueue(queue2);
	int n = 0, errorcontrol = 6;
	bool flag = true;
	system("chcp 936&title 队列演示程序状态输出&color e&cls");
	while (flag && n < MAX)
	{
		printQueue(queue2);
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
		if (hHook)
			errorcontrol = MessageBox(NULL, TEXT("请选择一项以继续："), TEXT("队列演示程序控制台"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
		else
			errorcontrol = MessageBox(NULL, TEXT("入队吗？"), TEXT("队列演示程序控制台"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST);
		switch (errorcontrol)
		{
		case 6:
			if (enqueue(queue2, n) == 1)
				printf("元素 %d 已成功入队！\n", n);
			else
				printf("元素 %d 入队失败！\n", n);
			n += 1;
			break;
		case 7:
			if (delqueue(queue2, num))
				printf("元素 %d 已成功出队！\n", num);
			else
				printf("队列为空，无需出队。\n");
			break;
		case 2:
			flag = false;
			break;
		default:
			continue;
		}
	}
	MessageBox(NULL, TEXT("演示完毕，请点击“确定”退出本程序。"), TEXT("队列演示程序"), MB_OK | MB_TOPMOST);
	system("cls");
	return 0;
}