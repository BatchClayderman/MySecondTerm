#include <iostream>
#define N 4095
using namespace std;

typedef struct//String struct
{
	char ch[N];
	int length;
}SeqString;

FILE* getfile()//获取文件路径
{
	char fname[N] = { 0 };
	FILE* fp;
	cout << "请输入文件路径，或在非管理员模式下将文件拖拽至此：" << endl;
	rewind(stdin);
	fgets(fname, sizeof(fname), stdin);
	rewind(stdin);
	fname[strlen(fname) - 1] = '\0';
	if (fname[strlen(fname) - 1] == '\"')
		fname[strlen(fname) - 1] = '\0';
	if (fname[0] == '\"')
	{
		for (unsigned int i = 0; i < strlen(fname) - 1; i++)
			fname[i] = fname[i + 1];
		fname[strlen(fname) - 1] = '\0';
	}
	fopen_s(&fp, fname, "r");
	cout << endl;
	return fp;
}

void HighRun(const char* commandline, const char* option)//以管理员身份运行
{
	cout << "已发起运行，请手动通过授权，按任意键可返回。" << endl;
	char c[N] = "mshta vbscript:createobject(\"shell.application\").shellexecute(\"cmd.exe\",\"/c start /realtime \"\"\"\" \"\"";
	strcat_s(c, commandline);
	strcat_s(c, "\"\" ");
	strcat_s(c, option);
	strcat_s(c, "\",\"\",\"runas\",\"1\")(window.close)");
	system(c);
}

void NewFile()//建立或者编辑文件
{
	char fname[N] = { 0 }, cmdline[15] = "notepad.exe";
	cout << "请输入文件路径，或在非管理员模式下将文件拖拽至此：" << endl;
	rewind(stdin);
	fgets(fname, sizeof(fname), stdin);
	rewind(stdin);
	fname[strlen(fname) - 1] = '\0';
	if (fname[strlen(fname) - 1] == '\"')
		fname[strlen(fname) - 1] = '\0';
	if (fname[0] == '\"')
	{
		for (unsigned int i = 0; i < strlen(fname) - 1; i++)
			fname[i] = fname[i + 1];
		fname[strlen(fname) - 1] = '\0';
	}
	cout << endl;
	for (unsigned int i = 0; i < strlen(fname); i++)
		if ((fname[i] > 0 && fname[i] < 32) || fname[i] == '/' || fname[i] == '*' || fname[i] == '?' || fname[i] == '\"' || fname[i] == '<' || fname[i] == '>' || fname[i] == '|' || fname[i] == '&')
		{
			cout << "\a错误：输入的路径不合法，请按任意键返回。" << endl;
			return;
		}
	HighRun(cmdline, fname);
}

void LineCount()//统计行数
{
	FILE* fp;
	char buf[N] = { 0 };
	int i = 0, count = 1;
	if ((fp = getfile()) == NULL)
	{
		cout << "\a错误：打开文件失败，请检测文件是否存在，并确保程序具有足够的权限。" << endl << endl;
		return;
	}
	while (fgets(buf, N, fp) != NULL)
		if (buf[strlen(buf) - 1] == '\n')
			count++;
	fclose(fp);
	cout << "统计完毕，文件共 " << count << " 行。" << endl << endl;
}

void SubStrCount()//计算某单词数目
{
	FILE* fp;
	char fname[10] = { 0 }, ch[N] = { 0 }, ch1[N] = { 0 };
	int i = 0, total = 0;
	if ((fp = getfile()) == NULL)
	{
		cout << "\a错误：打开文件失败，请检测文件是否存在，并确保程序具有足够的权限。" << endl << endl;
		return;
	}
	cout << "请输入要统计计数的单词：";
	scanf_s("%s", ch, sizeof(ch));
	rewind(stdin);
	while (!feof(fp))
	{
		rewind(stdin);
		char c = fgetc(fp);
		rewind(stdin);
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			ch1[i++] = c;
		else {
			ch1[i] = '\0';
			if (strcmp(ch1, ch) == 0)
				total++;
			i = 0;
			memset(ch1, 0, sizeof(ch1));//清空字符数组
		}
	}
	ch1[i] = '\0';
	if (strcmp(ch1, ch) == 0)
		total++;
	cout << "经统计，该单词在文本文档中共出现 " << total << " 次。" << endl << endl;
}

void SubStrInd()//计算单词位置和行内数目
{
	FILE* fp;
	char fname[10] = { 0 }, ch[N] = { 0 }, ch1[N] = { 0 };//存放单词
	int i = 0;
	if ((fp = getfile()) == NULL)
	{
		cout << "\a错误：打开文件失败，请检测文件是否存在，并确保程序具有足够的权限。" << endl << endl;
		return;
	}
	cout << "请输入要统计计数的单词：";
	scanf_s("%s", ch, sizeof(ch));
	rewind(stdin);
	cout << endl << endl;
	int line_num = 0;//行数
	int loc = 0;//行内位置
	int number = 0;//一行中的数目
	while (!feof(fp))
	{
		char c = fgetc(fp);
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			ch1[i++] = c;
		else
		{
			ch1[i] = '\0';
			if (strcmp(ch1, ch) == 0)
			{
				number++;
				cout << "经查找，单词 " << ch << " 为文本文档中第 " << line_num + 1 << " 行第 " << loc + 1 << " 个单词。" << endl;
			}
			if (ch1[0] != '\0')
				loc++;
			i = 0;
			ch1[0] = '\0';//清空字符数组
			if (c == '\n')
			{
				loc = 0;
				cout << "经统计，单词 " << ch << " 在文本文档的第 " << line_num + 1 << " 行共出现 " << number << " 次。" << endl << endl;
				number = 0;//记得将number清零
				line_num++;//记得将行数 + 1
			}
		}
	}
	ch1[i] = '\0';
	_fcloseall();
	cout << endl;
}

int main(int argc, char* argv[])
{
	system("chcp 936&title 单词检索系统&color e&cls");
	int choice= 0;
	while (true)
	{
		system("cls");
		cout << "/********** 单词检索系统 **********/" << endl;
		cout << "\t1 = 建立或者编辑文件" << endl;
		cout << "\t2 = 统计文本文档行数" << endl;
		cout << "\t3 = 统计单词子串数目" << endl;
		cout << "\t4 = 子串定位与行数目" << endl;
		cout << "\t5 = 以管理员身份运行" << endl;
		cout << "\t0 = 退出单词检索系统" << endl << endl;
		cout << "请选择一项以继续：";
		rewind(stdin);
		while (scanf_s("%d", &choice) != 1)
			rewind(stdin);
		rewind(stdin);
		system("cls");
		switch (choice)
		{
		case 1:
			NewFile();
			system("pause>nul");
			continue;
		case 2:
			LineCount();
			break;
		case 3:
			SubStrCount();
			break;
		case 4:
			SubStrInd();
			break;
		case 5:
			HighRun(argv[0], "");
			system("pause>nul");
			continue;
		case 0:
			system("cls");
			cout << "欢迎再次使用，请按任意键退出。" << endl;
			system("pause>nul&cls");
			return 0;
		default:
			continue;
		}
		cout << endl << "执行操作完毕，请按任意键返回菜单。" << endl;
		system("pause>nul");
	}
	return 9009;
}