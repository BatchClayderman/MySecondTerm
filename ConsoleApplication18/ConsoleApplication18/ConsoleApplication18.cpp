#include <iostream>
#ifdef WIN32
#include <Windows.h>
#else
#ifdef _WIN64
#include <Windows.h>
#ifndef WIN32
#define WIN32 1
#endif
#endif
#endif//_Windows_H
#ifndef RESUME_H
#define RESUME_H
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifndef MAX_LEN
#define MAX_LEN 20
#endif
#ifndef MAX_LEN_STR
#define MAX_LEN_STR "20"
#endif
#ifndef Red
#define Red 0xC
#endif
#ifndef Yellow
#define Yellow 0xE
#endif
#ifndef White
#define White 0xF
#endif//默认输出
#endif//RESUME_H
using namespace std;
bool Outing = false;

#ifdef WIN32
string GF_GetEXEPath()
{
	char FilePath[MAX_PATH << 1];
	GetModuleFileNameA(NULL, FilePath, MAX_PATH);
	(strrchr(FilePath, '\\'))[1] = 0;
	return string(FilePath);
}
#else
string GF_GetEXEPath()
{
	int rval;
	char link_target[4096];
	char* last_slash;
	size_t result_Length;
	char* result;
	string strExeDir;
	rval = readlink("/proc/self/exe", link_target, 4096);
	if (rval < 0 || rval >= 1024)
		return "";
	link_target[rval] = 0;
	last_slash = strrchr(link_target, '/');
	if (last_slash == 0 || last_slash == link_target)
		return "";
	result_Length = last_slash - link_target;
	result = (char*)malloc(result_Length + 1);
	strncpy(result, link_target, result_Length);
	result[result_Length] = 0;
	strExeDir.append(result);
	strExeDir.append("/");
	free(result);
	return strExeDir;
}
#endif

string nnoyhjnq(string in)
{
	string out = "";
	for (size_t i = 0; i < in.length(); ++i)
		out += (in[i] + i + 1);
	return out;
}

void replace_string(char* strSrc, char* strFind, char* strReplace)//替换字符
{
	if (strSrc == NULL || strFind == NULL || strReplace == NULL)
		return;
	char* replace = strReplace, * find = strFind;
	while (*strSrc != '\0')
	{
		if (*strSrc == *strFind)
		{
			char* begin = strSrc;
			while (*strSrc != '\0' && *strFind != '\0' && (*strSrc++ == *strFind++));
			if (*strFind == '\0')
			{
				while (*strReplace != '\0' &&
					(*begin++ = *strReplace++));
				strReplace = replace;
			}
			strFind = find;
		}
		else
			strSrc++;
	}
}

void echo(string str, short int x)//输出流
{
	while (Outing);
	Outing = true;
	if (x >= 0x0 && x <= 0xF)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	cout << str << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);//归还默认色
	Outing = false;
	return;
}

void Error(string reason)//文件名有误
{
	system("cls");
	echo("\a错误：" + reason + "，请按任意键退出本程序并手动重新启动。", Red);
	system("pause>nul&cls");
	exit(EOF);
}

string getch()//获得输入并处理
{
	char b[MAX_PATH << 1] = { 0 }, lt[2] = "<", nlt[5] = "&lt;", gt[2] = ">", ngt[5] = "&gt;", space[2] = " ", nspace[7] = "&nbsp;", qua[2] = "\"", nqua[7] = "&quot;", aand[2] = "&", naand[6] = "&amp;";
	rewind(stdin);
	fflush(stdin);
	scanf_s("%s", &b, sizeof(b) >> 2);
	rewind(stdin);
	replace_string(b, lt, nlt);
	replace_string(b, gt, ngt);
	replace_string(b, space, nspace);
	replace_string(b, qua, nqua);
	replace_string(b, aand, naand);
	return string(b);
}


int main()
{
	system("chcp 936&title 个人简历生成器&cls");
	string cmd = "\"", ch, c = "if exist ", name = "Developer_", shortname = "";
	cmd += GF_GetEXEPath() + "Developer_";
	FILE* fp;
	shortname = "请输入您名字的音序（建议小写，且不超过 ";
	shortname += MAX_LEN_STR;
	shortname += " 位，如yye）：";
	echo(shortname, Yellow);
	ch = getch();
	if (ch.length() > MAX_LEN)
		Error("输入的字符太长");
	for (unsigned int k = 0; k < ch.length(); ++k)
	{
		if ((ch[k] <= 'z' && ch[k] >= 'a') || (ch[k] <= 'Z' && ch[k] >= 'A'))
			continue;
		else if (!(ch[k] == '_'))
			Error("输入含有特殊字符");
	}
	shortname = ch;
	name += ch;
	name += ".html";
	cmd += ch;
	cmd += ".html\"";
	c += cmd;
	c += " (del /a /f /q ";
	c += cmd;
	c += ")";
	system(c.c_str());
	system("cls");
	for (unsigned int k = 0; k < cmd.length() - 1; k++)
		cmd[k] = cmd[k + 1];
	cmd[cmd.length() - 2] = 0;
	fopen_s(&fp, cmd.c_str(), "w+");
	if (fp)
	{
		char ch1[MAX_PATH << 1] = "<!DOCTYPE html>\n<html xmlns=\"http://www.w3.org/1999/xhtml \">\n\t<head>\n\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charsetgbk\" />\n\t\t<title>个人简历</title>\n\t</head>\n\t<body>\n\t\t<div>\n";
		fwrite(ch1, strlen(ch1), 1, fp);
		char ch2[MAX_PATH << 1] = "\t\t\t<table border = \"1\" width=\"900\" cellspacing=\"0\" cellpadding=\"5\" align=\"center\" id=\"table\" background=\"bgphoto_";
		strcat_s(ch2, ch.c_str());
		strcat_s(ch2, ".gif\">\n\t\t\t\t<caption><h2>个人简历</h2></caption>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n\t\t\t\t\t<td width=\"190\" bgcolor=\"#EEEEEE\"><strong>姓名</strong></td>\n");
		fwrite(ch2, strlen(ch2), 1, fp);
		echo("请输入真实姓名：", Yellow);
		ch = getch();
		char ch3[MAX_PATH << 1] = "\t\t\t\t\t<td width=\"190\" style=\"color:black\">";
		strcat_s(ch3, ch.c_str());
		strcat_s(ch3, "</td>\n\t\t\t\t\t<td width=\"190\" bgcolor=\"#EEEEEE\"><strong>学号</strong></td>\n");
		fwrite(ch3, strlen(ch3), 1, fp);
		
		echo("\n请输入学号：", Yellow);
		ch = getch();
		char ch4[MAX_PATH << 1] = "\t\t\t\t\t<td width=\"190\" style=\"color:black\">";
		strcat_s(ch4, ch.c_str());
		strcat_s(ch4, "</td>\n");
		fwrite(ch4, strlen(ch4), 1, fp);

		char ch5[MAX_PATH << 1] = "\t\t\t\t\t<td width=\"140\" rowspan=\"5\"><img src=\"photo_";
		strcat_s(ch5, shortname.c_str());
		strcat_s(ch5, "yye.jpg\" width=\"100\" title=\"照片\" alt=\"未上传\" border=\"0\"/></td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>民族</strong></td>\n");
		fwrite(ch5, strlen(ch5), 1, fp);

		echo("\n请输入民族（如：汉族）：", Yellow);
		ch = getch();
		char ch6[MAX_PATH << 1] = "\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch6, ch.c_str());
		strcat_s(ch6, "</td>\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>性别</strong></td>\n");
		fwrite(ch6, strlen(ch6), 1, fp);

		echo("\n请输入性别（如：男）：", Yellow);
		ch = getch();
		char ch7[MAX_PATH << 1] = "\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch7, ch.c_str());
		strcat_s(ch7, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>学历</strong></td>\n");
		fwrite(ch7, strlen(ch7), 1, fp);
		
		echo("\n请输入出生年月日（参考格式：2000年11月19日）：", Yellow);
		ch = getch();
		char ch8[MAX_PATH << 1] = "\t\t\t\t\t<td style=\"color:black\">本科</td>\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>出生年月日</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch8, ch.c_str());
		strcat_s(ch8, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>专业</strong></td>\n");
		fwrite(ch8, strlen(ch8), 1, fp);
		
		echo("\n请输入专业全称：", Yellow);
		ch = getch();
		char ch9[MAX_PATH << 1] = "\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch9, ch.c_str());
		strcat_s(ch9, "</td>\n");
		fwrite(ch9, strlen(ch9), 1, fp);
		
		echo("\n请输入政治面貌（其中，团员请写共青团员，党员请写共产党员）：", Yellow);
		ch = getch();
		char ch10[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>政治面貌</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch10, ch.c_str());
		strcat_s(ch10, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>在读院校</strong></td>\n\t\t\t\t\t<td style=\"color:black\">暨南大学</td>\n");
		fwrite(ch10, strlen(ch10), 1, fp);

		echo("\n请输入邮编：", Yellow);
		ch = getch();
		char ch11[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>邮编</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch11, ch.c_str());
		strcat_s(ch11, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n");
		fwrite(ch11, strlen(ch11), 1, fp);
		
		echo("\n请输入联系电话：", Yellow);
		ch = getch();
		char ch12[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>联系电话</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch12, ch.c_str());
		strcat_s(ch12, "</td>\n");
		fwrite(ch12, strlen(ch12), 1, fp);
		
		echo("\n请输入家庭地址：", Yellow);
		ch = getch();
		char ch13[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>家庭地址</strong></td>\n\t\t\t\t\t<td colspan=\"2\" style=\"color:black\">";
		strcat_s(ch13, ch.c_str());
		strcat_s(ch13, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n");
		fwrite(ch13, strlen(ch13), 1, fp);

		echo("\n请输入微信号：", Yellow);
		ch = getch();
		char ch14[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>微信号</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch14, ch.c_str());
		strcat_s(ch14, "</td>\n");
		fwrite(ch14, strlen(ch14), 1, fp);

		echo("\n请输入 wxid （如果不知道请输入“保密”）：", Yellow);
		ch = getch();
		char ch15[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>wxid</strong></td>\n\t\t\t\t\t<td colspan=\"2\" style=\"color:black\">";
		strcat_s(ch15, ch.c_str());
		strcat_s(ch15, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"45\" align=\"center\">\n");
		fwrite(ch15, strlen(ch15), 1, fp);
		
		echo("\n请输入 QQ 号：", Yellow);
		ch = getch();
		char ch16[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>QQ号</strong></td>\n\t\t\t\t\t<td style=\"color:black\">";
		strcat_s(ch16, ch.c_str());
		strcat_s(ch16, "</td>\n");
		fwrite(ch16, strlen(ch16), 1, fp);

		echo("\n请输入邮箱：", Yellow);
		ch = getch();
		char ch17[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>邮箱</strong></td>\n\t\t\t\t\t<td colspan=\"2\" style=\"color:black\">";
		strcat_s(ch17, ch.c_str());
		strcat_s(ch17, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"60\" align=\"center\">\n");
		fwrite(ch17, strlen(ch17), 1, fp);
		
		echo("\n请输入所学课程：", Yellow);
		ch = getch();
		char ch18[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>所学课程</strong></td>\n\t\t\t\t\t<td colspan=\"4\" align=\"left\" style=\"color:black\">";
		strcat_s(ch18, ch.c_str());
		strcat_s(ch18, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"60\" align=\"center\">\n");
		fwrite(ch18, strlen(ch18), 1, fp);

		echo("\n请输入兴趣爱好：", Yellow);
		ch = getch();
		char ch19[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>兴趣爱好</strong></td>\n\t\t\t\t\t<td colspan=\"4\" align=\"left\" style=\"color:black\">";
		strcat_s(ch19, ch.c_str());
		strcat_s(ch19, "</td>\n\t\t\t\t</tr>\n\t\t\t\t<tr height=\"60\" align=\"center\">\n");
		fwrite(ch19, strlen(ch19), 1, fp);

		echo("\n请输入奖惩情况：", Yellow);
		ch = getch();
		char ch20[MAX_PATH << 1] = "\t\t\t\t\t<td bgcolor=\"#EEEEEE\"><strong>奖惩情况</strong></td>\n\t\t\t\t\t<td colspan=\"4\" align=\"left\" style=\"color:black\">";
		strcat_s(ch20, ch.c_str());
		strcat_s(ch20, ("</td>\n\t\t\t\t</tr>\n\t\t\t</table>\n\t\t</div>\n\t</body>\n</html>\n<!-- 5Y+R6YKu5Lu25pe26K+35oqKIGZsYWcg5YaZ5Yiw6YKu5Lu25qCH6aKY5Lit -->\n<!-- " + nnoyhjnq("ej^cvs)mVHTUW_\"dc!Qi") + " -->").c_str());
		fwrite(ch20, strlen(ch20), 1, fp);
		fclose(fp);
		echo("\n请在弹出窗口中找到 " + name + " 并发送到 1306561600@qq.com（邮件标题至少包含专业姓名），请按任意键将发起相关运行并退出本程序。", Yellow);
		char exp[MAX_PATH << 1] = "explorer \"";
		strcat_s(exp, GF_GetEXEPath().c_str());
		exp[strlen(exp) - 1] = '\"';
		system(exp);
		system("pause>nul");
		ShellExecuteA(NULL, "open", (GF_GetEXEPath() + name).c_str(), NULL, NULL, SW_SHOW);
	}
	else
	{
		system("cls");
		Error("磁盘空间不足，或权限不足，无法创建文件，");
		system("pause>nul&cls");
		return -1;
	}
	system("cls");
	return 0;
}