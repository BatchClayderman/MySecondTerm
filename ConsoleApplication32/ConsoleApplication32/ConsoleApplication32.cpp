#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <time.h>//时间库，用于计时
#define MAX_Height 800//最大高度
#define MAX_Width 800//最大宽度
using namespace std;
int sWidth = 40, sHeight = 40;//显示区域的大小
int width = 45, height = 45;//迷宫的实际大小，建议为奇数，必须大于10
int LV = 10;//出口所在的位置范围
int walk_count = 1;//走过计数
int operate_count = 1;//操作计数
int Boom_count = 5;//炸弹数
int boom_count = Boom_count;//炸弹数
const char wall = 1;
const char path = 0;
const char target = 2;
char color_code[3] = "e";//颜色
char map[MAX_Height][MAX_Width];//地图
bool fog[MAX_Height][MAX_Width];//迷雾
bool walk[MAX_Height][MAX_Width];//走过之地
bool difficult = true;//迷雾模式
extern HHOOK hHook;
extern LRESULT __stdcall CBTHookProc1(long nCode, WPARAM wParam, LPARAM lParam);
extern LRESULT __stdcall CBTHookProc2(long nCode, WPARAM wParam, LPARAM lParam);
extern LRESULT __stdcall CBTHookProc3(long nCode, WPARAM wParam, LPARAM lParam);
HHOOK hHook;
time_t start_time, end_time;//声明计时变量
int elapsed_time = 0;

vector<pair<pair<int, int>, int> > walls;//待凿墙列表
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

/* 四周一步 */
int xx[] = { 0, 0, -1, 1 };
int yy[] = { -1, 1, 0, 0 };

/* 四周两步 */
int x2[] = { 0, 0, -2, 2 };
int y2[] = { -2, 2, 0, 0 };

/* 玩家坐标 */
int playerx;
int playery;
int SPX;
int SPY;
const int margin = 3;

LRESULT __stdcall CBTHookProc1(long nCode, WPARAM wParam, LPARAM lParam)//启动菜单
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("进入游戏"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("设置"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("退出游戏"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc2(long nCode, WPARAM wParam, LPARAM lParam)//投降菜单
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("我投降我投降"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("我才不投降"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("退出游戏"));
		UnhookWindowsHookEx(hHook);
	}
	return 0;
}

LRESULT __stdcall CBTHookProc3(long nCode, WPARAM wParam, LPARAM lParam)//设置
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("体验设置"));
		SetDlgItemText((HWND)wParam, IDNO, TEXT("难度设置"));
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("取消设置"));
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

void full_screen()//全屏显示
{
	char modeline[50] = "mode con: cols=", tmp[10] = { 0 };
	_itoa_s(sWidth + 1, tmp, 10);
	strcat_s(modeline, tmp);
	_itoa_s(sHeight + 1, tmp, 10);
	strcat_s(modeline, " lines=");
	strcat_s(modeline, tmp);
	system(modeline);
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
	int cy = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);//获取窗口信息
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);//禁止窗口被关
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SIZEBOX & ~WS_SYSMENU);//禁用菜单
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

void gotoxy(int x, int y)//移动光标到xy位置
{
	COORD coord = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setAllWall()//设置全地图为墙
{
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			map[y][x] = wall;
}

void Boom(int x, int y)//轰炸四周
{
	if (boom_count <= 0)//判断是否拥有炸弹
	{
		MessageBox(NULL, TEXT("很抱歉，您已经没有炸弹了。"), TEXT("迷宫—炸弹"), MB_OK | MB_ICONERROR | MB_TOPMOST);
		return;
	}
	if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)//判断是否处于迷宫边缘
	{
		MessageBox(NULL, TEXT("您处于迷宫边缘，不能炸毁。"), TEXT("迷宫—炸弹"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
		return;
	}
	int path_count = 0;
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (map[y + i][x + j] == target)//判断星星是否在附近
			{
				MessageBox(NULL, TEXT("您附近含有星星，不能炸毁。"), TEXT("迷宫—炸弹"), MB_OK | MB_ICONWARNING | MB_TOPMOST);
				return;
			}
			if (map[y + i][x + j] == path)//判断炸弹是否有效
				path_count++;
		}
	if (path_count == 9)
	{
		MessageBox(NULL, TEXT("您附近均为通路，无需炸毁。"), TEXT("迷宫—炸弹"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
		return;
	}
	char msg[100] = "您还剩 ", tmp[10] = { 0 };
	_itoa_s(boom_count, tmp, 10);
	strcat_s(msg, tmp);
	strcat_s(msg, " 个炸弹，确定要炸毁附近的围墙？");
	if (MessageBox(NULL, CharToLpcwstr(msg), TEXT("迷宫—炸弹"), MB_OKCANCEL | MB_ICONWARNING | MB_TOPMOST) == 2)
		return;
	map[y - 1][x - 1] = map[y - 1][x] = map[y - 1][x + 1] = map[y][x - 1] = map[y][x + 1] = map[y + 1][x - 1] = map[y + 1][x] = map[y + 1][x + 1] = path;
	boom_count--;
	operate_count++;
	return;
}

bool isOutBounds(int x, int y)//判断是否越界
{
	return (x < 0 || x >= width || y < 0 || y >= height);
}

void explore(int x, int y)//向四周探索
{
	for (int i = 0; i < 4; ++i)//遍历四个方向
		for (int x1 = x, y1 = y; !isOutBounds(x1, y1) && map[y1][x1] == path; x1 += xx[i], y1 += yy[i])//顺着一条路走
			for (int fy = y1 - 1; fy <= y1 + 1; ++fy)//每走一个格子检查四周是否为通路
				for (int fx = x1 - 1; fx <= x1 + 1; ++fx)
					if (!isOutBounds(fx, fy) && fog[fy][fx])
						fog[fy][fx] = false;
}

void pushAroundWall(int x, int y)//将坐标处的墙添加到待通墙中
{
	for (int i = 0; i < 4; ++i)//遍历四个方向
	{
		int tx = x + xx[i];
		int ty = y + yy[i];
		if (isOutBounds(tx, ty))
			continue;
		int wx = x + x2[i];
		int wy = y + y2[i];
		if (isOutBounds(wx, wy))
			continue;
		if (map[ty][tx] == wall)//只要是墙就加入列表
			walls.push_back(pair<pair<int, int>, int>(pair<int, int>(tx, ty), i));
	}
}

void showMap()//展示地图
{
	int dx = sWidth / 2 - playerx;
	int dy = sHeight / 2 - playery;
	gotoxy(0, 0);//移动光标到最开始的位置
	for (int sy = 0; sy < sHeight; ++sy)//遍历整个地图
	{
		for (int sx = 0; sx < sWidth; ++sx)
		{
			int x = sx - dx;
			int y = sy - dy;
			/*
			//const char* Symbol[6] = { "◎", "☆", "□", "▽", "●", "■" };
			字符说明：
				玩家—◎
				胜利—☆
				通路—□
				已走的路—▽
				墙或雾—●
				迷宫外—■
			*/
			if (isOutBounds(x, y))
			{
				printf("■");
				continue;
			}
			if (x == playerx && y == playery)
			{
				printf("◎");
				continue;
			}
			if (fog[y][x])
			{
				printf("●");
				continue;
			}
			if ((!walk[y][x]) || (x == 1 && y == 1))
			{
				printf("▽");
				continue;
			}
			if (map[y][x] == path)
			{
				printf("□");
				continue;
			}
			if (map[y][x] == target)
			{
				printf("☆");
				continue;
			}
			printf("●");
			continue;
			int d = 0;
			for (int i = 0; i < 4; ++i)
				if (!isOutBounds(x + xx[i], y + yy[i]) && map[y + yy[i]][x + xx[i]] == wall)
					d |= 1 << i;
			const int up = 1;
			const int down = 2;
			const int left = 4;
			const int right = 8;
			char ch = 0;
			switch (d)
			{
			case 0:
				ch = '&';
				break;
			case up:
			case down:
				ch = '|';
				break;
			case left:
			case right:
				ch = '-';
				break;
			default:
				ch = '+';
			}
			putchar(ch);
		}
		cout << endl;
	}
}

void sleep(int n)//随机延迟
{
	for (int i = 0; i < n * n * n * n; ++i);
}

void refresh()//刷新地图
{
	gotoxy(1, 1);
	showMap();
}

void generate(int cx, int cy)//生成地图算法，参数为起始点坐标
{
	setAllWall();//首先将地图全部设置为墙
	for (int i = 0; i < width; ++i)//填满迷雾，清空已经走过的路径
		for (int j = 0; j < height; ++j)
		{
			fog[i][j] = difficult;
			walk[i][j] = true;
		}
	playerx = cx;//设置玩家横坐标
	playery = cy;//设置玩家纵坐标
	pushAroundWall(cx, cy);//从起点开始，将四周的墙壁添加到待凿列表中
	map[cy][cx] = path;//把这个点变成路
	while (!walls.empty())//只要还有待凿的墙，就一直循环
	{
		int index = rand() % walls.size();// 随机找个待凿的墙
		int wx = walls[index].first.first;
		int wy = walls[index].first.second;
		int d = walls[index].second;
		if (map[wy + yy[d]][wx + xx[d]] == wall)//如果是墙则打穿，并将下一个点四周的墙壁加入待凿列表
		{
			map[wy][wx] = path;
			map[wy + yy[d]][wx + xx[d]] = path;
			pushAroundWall(wx + xx[d], wy + yy[d]);
		}
		walls.erase(walls.begin() + index);
	}
	map[height - rand() % LV - 2][width - rand() % LV - 2] = target;//随机星星地址
	explore(playerx, playery);//探路
}

void Setting1()//修改体验设置
{
	operate_count++;//操作数加1，如果不是游戏期间，操作数将在启动游戏时清零
	char commandline[10] = "color ", colorcode[3] = { 0 };
	strcpy_s(colorcode, color_code);
	bool flag = true;
	while (flag)
	{
		for (int i = strlen("color "); i < 10; ++i)
			commandline[i] = 0;
		system("cls");
		cout << "可供选择的颜色如下：" << endl;
		cout << "\t0 = 黑色\t8 = 灰色" << endl;
		cout << "\t1 = 蓝色\t9 = 淡蓝色" << endl;
		cout << "\t2 = 绿色\tA = 淡绿色" << endl;
		cout << "\t3 = 浅绿色\tB = 淡浅绿色" << endl;
		cout << "\t4 = 红色\tC = 淡红色" << endl;
		cout << "\t5 = 紫色\tD = 淡紫色" << endl;
		cout << "\t6 = 黄色\tE = 淡黄色" << endl;
		cout << "\t7 = 白色\tF = 亮白色" << endl;
		cout << endl << "请输入代号（如：FC 在亮白色上产生淡红色）：" << endl;
		rewind(stdin);
		scanf_s("%s", &colorcode, sizeof(colorcode));
		rewind(stdin);
		if (strlen(colorcode) == 1)
		{
			if ((colorcode[0] >= '0' && colorcode[0] <= '9') || (colorcode[0] >= 'A' && colorcode[0] <= 'F') || (colorcode[0] >= 'a' && colorcode[0] <= 'f'))
			{
				strcat_s(commandline, colorcode);
				system(commandline);
			}
			else
			{
				cout << '\a';
				continue;
			}
		}
		else if (strlen(colorcode) == 2)
		{
			if (((colorcode[0] >= '0' && colorcode[0] <= '9') || (colorcode[0] >= 'A' && colorcode[0] <= 'F') || (colorcode[0] >= 'a' && colorcode[0] <= 'f')) && ((colorcode[1] >= '0' && colorcode[1] <= '9') || (colorcode[1] >= 'A' && colorcode[1] <= 'F') || (colorcode[1] >= 'a' && colorcode[1] <= 'f')) && (colorcode[0] != colorcode[1]))
			{
				strcat_s(commandline, colorcode);
				system(commandline);
			}
			else
			{
				cout << '\a';
				continue;
			}
		}
		else
		{
			cout << '\a';
			continue;
		}
		switch (MessageBox(NULL, TEXT("颜色预览如图，是否保留？"), TEXT("迷宫—体验设置"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST))
		{
		case 6:
			strcpy_s(color_code, colorcode);
			system("cls");
			flag = false;
			break;
		case 7:
			for (int i = strlen("color "); i < 10; i++)
				commandline[i] = 0;
			strcat_s(commandline, color_code);
			system(commandline);
			system("cls");
			break;
		case 2:
			for (int i = strlen("color "); i < 10; i++)
				commandline[i] = 0;
			strcat_s(commandline, color_code);
			system(commandline);
			flag = false;
			break;
		default:
			continue;
		}
	}
	system("cls");
	cout << "请设置显示区域高度（15-50）：";
	rewind(stdin);
	while (scanf_s("%d", &sHeight) != 1 || sHeight < 15 || sHeight > 50)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	rewind(stdin);
	cout << "请设置显示区域宽度（15-80）：";
	rewind(stdin);
	while (scanf_s("%d", &sWidth) != 1 || sWidth < 15 || sWidth > 80)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	rewind(stdin);
	system("cls");
}

bool Setting2(bool flag)//难度设置
{
	if (flag && (MessageBox(NULL, TEXT("您正处于游戏期间，修改难度设置需要放弃当前迷宫以重新开始，是否继续修改？"), TEXT("迷宫—难度设置"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST) == 7))
		return false;
	system("cls");
	cout << "地图高度应为 15 - " << MAX_Height - 1 << " 之间的正整数，且建议为奇数。" << endl;
	cout << "地图宽度应为 15 - " << MAX_Width - 1 << " 之间的正整数，且建议为奇数。" << endl << endl;
	cout << "请输入地图高度：";
	rewind(stdin);
	while (scanf_s("%d", &height) != 1 || height < 15 || height >= MAX_Height)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	cout << "请输入地图宽度：";
	rewind(stdin);
	while (scanf_s("%d", &width) != 1 || width < 15 || width >= MAX_Width)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	cout << endl << "星星随机范围是指星星可能出现在棋盘中的右下区域的范围，" << "该范围应该为 5 - " << min(height, width) - 5 << "，" << "请输入星星随机范围：";
	while (scanf_s("%d", &LV) != 1 || LV < 5 || LV > min(height, width) - 5)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	cout << "请输入炸弹个数（3 - " << height * width << "）：";
	while (scanf_s("%d", &Boom_count) != 1 || Boom_count < 3 || Boom_count > height * width)
	{
		cout << "\a输入有误，请重新输入：";
		rewind(stdin);
	}
	difficult = (MessageBox(NULL, TEXT("是否开启迷雾模式？"), TEXT("迷宫—难度设置"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST) == 6);
	system("cls");
	return true;
}

bool Settings(bool flag)//修改设置
{
	int errorcontrol = 6;
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc3, NULL, GetCurrentThreadId());
	if (hHook)
		errorcontrol = (flag ? MessageBox(NULL, TEXT("注意：游戏期间修改体验设置，计时将会继续。\n请选择您希望修改的设置："), TEXT("迷宫—设置"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST) : MessageBox(NULL, TEXT("请选择您希望修改的设置："), TEXT("迷宫—设置"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST));
	else
		errorcontrol = (flag ? MessageBox(NULL, TEXT("注意：游戏期间修改体验设置，计时将会继续。\n\n是 = 修改体验设置\n否 = 修改难度设置\n取消 = 取消设置"), TEXT("迷宫—设置"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST) : MessageBox(NULL, TEXT("是 = 修改体验设置\n否 = 修改难度设置\n取消 = 取消设置"), TEXT("迷宫—设置"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST));
	system("cls");
	switch (errorcontrol)
	{
	case 6:
		Setting1();
		return false;
	case 7:
		return Setting2(flag);
	default:
		return false;
	}
}

bool playerMove(int dir)//玩家移动，参数是移动的方向，如果获胜则返回true
{
	if (dir < 0 || dir >= 4)
		return false;
	int tx = playerx + xx[dir], ty = playery + yy[dir];
	if (isOutBounds(tx, ty))
		return false;
	if (map[ty][tx] == wall)
		return false;
	if (map[ty][tx] == target)
	{
		time(&end_time);//计时结束
		elapsed_time = int(difftime(end_time, start_time));//计算运行耗时
		char messages[500] = "恭喜你，游戏胜利！\n\n耗时 ", time_tmp[10] = { 0 };
		if (elapsed_time < 60 && elapsed_time >= 0)//涉及秒
		{
			_itoa_s(elapsed_time, time_tmp, 10);
			strcat_s(messages, time_tmp);
			strcat_s(messages, " 秒\n使用炸弹 ");
		}
		else if (elapsed_time >= 60 && elapsed_time < 3600)//涉及分
		{
			_itoa_s(int(elapsed_time / 60), time_tmp, 10);
			strcat_s(messages, time_tmp);
			if (elapsed_time % 60 < 10)
				strcat_s(messages, " 分 0");
			else
				strcat_s(messages, " 分 ");
			_itoa_s(elapsed_time % 60, time_tmp, 10);
			strcat_s(messages, time_tmp);
			strcat_s(messages, " 秒\n使用炸弹 ");
		}
		else if (elapsed_time >= 3600 && elapsed_time < 86400)//涉及时
		{
			_itoa_s(int(elapsed_time / 3600), time_tmp, 10);
			strcat_s(messages, time_tmp);
			if (int(elapsed_time % 3600 / 60) < 10)
				strcat_s(messages, " 时 0");
			else
				strcat_s(messages, " 时 "); 
			_itoa_s(int(elapsed_time % 3600 / 60), time_tmp, 10);
			strcat_s(messages, time_tmp);
			if (elapsed_time % 60 < 10)
				strcat_s(messages, " 分 0");
			else
				strcat_s(messages, " 分 ");
			_itoa_s(elapsed_time % 60, time_tmp, 10);
			strcat_s(messages, time_tmp);
			strcat_s(messages, " 秒\n使用炸弹 ");
		}
		else
			strcat_s(messages, "数据异常\n使用炸弹");
		_itoa_s(Boom_count - boom_count, time_tmp, 10);
		strcat_s(messages, time_tmp);
		strcat_s(messages, " / ");
		_itoa_s(Boom_count, time_tmp, 10);
		strcat_s(messages, time_tmp);
		strcat_s(messages, " 个\n走过 / 操作 / 格数\n");
		_itoa_s(walk_count, time_tmp, 10);
		strcat_s(messages, time_tmp);
		strcat_s(messages, " / ");
		_itoa_s(operate_count, time_tmp, 10);
		strcat_s(messages, time_tmp);
		strcat_s(messages, " / ");
		_itoa_s(height * width, time_tmp, 10);
		strcat_s(messages, time_tmp);
		strcat_s(messages, "\n\n随机范围 ");
		_itoa_s(LV, time_tmp, 10);
		strcat_s(messages, time_tmp);
		difficult ? strcat_s(messages, "\n迷雾模式 开\n\n是否修改难度再来一局？\n点击“取消”可退出游戏。") : strcat_s(messages, "\n迷雾模式 关\n\n是否修改难度再来一局？\n点击“取消”可退出游戏。");
		switch (MessageBox(NULL, CharToLpcwstr(messages), TEXT("迷宫"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST | MB_DEFBUTTON2))
		{
		case 6:
			Setting2(false);
			return true;
		case 7:
			return true;
		case 2:
			exit(0);
		}
	}
	if (map[ty][tx] == path)//只有是通路的时候才能移动
	{
		playerx = tx, playery = ty;
		if (walk[ty][tx])
			walk_count++;
		walk[ty][tx] = false;
		operate_count++;
	}
	explore(playerx, playery);//移动完后再次探索迷雾
	return false;
}

bool updata()//更新
{
	char ch = _getch();
	/*
	按键说明：
		上下左右—wsad 或 ikjl
		帮助—h
		刷新—x
		设置—f
		开灯—m
		重来—r
		炸弹—b
		投降或退出—g
		强退—长按Ctrl+C
	*/
	switch (ch)
	{
	case 'W':
	case 'w':
	case 'I':
	case 'i':
		if (playerMove(up))//上
			return true;
		break;
	case 'S':
	case 's':
	case 'K':
	case 'k':
		if (playerMove(down))//下
			return true;
		break;
	case 'A':
	case 'a':
	case 'J':
	case 'j':
		if (playerMove(2))//左
			return true;
		break;
	case 'D':
	case 'd':
	case 'L':
	case 'l':
		if (playerMove(3))//右
			return true;
		break;
	case 'H'://帮助
	case 'h':
		MessageBox(NULL, TEXT("按键控制（不区分大小写）：\n   上下左右—wsad 或 ikjl\n   帮助—h     刷新—x     设置—f\n   开灯—m     重来—r     炸弹—b\n   投降或退出—g     强退—长按Ctrl+C\n\n字符说明：\n   玩家—◎     胜利—☆\n   通路—□     已走的路—▽\n   墙或雾—●     迷宫外—■\n\n点击“确定”以返回游戏。"), TEXT("迷宫—帮助"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
		break;
	case 'G'://投降
	case 'g':
		hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc2, NULL, GetCurrentThreadId());
		switch (MessageBox(NULL, TEXT("嘻嘻，真的要投降吗？"), TEXT("迷宫—投降或退出"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST | MB_DEFBUTTON2))
		{
		case 6:
			switch (MessageBox(NULL, TEXT("修改难度设置再来吗？"), TEXT("迷宫—投降"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST))
			{
			case 2:
				exit(-1);
			case 6:
				Setting2(false);
			default:
				return true;
			}
		case 2:
			exit(1);
		default:
			break;
		}
		break;
	case 'F'://设置
	case 'f':
		return Settings(true);
	case 'X'://刷新窗口
	case 'x':
		full_screen();
		break;
	case 'R'://新开一局
	case 'r':
		switch (MessageBox(NULL, TEXT("放弃当局并重来吗？"), TEXT("迷宫—重来"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_TOPMOST))
		{
		case 6:
			return true;
		case 2:
			exit(1);
		default:
			return false;
		}
	case 'M':
	case 'm':
		if (!difficult || MessageBox(NULL, TEXT("游戏太难了？确定要开灯吗？"), TEXT("迷宫—开灯"), MB_OKCANCEL | MB_ICONQUESTION | MB_TOPMOST) == 2)
			return false;
		for (int i = 0; i < width; ++i)//填满迷雾，清空已经走过的路径
			for (int j = 0; j < height; ++j)
				fog[i][j] = false;
		operate_count++;
		difficult = false;
		break;
	case 'B':
	case 'b':
		Boom(playerx, playery);
		break;
	default:
		return false;
	}
	return false;
}

int main()
{
	system("chcp 936&title 迷宫&color e&cls");//此处chcp 936很重要，在某些代码页默认为437的电脑上，迷宫将是乱码！！
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc1, NULL, GetCurrentThreadId());
	if (hHook)
	{
		switch (MessageBox(NULL, TEXT("按键控制（不区分大小写）：\n   上下左右—wsad 或 ikjl\n   帮助—h     刷新—x     设置—f\n   开灯—m     重来—r     炸弹—b\n   投降或退出—g     强退—长按Ctrl+C\n\n字符说明：\n   玩家—◎     胜利—☆\n   通路—□     已走的路—▽\n   墙或雾—●     迷宫外—■\n\n带上若干炸弹，移动玩家找到星星即为胜利！"), TEXT("迷宫游戏说明"), MB_YESNOCANCEL | MB_ICONINFORMATION | MB_TOPMOST))
		{
		case 7:
			Settings(false);
			break;
		case 2:
			exit(0);
		default:
			break;
		}
	}
	full_screen();
main:
	srand((unsigned int)time(0));//初始化随机数种子
	srand((unsigned)time(0));//初始化时间种子
	time(&start_time);//开始计时
	walk_count = 1;//初始化走过格数
	operate_count = 1;//初始化操作计数
	boom_count = Boom_count;//初始化炸弹数
	do
	{
		generate(1, 1);//生成地图
		while (true)//游戏循环直到获胜
		{
			showMap();//输出地图
			if (updata())//更新
				goto main;
		}
	} while (_getch() != 0);
	return 0;
}