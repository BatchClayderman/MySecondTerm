#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define STACK_INIT_SIZE 100
#define STACK_GROW_SIZE 50
#define ELEMTYPE char
#define OK 1
#define ERROR 0

typedef struct//建立一个栈的首结点
{
	ELEMTYPE* base;
	ELEMTYPE* top;
	int stacksize;
} SpStack;

int InitStack(SpStack* s)//建立空的栈并返回首地址
{
	s->base = ((ELEMTYPE*)malloc(STACK_INIT_SIZE * sizeof(ELEMTYPE)));
	if (!s->base)
		return ERROR;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

int StackEmpty(SpStack* s)//判断栈是否为空
{
	if (s->top == s->base)
		return OK;
	else
		return ERROR;
}

int Push(SpStack* s, SpStack* new_s, ELEMTYPE e)//往栈顶插入元素即进栈
{
	if (s->top - s->base >= s->stacksize)//判断是否栈满
	{
		new_s->base = ((ELEMTYPE*)realloc(s->base, (s->stacksize + STACK_GROW_SIZE) * sizeof(ELEMTYPE)));
		if (!new_s->base)
			return ERROR;
		s = new_s;
		s->stacksize += STACK_GROW_SIZE;
		s->top = s->base + s->stacksize;
	}
	*s->top++ = e;
	return OK;
}

int Pop(SpStack* s, ELEMTYPE* e)//让栈顶元素依次输出即出栈
{
	if (StackEmpty(s))
		return ERROR;
	*e = *(--s->top);
	return OK;
}

int Comp(ELEMTYPE a, ELEMTYPE b)//执行比对
{
	if ((a == '(' && b != ')')|| (a == '[' && b != ']')|| (a == '{' && b != '}'))
		return ERROR;
	else
		return OK;
}

int Count(SpStack* s, SpStack* new_s, ELEMTYPE e[STACK_INIT_SIZE * 2])//执行判断
{
	ELEMTYPE e1;
	int i;
	InitStack(s);
	if ('\n' == e[strlen(e) - 1])
		e[strlen(e) - 1] = 0;
	printf("%s\n", e);
	for (i = 0; e[i] != '\0'; i++)
	{
		switch (e[i])
		{
		case '(':
		case '[':
		case '{':
			Push(s, new_s, e[i]);
			break;
		case ')':
		case ']':
		case '}':
			if (StackEmpty(s))
			{
				printf("%*s↖右括号多余\n", i + 1, "");
				return ERROR;
			}
			else
				Pop(s, &e1);
			if (!Comp(e1, e[i]))
			{
				printf("%*s↖左右匹配出错\n", i + 1, "");
				return ERROR;
			}
		}
	}
	if (!StackEmpty(s))
	{
		printf("%*s↖缺少右括号\n", i, "");
		return ERROR;
	}
	else
	{
		printf("匹配正确，未发现问题。\n");
		return OK;
	}
}

int main(int argc, char* argv[])//支持命令行启动
{
	char Ens = 'E';
	ELEMTYPE e[STACK_INIT_SIZE * 2];
	SpStack s, new_s;
	if (argc != 1)
	{
		int i = 1;
		printf("\n");
		for (int i = 1; i < argc; i++)
		{
			Count(&s, &new_s, argv[i]);
			printf("\n\n");
		}
		return i;
	}
	system("chcp 936&title 判断括号是否匹配&color e");
	while (true)
	{
		system("cls");
		printf("请输入表达式（最多支持 %d 个字符）：\n", STACK_INIT_SIZE * 2 - 1);
		rewind(stdin);
		fgets(e, STACK_INIT_SIZE * 2, stdin);
		rewind(stdin);
		system("cls");
		Count(&s, &new_s, e);
		free(s.base);
		rewind(stdin);
		printf("\n\n输入“E”或“e”回车退出程序，输入其它回车继续运行。\n");
		scanf_s("%c", &Ens, sizeof(Ens));
		if (Ens == 'E' || Ens == 'e')
		{
			system("cls");
			return 0;
		}
		rewind(stdin);
	}
	return -1;
}