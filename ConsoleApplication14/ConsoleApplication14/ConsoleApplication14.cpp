#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int qelemType;

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

void initQueue(sqqueue& queue)//置空队列
{
	queue.rear = (linkqueue)malloc(sizeof(queue));
	if (queue.rear)
		queue.rear->next = queue.rear;
}

int emptyQueue(sqqueue& queue)//判队列是否为空
{
	if (queue.rear->next == queue.rear)
		return OK;
	else
		return 0;
}

int enqueue(sqqueue& queue, qelemType e)//元素入列
{
	linkqueue p;
	p = (linkqueue)malloc(sizeof(queue));
	if (!p)
		return OVERFLOW;
	p->data = e;
	p->next = queue.rear->next;
	queue.rear->next = p;
	queue.rear = p;
	return OK;
}

int delqueue(sqqueue& queue, qelemType& e)//元素出列
{
	linkqueue p;
	if (queue.rear->next == queue.rear)
		return ERROR;//若队列为空返回ERROR
	p = queue.rear->next->next;//循环链表队列队尾指针下一结点(也即头结点)的下一结点(即队头指针)
	e = p->data;
	queue.rear->next->next = p->next;
	free(p);//delete(p);//free函数与delete函数均可使用
	return OK;
}

int main()
{
	sqqueue queue2;
	qelemType num;
	int n;
	system("chcp 936&title 出列入列测试&color e&cls");
	while (true)
	{
		system("cls");
		rewind(stdin);
		printf("请输入元素队列个数：");
		if (scanf_s("%d", &n) == 1)
		{
			rewind(stdin);
			if (n < 0)
			{
				printf("\a错误：元素个数不能为负数，请按任意键重新输入。\n");
				system("pause>nul");
				continue;
			}
			else
				break;
		}
		else
		{
			printf("\a错误：非法输入，请按任意键重新输入。\n");
			system("pause>nul");
			continue;
		}
	}
	system("cls");
	rewind(stdin);
	initQueue(queue2);
	if (emptyQueue(queue2))
		printf("当前队列为空！\n\n\n");
	else
		printf("当前队列不为空！\n\n\n");
	for (int i = 1; i <= n; i++)
		if (enqueue(queue2, i)==1)
			printf("元素 %d 已成功入列！\n", i);
		else
			printf("元素 %d 入列失败！\n", i);
	printf("\n\n");
	for (int j = 1; j <= n - 1; j++)
		if (delqueue(queue2, num))
			printf("元素 %d 已成功出列！\n", num);
		else
			printf("元素 %d 出列失败！\n", num);
	if (emptyQueue(queue2))
		printf("\n\n\n当前队列为空！\n");
	else
		printf("\n\n\n当前队列不为空！\n");
	printf("\n\n");
	return 0;
}