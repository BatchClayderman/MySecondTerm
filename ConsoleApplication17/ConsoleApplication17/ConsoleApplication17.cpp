#include <iostream>
#include <Windows.h>
#define MAX_Range 500//随机数的最大长度
#define MAX_Size 1000//生成InputBox的最大字符数
#define Max_Length 100000//无穷
using namespace std;
HHOOK hHook;

LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam)//启动菜单
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("查看简介"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("动身前往"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("离开校园"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

WCHAR* CharToLpcwstr(char* strings)//转换字符
{
	int ASize = MultiByteToWideChar(CP_ACP, 0, strings, -1, NULL, 0);
	WCHAR* PwszUnicode = (wchar_t*)malloc(ASize * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, strings, -1, PwszUnicode, ASize);
	return PwszUnicode;
}

void FullScreen()//全屏显示
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int cy = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);//获取窗口信息
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);//禁止窗口被关
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SIZEBOX & ~WS_SYSMENU);//禁用菜单
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
	return;
}

int InputBox(char* _0)//文本输入框
{
	int i, j;
	char cmd[5 * MAX_Size] = { 0 }, runvbs[10 * MAX_Size] = "(if exist \"";
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
			fwrite("x = inputbox(\"请输入选择一个地点（1 - 13）：\",\"暨南大学欢迎您！\",\"1\")\nIf not x <> false Then\nx = 13\nEnd if\nOn Error Resume Next\nx = int(x)\nIf err.number <> 0 Then\nx = 0\nEnd if\nSet fso = CreateObject(\"Scripting.FileSystemObject\")\nSet f = fso.CreateTextFile(\"", 257, 1, fp);
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

typedef struct graph//图
{
	int cost[14][14] = { Max_Length };//顶点表
	int n = 13;//结点数
	int place = 1;//所处位置
	const char PlaceN[13][20] = { "南门（入校）","实验楼", "镜湖","湖景餐厅", "图书馆","教学楼","食堂","宿舍区","膳北小馆","清真食堂","升旗广场","体育馆", "东门（离校）" };
	const char introduction[13][150] = {
		"暨大番禺校区的南门是一座拱门，犹如一扇开启神秘世界的大门，进入暨大，就有了不一样的世界。衷心欢迎您的到来，来自世界各地的朋友们！",
		"实验楼是梦想的起源地，向导最喜欢来这了，唯有多实践，方能出真知。Windows Hook、Python Tensorflow，无不起源于此。",
		"镜湖，一个充满了浪漫主义色彩的灵湖，平静时如其名，灵动时闪耀出阳光在水面上流动的瑰丽之景，爱镜湖，爱湖畔上的另一半。",
		"湖景餐厅，故名思意，位于湖畔，几乎每所中国大学都有湖景餐厅，而之于暨大的湖景餐厅，那可是具有独树一帜的景色。当夜幕降临，星光之下，别有一番风味。",
		"图书馆典藏云集，阵阵墨香是那知识殿堂的华灯，文字跳跃是那真挚情感的寄托。“书中自有黄金屋”，在图书馆，一同感悟书籍带来的恢弘。",
		"大学校园，不但充满了鸟语花香，绿树成荫，而且错落有致的教学楼更是平添了暨大的风土人情。",
		"暨南大学番禺校区的食堂可谓是全国同类食堂中最好的，没有之一，不信？赶紧去试试吧！",
		"还记得初中的政治书上说，“学校是我们的第二个家”，在这里，宿舍区或许就是成就蓝色温馨的精神居所吧！",
		"膳北小馆量大，口味偏北方，是不少非本地生的选择。曾与兄弟于此相聚畅饮，共述“觥筹交错”的手足情谊。",
		"清真食堂，这个食堂在本部也有哦！就在一楼食堂的旁边，面对建阳宿舍。清真食堂是个清淡而不乏味的食堂，较能予人一种家的感觉。",
		"透过稀疏的树隙，从远方望去，隐隐约约地能看到五星红旗随风飞扬的瑰丽场景，升旗之时，庄严、肃静，共述祖国好。",
		"雄伟的体育馆大气蓬勃，是个充满雄性荷尔蒙的地方，是个挥洒汗水的地方，亦是个释放过盛青春活力的地方……",
		"我们的校园美不？还想再来一次吧！随时欢迎哦！许你一个美好的明天，愿世间的每个角落都洒满璀璨的星光。",
	};
}graph;

void randdistance(graph& G)//生成随机长度
{
	for (int i = 0; i < G.n + 1; ++i)
		for (int j = 0; j < G.n + 1; ++j)
			G.cost[i][j] = Max_Length;
	G.cost[1][3] = G.cost[3][1] = rand() % MAX_Range;
	G.cost[1][7] = G.cost[7][1] = rand() % MAX_Range;
	G.cost[2][6] = G.cost[6][2] = rand() % MAX_Range;
	G.cost[2][7] = G.cost[7][2] = rand() % MAX_Range;
	G.cost[3][5] = G.cost[5][3] = rand() % MAX_Range;
	G.cost[3][7] = G.cost[7][3] = rand() % MAX_Range;
	G.cost[4][6] = G.cost[6][4] = rand() % MAX_Range;
	G.cost[4][13] = G.cost[13][4] = rand() % MAX_Range;
	G.cost[6][9] = G.cost[9][6] = rand() % MAX_Range;
	G.cost[6][10] = G.cost[10][6] = rand() % MAX_Range;
	G.cost[6][12] = G.cost[12][6] = rand() % MAX_Range;
	G.cost[8][9] = G.cost[9][8] = rand() % MAX_Range;
	G.cost[8][12] = G.cost[12][8] = rand() % MAX_Range;
	G.cost[9][10] = G.cost[10][9] = rand() % MAX_Range;
	G.cost[9][11] = G.cost[11][9] = rand() % MAX_Range;
	return;
}

void ShowAll(graph G)//打印景点
{
	cout << "/***** 暨南大学番禺校区 *****/" << endl;
	for (int i = 0; i < 13; ++i)
		cout << "\t" << i + 1 << " = " << G.PlaceN[i] << endl;
	cout << endl << "当前位置：" << G.PlaceN[G.place - 1] << endl << endl << endl;
	return;
}

void introduce(graph G, char* _0)//介绍
{
	int a;
	ShowAll(G);
	do
	{
		a = InputBox(_0);
	} while (a < 1 || a > 13);
	cout << G.PlaceN[a - 1] << "简介：" << endl << G.introduction[a - 1] << endl << endl;
	int i, v, w, j, min, top[14] = { 0 }, path[14][14], eventual[14] = { 0 }, D[14];
	for (i = 1; i < G.n + 1; ++i)
		for (j = 1; j < G.n + 1; ++j)
			path[i][j] = 0;
	for (v = 1; v < G.n + 1; ++v)
	{
		D[v] = G.cost[a][v];
		if (D[v] < Max_Length)
		{
			path[v][(++(top[v]))] = a;
			path[v][(++(top[v]))] = v;
		}
	}
	D[a] = 0;
	eventual[a] = 1;
	for (i = 2; i < G.n + 1; ++i)
	{
		min = Max_Length;
		for (w = 1; w < G.n + 1; ++w)
			if ((eventual[w] == 0) && (D[w] < min))
			{
				v = w;
				min = D[w];
			}
		eventual[v] = 1;
		for (w = 1; w < G.n + 1; ++w)
			if ((eventual[w] == 0) && (min + G.cost[v][w] < D[w]))
			{
				D[w] = min + G.cost[v][w];
				for (j = 1; j < G.n + 1; ++j)
					path[w][j] = path[v][j];
				top[w] = top[v] + 1;
				path[w][(top[w])] = w;
			}
	}
	for (w = 1; w < G.n + 1; w++)
		if (w != a)
		{
			cout << "该地达到" << G.PlaceN[w - 1] << "的最短路径长度为 " << D[w] << " 米，具体路线如下：" << endl << a;
			for (i = 2; path[w][i] != 0; ++i)
				cout << "->" << path[w][i];
			cout << endl;
		}
	cout << endl << endl << endl;
	return;
}

void shortestdistance(graph& G, char* _0)//最短路径
{
	ShowAll(G);
	int i, v, w, j, min, top[14] = { 0 }, path[14][14], eventual[14] = { 0 }, D[14];
	for (i = 1; i < G.n + 1; ++i)
		for (j = 1; j < G.n + 1; ++j)
			path[i][j] = 0;
	for (v = 1; v < G.n + 1; ++v)
	{
		D[v] = G.cost[G.place][v];
		if (D[v] < Max_Length)
		{
			path[v][(++(top[v]))] = G.place;
			path[v][(++(top[v]))] = v;
		}
	}
	D[G.place] = 0;
	eventual[G.place] = 1;
	for (i = 2; i < G.n + 1; ++i)
	{
		min = Max_Length;
		for (w = 1; w < G.n + 1; ++w)
			if ((eventual[w] == 0) && (D[w] < min))
			{
				v = w;
				min = D[w];
			}
		eventual[v] = 1;
		for (w = 1; w < G.n + 1; ++w)
			if ((eventual[w] == 0) && (min + G.cost[v][w] < D[w]))
			{
				D[w] = min + G.cost[v][w];
				for (j = 1; j < G.n + 1; ++j)
					path[w][j] = path[v][j];
				top[w] = top[v] + 1;
				path[w][(top[w])] = w;
			}
	}
	do
	{
		w = InputBox(_0);
	} while (w <= ERROR || w > 13);
	if (w == G.place)
	{
		char msg[100] = "您已位于目的景点：";
		strcat_s(msg, G.PlaceN[G.place - 1]);
		strcat_s(msg, "\n无需动身，点击“确定”返回主菜单。");
		MessageBox(NULL, CharToLpcwstr(msg), TEXT("温馨提示"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
		return;
	}
	cout << endl << G.introduction[w - 1] << endl << "经计算，最短路径长度为 " << D[w] << " 米，具体路线如下：" << endl << G.place;
	for (i = 2; path[w][i] != 0; ++i)
		cout << "->" << path[w][i];
	G.place = w;
	cout << endl << endl << endl << endl;
	return;
}

int main(int argc, char* argv[])
{
	system("chcp 936&title 状态输出&color e&mode con: cols=50 lines=50&cls");
	graph G;
	randdistance(G);
	FullScreen();
	char msg[100] = { 0 }, tmp[20];
	while (true)
	{
		for (int i = 0; i < 100; ++i)
			msg[i] = 0;
		for (int i = 0; i < 20; ++i)
			tmp[i] = 0;
		strcat_s(msg, "当前所处景点：");
		strcat_s(tmp, G.PlaceN[G.place - 1]);
		strcat_s(msg, tmp);
		strcat_s(msg, "\n您希望本向导为您做些什么？\n请选择一项以继续：");
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
		switch (hHook ? MessageBox(NULL, CharToLpcwstr(msg), TEXT("暨南大学欢迎您！"), MB_YESNOCANCEL | MB_ICONINFORMATION | MB_TOPMOST | MB_DEFBUTTON2) : MessageBox(NULL, TEXT("仅查看介绍吗？\n是 = 查看简介\n否 = 动身前往\n取消 = 离开校园\n\n您希望本向导为您做些什么？请选择一项以继续："), TEXT("暨南大学欢迎您！"), MB_YESNOCANCEL | MB_ICONINFORMATION | MB_TOPMOST | MB_DEFBUTTON2))
		{
		case 6:
			introduce(G, argv[0]);
			break;
		case 7:
			shortestdistance(G, argv[0]);
			if (G.place == 13)
			{
				MessageBox(NULL, TEXT("欢迎再来呀！期待您的下次光临！"), TEXT("暨南大学番禺校区"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
				return 0;
			}
			break;
		case 2:
			if (MessageBox(NULL, TEXT("校园那么美，您确定要离开吗？"), TEXT("流连忘返之际，我们不说再见"), MB_OKCANCEL | MB_ICONQUESTION | MB_TOPMOST) == 1)
				return 0;
		default:
			continue;
		}
	}
	return 9009;
}