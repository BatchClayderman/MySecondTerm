#include <stdio.h>
#include <stdlib.h>
#define maxsize 10
#define OK 1
#define ERROR 0

typedef struct
{
	int data[maxsize];
	int last;
}Sequenlist;

Sequenlist* create() //按要求创建一个具有4个元素{2，3，4，5}的顺序表
{
	Sequenlist* L;
	L = (Sequenlist*)malloc(sizeof(Sequenlist));
	if(!L)
		return ERROR;
	L->last = 0;
	for (int i = 1; L->last < maxsize && i <= 4; i++)
	{
		L->data[i] = i + 1;
		L->last++;
	}
	return L;
}

int Length(Sequenlist* L) //求取顺序表的长度
{
	return (L->last);
}

int GetData(Sequenlist* L, int i) //获取第 i 个元素
{
	if (i >= 1 && i <= L->last)
		return (L->data[i]);
	else
		return ERROR;
}

int Find(Sequenlist* L, int x) // 查找元素 x
{
	int i = 1;
	while (i <= L->last && L->data[i] != x)
		i++;
	if (i <= L->last)
		return i;
	else
		return ERROR;
}

int Insert(Sequenlist* L, int x, int i) //在顺序表的某一位置插入数据
{
	int j;
	if (i < 1 || i > L->last + 1 || L->last == maxsize)//在表中第 i 个位置插入新元素 x 
		return ERROR; //插入不成功 
	else
	{
		for (j = L->last; j >= i; j--)
			L->data[j + 1] = L->data[j];
		L->data[i] = x; L->last++;
		return OK; //插入成功 
	}
}

int Delete(Sequenlist* L, int i) //删除顺序表中 i 位置的数据
{
	int j;
	if (i <1 || i >L->last)
		return ERROR;
	for (j = i + 1; j <= L->last; j++)
		L->data[j - 1] = L->data[j];
	L->last--;
	return OK;
}

void print(Sequenlist* L) //打印顺序表
{
	printf("顺序表打印如下：\n");
	for (int i = 1; i <= L->last; i++)
		if (i % 5 == 0)
			printf("%d\n", L->data[i]);
		else
			printf("%d\t", L->data[i]);
	if (L->last % 5 != 0)
		printf("\n");
	printf("\n顺序表打印完毕。\n");
}

int Destroy(Sequenlist* L)//销毁顺序表
{
	if (L)
	{
		free(L);
		L = NULL;
		return OK;
	}
	else
		return ERROR;
}

/*以上是顺序表实现函数，以下是链式表实现函数*/

typedef struct LNode
{
	int data; //链表数据
	struct LNode* next; //链表指针
}LNode, * LinkList;

LinkList HeadCreate(LinkList la)//按要求建立单链表（头插法）
{
	la = (LinkList)malloc(sizeof(LNode)); //建立头结点
	if (la)
		la->next = NULL;
	else
		return ERROR;
	for (int num = 0; num < 4; num++)
	{
		LNode* p = (LinkList)malloc(sizeof(LNode));
		if (p)
		{
			p->data = num + 2;
			p->next = la->next;
			la->next = p;
		}
	}
	return la;
}

LinkList TailCreate(LinkList la)//按要求建立单链表（尾插法）
{
	la = (LinkList)malloc(sizeof(LNode));
	if (la)
		la->next = NULL;
	else
		return ERROR;
	LinkList s, r = la;
	for (int num = 0; num < 4; num++)
	{
		s = (LinkList)malloc(sizeof(LNode));
		if (s)
		{
			s->data = num + 2;
			r->next = s;
			r = s;
		}
		else
			return ERROR;
	}
	r->next = NULL;
	return la;
}

int LengthList(LinkList la)//获取单链表的表长
{
	int nLen = 0;
	LinkList p = la->next;
	while (p)
	{
		p = p->next;
		nLen++;
	}
	return nLen;
}

void TravelList(LinkList la)//单链表遍历
{
	LinkList p = la->next;
	printf("单链表遍历如下：\n>> head");
	while (p != NULL)
	{
		printf(" -> %d", p->data);
		p = p->next;
	}
	printf("\n单链表打印完毕，长度为 %d。\n", LengthList(la));
	return;
}

LinkList GetElem(LinkList la, int i)//单链表的按位查找
{
	int j = 1;
	LNode* p = la->next;
	if (i < 1)
		return NULL;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	return p;
}

int LocalElem(LinkList la, int e)//单链表的按值查找
{
	int i = 1;
	LinkList p = la->next;
	while (p != NULL)
	{
		if (p->data == e)
			break;
		else
		{
			p = p->next;
			i++;
		}
	}
	return i;
}

bool InsertList(LinkList la, int i, int e)//单链表插入操作（其中 i 为位置，e 为数值）
{
	int j = 1;
	LinkList p = la, s;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (p == NULL)
		return false;
	if ((s = (LinkList)malloc(sizeof(LNode))) == NULL)
		return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool DeleteList(LinkList la, int i)//单链表删除操作
{
	int j = 1;
	LinkList p = la, q;
	while (p && j < i) //p指向第 i-1 个元素
	{
		p = p->next;
		j++;
	}
	if (p == NULL || p->next == NULL) //表示不存在第 i-1 个和第 i 的元素
		return false;
	q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

LinkList Reserve(LinkList la)//单链表逆置
{
	if (la == NULL || la->next == NULL)
		return la;
	LinkList p = la->next, q = p->next, r = q->next;
	la->next = NULL;
	p->next = NULL;
	while (r != NULL)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	la->next = q;
	return la;
}

int ClearMyList(LinkList *la)//销毁单链表
{
	LinkList q;
	while (*la)
	{
		q = (*la)->next;
		free(*la);
		*la = q;
	}
	if (*la)
		return ERROR;
	else
		return OK;
}

/*以上是链式表实现函数，以下是主函数*/

int main()//主函数
{
	int length, value, flag;
	system("chcp 936&title 顺序表演示&color e&cls");
	Sequenlist* L;
	L = create();
	if (!L)
	{
		printf("\a错误：创建线性表失败！");
		goto next;
	}
	length = Length(L);
	printf("顺序表创建成功，其长度为 %d。\n", length);
	print(L);
	printf("顺现在开始在元素 4 和 5 之间插入元素 9。\n");
	value = Find(L, 4);
	if (value)
	{
		printf(">> 确认元素 4 所在的位置为 %d。\n正在执行插入元素 9，请稍候。\n", value);
		Insert(L, 9, value + 1);
		value = Find(L, 9);
		if (value)
			printf(">> 元素 9 已成功插入。\n");
		else
			printf("\a>> 元素 9 插入失败！\n");
	}
	else
		printf("\a>> 元素 4 不在表中，插入失败。");
	print(L);
	printf("正在查找位置 3 上的元素，请稍候。\n");
	value = GetData(L, 3);
	if (value)
		printf(">> 位置为 3 上的元素为 %d。\n", value);
	else
		printf("\a>> 位置 3 上的元素不存在。\n");
	flag = Delete(L, 3);
	if (flag)
		printf(">> 删除指定元素成功！\n");
	else
		printf("\a>> 删除指定元素失败！\n");
	print(L);
	printf("演示完毕，正在销毁顺序表，请稍候。\n");
	flag = Destroy(L);
	if (flag)
		printf(">> 顺序表销毁成功！");
	else
		printf("\a>> 顺序表销毁失败！");
	printf("\n\n\n顺序表演示完毕，请按任意键演示链式表。\n");
	system("pause>nul");
	//以上是顺序表主程序，以下是链式表主程序。
next:
	system("title 链式表演示&color a&cls");
	LNode la;
	LinkList p;
	p = HeadCreate(&la); //头插法创建单链表（也可以使用尾插法）
	if (!p)
	{
		system("cls");
		printf("\a链表创建失败，请按任意键退出。\n");
		system("pause>nul&cls");
		return -1;
	}
	printf("链表创建成功，首结点地址：%p。\n", GetElem(p, 1));
	TravelList(p);
	printf("正在获取值为 4 的元素所在的位置，请稍候。\n");
	value = LocalElem(p, 4);//单链表的查找值为 4 的元素
	if (value)
	{
		printf(">> 获取成功，其位置为 %d。\n", value);
		printf("尝试插入元素 9，请稍候。\n");
		if (InsertList(p, value, 9))
			printf(">> 元素插入成功。\n");
		else
			printf("\a>> 元素插入失败！\n");
	}
	else
		printf("\a>> 获取失败，可能是元素不存在。\n");
	TravelList(p);
	printf("尝试删除链表的第 3 个元素，请稍候。\n");
	if (DeleteList(p, 3)) //删除链表的第 3 个元素
		printf(">> 删除指定元素成功。\n");
	else
		printf("\a>> 删除指定元素失败！\n");
	TravelList(p);
	p = Reserve(p);
	TravelList(p);
	printf("正在尝试销毁单链表，请稍候。\n");
	if (ClearMyList(&p))
		printf(">> 单链表销毁成功。\n");
	else
		printf("\a>> 单链表销毁失败！\n");
	printf("\n\n演示完毕，请按任意键退出本程序。\n");
	system("pause>nul&cls");
	return 0;
}