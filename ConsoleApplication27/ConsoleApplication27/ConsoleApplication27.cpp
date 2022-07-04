#include <iostream>
#define MAXTREE 200
using namespace std;
typedef char ElemType;

typedef struct BiTNode//二叉树
{
	ElemType data;
	struct BiTNode* lchild, * rchild;
}*BiTree, BiTNode;

void raiseError()//抛出异常
{
	system("cls");
	cout << "\a很抱歉，程序发生异常，请检查您的输入，并确保内存资源充足，按任意键退出。" << endl;
	system("pause>nul");
	return;
}

void CreateTree(BiTree& b, char str[])//建立二叉树
{
	char ch;
	BiTree stack[MAXTREE] = { 0 }, p = NULL;
	int top = -1, k = 1, j = 0;//k = 1 为左孩子，2 为右孩子
	while ((ch = str[j++]) != '\0')
	{
		switch(ch)
		{
		case '(':
			top++;
			if (top < 0 || top > MAXTREE)
			{
				raiseError();
				exit(-1);
			}
			stack[top] = p;//根节点入栈
			k = 1;
			break;
		case ',':
			k = 2;
			break;
		case ')':
			top--;//根节点出栈
			break;
		case ' ':
			break;
		default:
			p = (BiTree)malloc(sizeof(BiTNode));
			if (!p)
			{
				raiseError();
				exit(-1);
			}
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)//树为空时
				b = p;
			else//树非空时
			{
				switch(k)
				{
				case 1:
					if (top < 0 || top > MAXTREE || stack[top] == NULL)
					{
						raiseError();
						exit(-1);
					}
					stack[top]->lchild = p;
					break;
				case 2:
					if (top < 0 || top > MAXTREE || stack[top] == NULL)
					{
						raiseError();
						exit(-1);
					}
					stack[top]->rchild = p;
					break;
				default:
					raiseError();
				}
			}
		}
	}
	return;
} 

void PrintTree(BiTree b)//递归打印二叉树
{
	if (b)
	{
		cout << b->data;//访问根节点
		if( b->lchild != NULL || b->rchild != NULL )
		{
			cout << "(";
			PrintTree(b->lchild);//递归处理左子树
			if(b->rchild != NULL)
				cout << ",";
			PrintTree(b->rchild);//递归处理右子树
			cout << ")";
		}
	}
	return;
} 

bool BiTree_Revolute(BiTree &T)//左右子树交换
{
	if (!T)
		return false;
	BiTNode* temp;
	if (T->lchild != NULL && T->rchild != NULL)
	{
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
	BiTree_Revolute(T->lchild);
	BiTree_Revolute(T->rchild);
	return true;
}

BiTree FreeTree(BiTree b)//销毁二叉树
{
	if (b == NULL)
		return b;
	else
	{
		FreeTree(b->lchild);//递归释放左子树
		FreeTree(b->rchild);//递归释放右子树
		free(b);//释放根节点
		b = NULL;//释放指向根节点的指针
	}
	return b;
}

int TreeSize(BiTNode* root)//结点个数 = 树的左子树结点 + 右子树结点 + 根结点数
{
	if (root == NULL)
		return 0;
	size_t lsize = TreeSize(root->lchild);//递归统计左子树的节点个数
	size_t rsize = TreeSize(root->rchild);//递归统计右子树的节点个数
	return 1 + lsize + rsize;
}

int main()
{
	system("chcp 936&title 二叉树&color e&cls");
	BiTree T = NULL;
	char strings[4 * MAXTREE] = { 0 };
	cout << "示例（所有字符均为英语字符）：(A(B(C(D,E),F),G(H,I(J,K))))" << endl << "元素形式为字符，如果输入的不为二叉树，但为合法的树，程序会继续运行。" << endl << "请参照上述示例建立二叉树：";
	rewind(stdin);
	fgets(strings,sizeof(strings),stdin);
	strings[strlen(strings) - 1] = '\0';
	rewind(stdin); 
	CreateTree(T, strings);
	system("cls");
	cout << "建立二叉树成功，开始演示。" << endl << endl;
	cout << "遍历二叉树输出如下：" << endl << "(";
	PrintTree(T);
	cout << ")" << endl << "该树共有 " << TreeSize(T) << " 个结点。" << endl;
	cout << endl << "正在交换左右子树，请稍候。" << endl;
	if (BiTree_Revolute(T))
	{
		cout << "交换成功，遍历二叉树输出如下：" << endl << "(";
		PrintTree(T);
		cout << ")" << endl << endl << "演示完毕，正在尝试销毁二叉树。" << endl;
	}
	else
		cout << "交换失败，正在尝试销毁二叉树。" << endl;
	if (FreeTree(T))
		cout << "销毁二叉树失败，请按任意键退出。" << endl;
	else
		cout << "销毁二叉树成功，请按任意键退出。" << endl;
	system("pause>nul&cls");
	return 0;
}