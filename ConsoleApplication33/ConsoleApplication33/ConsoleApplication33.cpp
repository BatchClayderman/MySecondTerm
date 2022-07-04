#include <iostream>
#include <fstream>
#define MaxCode 1000
typedef struct char_count* count_node;
typedef struct HNodeType* HNode;
typedef struct charCode* code;
int n = 0, num = 0, sumStrLen = 0;//输入不同字符的个数，num会改变，所以n用来保存num的值，sumStrLen保存编码前字符串长度
char str[100000] = { 0 }, PathFile[MaxCode] = { 0 }, hfmTreeFile[MaxCode] = { 0 }, CodeFile[MaxCode] = { 0 }, TextFile[MaxCode] = { 0 }, buf[10 * MaxCode] = { 0 };//编码前的字符串
short int codeStr[100000000] = { 0 };//编码后的比特
using namespace std;

struct char_count//从字符串中分离字符
{
	char ch;//字符
	long int count;//出现的次数
	short int bit;//分配的比特
};
count_node weight[126];//用来记录各个字符的权值和在哈夫曼树中这个结点被分配到的比特

struct HNodeType
{
	count_node node;//结点
	HNode parent;//父结点
	HNode lchild;//左孩子
	HNode rchild;//右孩子
};
HNode p;//用来记录哈夫曼树的树根，也是个工作指针

struct charCode//字符集
{
	char ch;//字符
	short int codeNum[MaxCode];//编码
	int codeLen;//编码的长度
};
code char_code[125];//用来记录各字符编码的信息

void tranCode(int len)//译码
{
	HNode q = p;
	FILE* fp;
	fopen_s(&fp, TextFile, "w");
	cout << endl << "译码结果：" << endl;
	for (int i = 0; i < len; ++i)
	{
		if (q && codeStr[i] == 0)
		{
			q = q->lchild;//进入左子树
			if (q && q->node->ch)
			{
				cout << q->node->ch;
				if (fp)
					fputc(q->node->ch, fp);
				q = p;
			}
		}
		if (q && codeStr[i] == 1)
		{
			q = q->rchild;//进入右子树
			if (q && q->node->ch)
			{
				cout << q->node->ch;
				if (fp)
					fputc(q->node->ch, fp);
				q = p;
			}
		}
	}
	if (fp)
	{
		fclose(fp);
		cout << endl << "已成功将译码转存为文件，双击相应文件即可查看。" << endl;
	}
	else
		cout << endl << "错误：打开文件失败，无法转存译码文件。" << endl;
	return;
}

int finishCode()//把字符串编码，返回编码后数组的长度
{
	int m = 0;
	char c[10] = { 0 };
	FILE* fp;
	fopen_s(&fp, CodeFile, "w");
	cout << endl << "编码结果：" << endl;
	for (int i = 0; i < sumStrLen; ++i)
		for (int j = 0; j < sumStrLen; ++j)
			if (char_code[j]->ch == str[i])
			{
				for (int k = 0; k < char_code[j]->codeLen; ++k)
				{
					codeStr[m] = char_code[j]->codeNum[k];
					cout << codeStr[m];
					sprintf_s(c, "%hd", codeStr[m]);
					if (fp)
						fputs(c, fp);
					m++;
				}
				break;
			}
	cout << endl;
	if (fp)
	{
		cout << "已成功将编码转存为文件，双击相应文件即可查看。" << endl;
		fclose(fp);
	}
	else
		cout << "错误：打开文件失败，无法转存编码文件。" << endl;
	return m;
}

void efficiency(int len)//计算压缩效率
{
	int sumCodeLen = 0;
	for (int i = 0; i <= len; ++i)
		sumCodeLen += char_code[i]->codeLen;
	cout << endl << "压缩效率：" << sumCodeLen << " / " << sumStrLen << " = " << sumCodeLen * 1.0 / sumStrLen << endl;
	return;
}

void getCode()//获取各个字符的编码
{
	for (int i = 0; i < 125; ++i)
	{
		char_code[i] = new charCode();
		for (int j = 0; j < 1000; ++j)
			char_code[i]->codeNum[j] = -1;
	}
	int cache[1000] = { 0 }, i = 0, j = 0;
	HNode q1 = p, q2;
	while (q1->lchild)//左孩子
	{
		char_code[i]->ch = q1->lchild->node->ch;
		j = 0;
		cache[j] = q1->lchild->node->bit;
		j++;
		q2 = q1;
		while (q2->node->bit)
		{
			cache[j] = q2->node->bit;
			j++;
			q2 = q2->parent;
		}
		int m = 0;
		for (int k = j - 1; k >= 0; k--)
		{
			char_code[i]->codeNum[m] = cache[k];
			m++;
		}
		char_code[i]->codeLen = m;
		i++;
		if (q1->rchild)
			q1 = q1->rchild;
		else
			break;
	}
	q1 = p;
	if (q1->rchild)//右孩子
	{
		j = 0;
		int cache2[1000] = { 0 };
		while (q1->rchild)
		{
			cache[j] = q1->rchild->node->bit;
			j++;
			if (q1->rchild->node->ch)
				char_code[i]->ch = q1->rchild->node->ch;
			q1 = q1->rchild;
		}
		int m = 0;
		for (int k = j - 1; k >= 0; k--)
		{
			char_code[i]->codeNum[m] = cache[k];
			m++;
		}
		char_code[i]->codeLen = m;
	}
	cout << endl << "获得各字符的编码：" << endl;
	for (int k = 0; k <= i; ++k)
	{
		if (char_code[k]->ch)
		{
			cout << "字符：" << char_code[k]->ch << "\t\t编码：";
			int k2 = 0;
			while (char_code[k]->codeNum[k2] != -1)
			{
				cout << char_code[k]->codeNum[k2];
				k2++;
			}
		}
		cout << endl;
	}
	efficiency(i);//统计压缩效率
	tranCode(finishCode());//编码译码
	return;
}

void coder(HNode p)//分配比特
{
	if (p)
	{
		if (p->lchild)
			p->lchild->node->bit = 0;
		if (p->rchild)
			p->rchild->node->bit = 1;
		if (p->lchild)
			coder(p->lchild);
		if (p->rchild)
			coder(p->rchild);
	}
	return;
}

void outputHafftree(HNode p)//递归法先序遍历哈夫曼树
{
	char tmp[20] = { 0 };
	if (p)
	{
		if (p->node->ch != NULL)//访问根节点
		{
			cout << "字符：" << p->node->ch << "\t\t权值：" << p->node->count << endl;
			buf[strlen(buf)] = p->node->ch;
			buf[strlen(buf)] = ':';
			sprintf_s(tmp, "%d", p->node->count);
			for (unsigned int i = 0; i < strlen(tmp); ++i)
				buf[i + strlen(buf)] = tmp[i];
		}
		else if (p->node->count)
			cout << "（新增结点）\t权值：" << p->node->count << endl;
		if (p->lchild)//递归处理左子树
		{
			buf[strlen(buf)] = '(';
			outputHafftree(p->lchild);
		}
		if (p->rchild)//递归处理右子树
		{
			buf[strlen(buf)] = ',';
			outputHafftree(p->rchild);
			buf[strlen(buf)] = ')';
		}
	}
	return;
}

void HaffmanTree(bool flag)//创建哈夫曼树
{
	HNode hNl= new HNodeType(), hNr= new HNodeType();
	hNl->lchild = hNl->rchild = NULL;//该结点（将成为左孩子）的左右子树置为NULL
	hNl->node = weight[1];//该结点（将成为左孩子）的核心结点置为weight中未使用的最小count的结点
	hNr->lchild = hNr->rchild = NULL;//该结点（将成为左孩子）的左右子树置为NULL
	if (n == 1)//只有一个不同字符的情况
	{
		hNr->node = NULL;//没有右孩子，右孩子置NULL
		p = hNl->parent = new HNodeType();//左孩子和右孩子的父亲置为一个新的结点，并使工作指针p指向它
		p->lchild = hNl;//新结点的左孩子置为旧的这个左孩子
		p->rchild = NULL;//新结点的右孩子置为NULL
		p->node = new char_count();//给新父亲分配空间
		p->node->ch = NULL;//新增的父亲的核心结点的ch置NULL
		p->node->count = p->lchild->node->count;//父亲权值为两个孩子权值的和
		p->parent = NULL;//置空哈夫曼树根结点中的父亲结点
	}
	else
	{
		hNr->node = weight[2];//即将成为右孩子的核心结点置为weight中未使用的最小count的结点
		for (int i = 3; i <= n; ++i)
		{
			p = hNl->parent = hNr->parent = new HNodeType();//左孩子和右孩子的父亲置为一个新的结点，并使工作指针p指向它
			p->lchild = hNl;//新结点的左孩子置为旧的这个左孩子
			p->rchild = hNr;//新结点的右孩子置为旧的这个右孩子
			p->node = new char_count();//给新父亲分配空间
			p->node->ch = NULL;//新增的父亲的核心结点的ch置NULL
			p->node->count = p->lchild->node->count + p->rchild->node->count;//父亲权值为两个孩子权值的和
			hNl = new HNodeType();//给旧的左孩子（将再次成为一个左孩子）重新分配空间
			hNl->node = weight[i];//旧的左孩子（将再次成为一个左孩子）的核心结点置为weight中未使用的最小count的结点
			hNl->lchild = hNl->rchild = NULL;//旧的左孩子（将再次成为一个左孩子）的左右子树置为NULL
			hNr = p;//旧的右孩子成为父亲
		}//生成哈夫曼树的根结点
		p = hNl->parent = hNr->parent = new HNodeType();//左孩子和右孩子的父亲置为一个新的结点，并使工作指针p指向它
		p->lchild = hNl;//新结点的左孩子置为旧的这个左孩子
		p->rchild = hNr;//新结点的右孩子置为旧的这个右孩子
		p->node = new char_count();//给新父亲分配空间
		p->node->ch = NULL;//新增的父亲的核心结点的ch置NULL
		p->node->count = p->lchild->node->count + p->rchild->node->count;//父亲权值为两个孩子权值的和
		p->parent = NULL;//置空哈夫曼树根结点中的父亲结点
	}
	cout << endl << "先序遍历哈夫曼树：" << endl;
	outputHafftree(p);
	if (weight[2]->ch == NULL)
		buf[strlen(buf)] = ')';
	if (flag)
	{
		cout << endl << "尝试将以下内容写入文件：" << endl << buf << endl;
		FILE* fp;
		fopen_s(&fp, hfmTreeFile, "w");
		if (fp)
		{
			fputs(buf, fp);
			fclose(fp);
			cout << "已成功将哈夫曼树转存为文件，双击相应文件即可查看。" << endl;
		}
		else
			cout << "错误：打开文件失败，无法转存哈夫曼树文件。" << endl;
	}
	coder(p);
	return;
}

bool translate()//从文件转换字符到内存中
{
	char tmp[20] = { 0 };
	int j = 0;
	for (unsigned int i = 1; i < strlen(buf); ++i)
	{
		if (j >= MaxCode)
			return false;
		while (strlen(tmp) > 0)
			tmp[strlen(tmp) - 1] = 0;
		if (buf[i] == ':' && i + 1 < strlen(buf))
		{
			if (buf[i + 1] == ':')
				i++;
			num++;
			n++;
			j++;
			weight[j]->ch = buf[i - 1];
			i++;
			while (buf[i] != ',' && buf[i] != ')' && buf[i] != '\0' && buf[i] >= '0' && buf[i] <= '9')
			{
				tmp[strlen(tmp)] = buf[i];
				i++;
			}
			rewind(stdin);
			if (sscanf_s(tmp, "%d", &(weight[j]->count)) != 1)
				weight[j]->count = 1;
		}
	}
	if (weight[1]->ch == NULL)
		return false;
	return true;
}

void swap(int x, int y)//交换堆中的两个元素
{
	count_node t;
	t = weight[x];
	weight[x] = weight[y];
	weight[y] = t;
	return;
}

void siftdown(int i)//向下调整
{
	int t, flag = 0;
	while (i * 2 <= num && flag == 0)
	{
		if (weight[i]->count < weight[i * 2]->count)
			t = i << 1;
		else
			t = i;
		if (i * 2 + 1 <= num && weight[t]->count < weight[i * 2 + 1]->count)
			t = i * 2 + 1;
		if (t != i)
		{
			swap(t, i);
			i = t;
		}
		else
			flag = 1;
	}
	return;
}

void InitHeap()//建立堆
{
	for (int i = num / 2; i >= 1; i--)
		siftdown(i);
	return;
}

void heapsort()//堆排序
{
	while (num > 1)
	{
		swap(1, num);
		num--;
		siftdown(1);
	}
	return;
}

void priority_queue()//构造权值低的先出的优先队列（最小堆）
{
	InitHeap();
	heapsort();
	cout << endl << "建立最小堆（权值小的先出）：" << endl;
	for (int i = 1; i <= n; ++i)
		cout << "字符：" << weight[i]->ch << "\t\t权值：" << weight[i]->count << endl;
	return;
}

void GetStrWeight1()//接收用户输入的字符串并统计每个字符分别出现的次数
{
	long int count[126] = { 0 };
	char c;
	rewind(stdin);
	cout << "请输入字符串进行编码，编码完成后将自动译码：" << endl;
	while ((c = getchar()) >= '!')
	{
		count[c - 32]++;
		str[sumStrLen] = c;
		sumStrLen++;
	}
	rewind(stdin);
	sumStrLen <<= 3;
	int j = 1;
	cout << endl;
	for (int i = 1; i < 126; ++i)
		if (count[i] > 0)
		{
			weight[j]->ch = i + 32;
			weight[j]->count = count[i];
			cout << "字符：" << weight[j]->ch << "\t\t出现 " << weight[j]->count << " 次" << endl;
			j++;
			num++;
		}
	n = num;
	return;
}

void GetStrWeight2()//统计从文件当中获取的字符串中每个字符出现的次数
{
	int i = 0, j = 1;
	long int count[126] = { 0 };
	while (str[i] >= '!')
	{
		count[str[i] - 32]++;
		sumStrLen++;
		i++;
	}
	sumStrLen <<= 3;
	for (int i = 1; i < 126; ++i)
		if (count[i] > 0)
		{
			weight[j]->ch = i + 32;
			weight[j]->count = count[i];
			cout << "字符：" << weight[j]->ch << "\t\t出现 " << weight[j]->count << " 次" << endl;
			j++;
			num++;
		}
	n = num;
	return;
}

void get_file()//获取合法文件中的字符
{
	char path[1000] = { 0 };
	cout << "请输入文件路径：" << endl;
	rewind(stdin);
	fgets(path, sizeof(path), stdin);
	rewind(stdin);
	path[strlen(path) - 1] = '\0';
	if (path[strlen(path) - 1] == '\"')
		path[strlen(path) - 1] = '\0';
	if (path[0] == '\"')
	{
		for (unsigned int i = 0; i < strlen(path) - 1; ++i)
			path[i] = path[i + 1];
		path[strlen(path) - 1] = '\0';
	}
	ifstream fin(path);//以只读模式打开文件
	fin >> str;
	cout << endl << "文件内容：" << endl << str << endl << endl;
	return;
}

void Initbuf()//初始化
{
	for (int i = 0; i < MaxCode; ++i)
		buf[i] = 0;
	for (int i = 0; i < 100000; ++i)
		str[i] = 0;
	for (int i = 0; i < 100000000; ++i)
		codeStr[i] = 0;
	for (int i = 0; i < 126; ++i)
		weight[i] = new char_count();
	num = 0;
	n = num;
	sumStrLen = 0;
	return;
}

void task1()
{
	system("cls");
	short int choose;
	char FileOp[3 * MaxCode] = { 0 };
	cout << "/********** 哈夫曼树编码译码相关文件管理面板 **********/" << endl;
	cout << "\t0 = 返回\t1 = 隐藏\t2 = 锁定" << endl;
	cout << "\t3 = 解锁\t4 = 删除\t5 = 浏览" << endl;
	cout << "\t6 = 打开相关文件所在文件夹" << endl;
	cout << endl << "所有输入字符必须为英文字符，请选择一项以继续：";
	rewind(stdin);
	if (scanf_s("%hd", &choose) != 1)
		choose = 0;
	rewind(stdin);
	switch (choose)
	{
	case 1:
		strcat_s(FileOp, "attrib +a +h +r +s \"");
		strcat_s(FileOp, hfmTreeFile);
		strcat_s(FileOp, "\"&attrib +a +h +r +s \"");
		strcat_s(FileOp, CodeFile);
		strcat_s(FileOp, "\"&attrib +a +h +r +s \"");
		strcat_s(FileOp, TextFile);
		strcat_s(FileOp, "\"");
		system(FileOp);
		break;
	case 2:
		strcat_s(FileOp, "attrib +a -h +r +s \"");
		strcat_s(FileOp, hfmTreeFile);
		strcat_s(FileOp, "\"&attrib +a -h +r +s \"");
		strcat_s(FileOp, CodeFile);
		strcat_s(FileOp, "\"&attrib +a -h +r +s \"");
		strcat_s(FileOp, TextFile);
		strcat_s(FileOp, "\"");
		system(FileOp);
		break;
	case 3:
		strcat_s(FileOp, "attrib +a -h -r -s \"");
		strcat_s(FileOp, hfmTreeFile);
		strcat_s(FileOp, "\"&attrib +a -h -r -s \"");
		strcat_s(FileOp, CodeFile);
		strcat_s(FileOp, "\"&attrib +a -h -r -s \"");
		strcat_s(FileOp, TextFile);
		strcat_s(FileOp, "\"");
		system(FileOp);
		break;
	case 4:
		strcat_s(FileOp, "del /a /f /q \"");
		strcat_s(FileOp, hfmTreeFile);
		strcat_s(FileOp, "\"&del /a /f /q \"");
		strcat_s(FileOp, CodeFile);
		strcat_s(FileOp, "\"&del /a /f /q \"");
		strcat_s(FileOp, TextFile);
		strcat_s(FileOp, "\"");
		system(FileOp);
		break;
	case 5:
		system("cls");
		strcat_s(FileOp, "echo hfmTreeFile.txt：&type \"");
		strcat_s(FileOp, hfmTreeFile);
		strcat_s(FileOp, "\"&echo.&echo.&echo CodeFile.txt：&type \"");
		strcat_s(FileOp, CodeFile);
		strcat_s(FileOp, "\"&echo.&echo.&echo TextFile.txt：&type \"");
		strcat_s(FileOp, TextFile);
		strcat_s(FileOp, "\"&echo.");
		system(FileOp);
		break;
	case 6:
		strcat_s(FileOp, "explorer \"");
		strcat_s(FileOp, PathFile);
		system(FileOp);
		break;
	default:
		return;
	}
	cout << endl << endl << "操作完毕，请按任意键返回。" << endl;
	system("pause>nul");
}

void task2()
{
	int total = 0, qt = 0;
	char ch = 0;
	bool flag = false;
	cout << "请输入字符集大小（1-125）：";
	rewind(stdin);
	while (scanf_s("%d", &total) != 1 || total < 1 || total > 125)
		rewind(stdin);
	for (int i = 1; i <= total; ++i)
	{
		do
		{
			flag = false;
			cout << "请输入第 " << i << " 个字符：";
			rewind(stdin);
			scanf_s("%c", &ch, sizeof(ch));
			if (ch < '!')
			{
				flag = true;
				continue;
			}
			for (int j = 1; j < i; ++j)
				if (weight[j]->ch == ch)
				{
					flag = true;
					break;
				}
		} while (flag);
		weight[i]->ch = ch;
		cout << "请输入字符 " << ch << " 对应的权值：";
		rewind(stdin);
		while (scanf_s("%d", &qt) != 1 || qt < 1 || qt > MaxCode)
			rewind(stdin);
		weight[i]->count = qt;
	}
	n = total;
	num = total;
	priority_queue();
	HaffmanTree(true);
	do
	{
		rewind(stdin);
		cout << endl << "请依照上述字符，输入待编码字符串：" << endl;
		scanf_s("%s", &str, sizeof(str));
		flag = true;
		for (unsigned int i = 0; i < strlen(str); ++i)
		{
			flag = true;
			for (int j = 1; j <= total; ++j)
				if (str[i] == weight[j]->ch)
				{
					flag = false;
					break;
				}
			if (flag)
				break;
		}
	} while (flag);
	rewind(stdin);
	sumStrLen = strlen(str) << 3;
	getCode();
	return;
}

void task3()
{
	GetStrWeight1();
	priority_queue();
	HaffmanTree(true);
	getCode();
	return;
}

void task4()
{
	get_file();
	GetStrWeight2();
	priority_queue();
	HaffmanTree(true);
	getCode();
	return;
}

void task5()
{
	ifstream fin(hfmTreeFile);//以只读模式打开文件
	fin >> buf;
	cout << "读取文件内容输出如下：" << endl;
	cout << buf << endl;
	if (!translate())
	{
		cout << "解析文件内容失败，无法继续。" << endl << "请尝试使用其它功能修复以此问题，按任意键返回。" << endl;
		return;
	}
	priority_queue();
	HaffmanTree(false);
	bool flag = false;
	do
	{
		rewind(stdin);
		cout << endl << "请依照上述字符，输入待编码字符串：" << endl;
		scanf_s("%s", &str, sizeof(str));
		flag = true;
		for (unsigned int i = 0; i < strlen(str) - 1; ++i)
		{
			flag = true;
			for (int j = 1; j <= n; ++j)
				if (str[i] == weight[j]->ch)
				{
					flag = false;
					break;
				}
			if (flag)
				break;
		}
	} while (flag);
	rewind(stdin);
	sumStrLen = strlen(str) << 3;
	getCode();
	return;
}

void HighRun(char* commandline, const char* option)//以管理员身份运行
{
	char c[1000] = "mshta vbscript:createobject(\"shell.application\").shellexecute(\"cmd.exe\",\"/c start /realtime \"\"\"\" \"\"";
	strcat_s(c, commandline);
	strcat_s(c, "\"\" ");
	strcat_s(c, option);
	strcat_s(c, "\",\"\",\"runas\",\"1\")(window.close)");
	system(c);
}

void getpath(const char* v)//获取文件路径
{
	for (int i = strlen(v) - 1; i >= 0; i--)
	{
		if (v[i] == '\\')
		{
			for (int j = 0; j < i; ++j)
			{
				PathFile[j] = v[j];
				hfmTreeFile[j] = v[j];
				CodeFile[j] = v[j];
				TextFile[j] = v[j];
			}
			strcat_s(hfmTreeFile, "\\hfmTreeFile.txt");
			strcat_s(CodeFile, "\\CodeFile.txt");
			strcat_s(TextFile, "\\TextFile.txt");
			break;
		}
	}
	cout << "正在尝试获取相关路径信息：" << endl << PathFile << endl << hfmTreeFile << endl << CodeFile << endl << TextFile << endl << endl << "获取完成，正在发起跳转。" << endl;
	return;
}

int main(int argc, char* argv[])
{
	system("chcp 936&title 哈夫曼树编码译码处理器&color e&cls");
	if (strlen(argv[0]) > MaxCode - 20 || strlen(argv[0]) < 8)
	{
		cout << "警告：程序所处目录路径过长或目录深度过大，将会自动切换到“C:\\HaffmanTree\\”目录下。" << endl;
		system("pause&cls");
		getpath("C:\\HaffmanTree\\1.exe");
	}
	else
		getpath(argv[0]);
	short int choose = 0;
	while (true)
	{
		Initbuf();
		system("cls");
		cout << "/*************** 哈夫曼树编码译码处理器 ***************/" << endl;
		cout << "\t1 = 隐藏、锁定、解锁或删除处理器的相关文件" << endl;
		cout << "\t2 = 由向导带领着从终端输入并进行编码译码" << endl;
		cout << "\t3 = 直接输入字符串并进行哈夫曼编码译码" << endl;
		cout << "\t4 = 选择一个文件并进行哈夫曼编码译码" << endl;
		cout << "\t5 = 利用已有文件进行哈夫曼编码译码" << endl;
		cout << "\t6 = 以管理员权限重新启动本处理器" << endl;
		cout << "\t0 = 退出哈夫曼树编码译码处理器" << endl;
		cout << endl << "所有输入字符必须为英文字符，请选择一项以继续：";
		rewind(stdin);
		if (scanf_s("%hd", &choose) != 1)
			choose = 0;
		rewind(stdin);
		cout << endl << endl;
		switch (choose)
		{
		case 1:
			task1();
			continue;
		case 2:
			task2();
			break;
		case 3:
			task3();
			break;
		case 4:
			task4();
			break;
		case 5:
			task5();
			break;
		case 6:
			cout << "已发起运行，请手动确认授权，并按任意键关闭本窗口。" << endl;
			HighRun(argv[0], "");
			system("pause>nul&cls");
			exit(0);
		case 0:
			system("cls");
			cout << "欢迎再次使用，请按任意键退出。" << endl;
			system("pause>nul&cls");
			exit(0);
		default:
			continue;
		}
		cout << endl << endl << "操作完毕，请按任意键返回。" << endl;
		system("pause>nul");
	}
	return 9009;
}