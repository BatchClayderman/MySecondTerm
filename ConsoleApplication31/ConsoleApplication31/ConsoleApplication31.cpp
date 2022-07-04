#include <iostream>
#define MaxInt 32767//表示极大值
#define MVNum 63//最大顶点数
#define OK 1
#define Range 10000//最大路径长度
using namespace std;
typedef char VerTexType;//假设顶点的数据类型为字符型
typedef int ArcType;//假设边的权值为整型
typedef int Status;

typedef struct
{
	VerTexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	Status vexnum, arcnum;//图的当前点数和边数
}AMGraph;

Status LocateVex(AMGraph G, int v)//查找顶点V在图中的位置
{
	for (int i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)//图G存在，v和G中顶点有相同特征
			return i;//返回该顶点在图的位置
	return -1;
}

Status CreateUDN(AMGraph& G)//采用邻接矩阵创建双向有向网
{
	int i, j, k, w[10] = { rand() % Range };
	char v1[10] = { 'A','A','A','B','B','C','C','D','E','F' }, v2[10] = { 'B','C','D','C','E','D','F','G','F','G' };
	for (int i = 0; i < 10; ++i)
	{
		w[i] = rand() % Range;
		cout << i << '\t' << w[i] << endl;
	}
	G.vexnum = 7;//总顶点数
	G.arcnum = 10;//总边数
	for (i = 0; i < G.vexnum; ++i)//依次输入点的信息
		G.vexs[i] = 65 + i;
	for (i = 0; i < G.vexnum; ++i)//初始化邻接矩阵，边的权值均置为极大值MaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;//构建邻接矩阵
	for (k = 0; k < G.arcnum; ++k)//输入一条边依附的顶点及权值
	{
		i = LocateVex(G, v1[k]);//确定v1和v2在G中的位置，即顶点数组的下标
		j = LocateVex(G, v2[k]);
		G.arcs[j][i] = G.arcs[i][j] = w[k];//边<v1，v2>的权值为w
	}
	return OK;
}

void ShortestPath_DIJ(AMGraph G, int v0)//用迪杰斯特拉算法求有向网G的v0顶点到其余顶点的最短路径
{
	int i, t, j, w, n, v, min, Path[7] = { 0 }, S[7] = { 0 }, D[7] = { 0 }, a[6] = { 0 };
	n = G.vexnum; j = 0;//n为G中顶点的个数
	for (v = 0; v < n; ++v)//n个顶点依次初始化
	{
		S[v] = false;//S初始为空集
		D[v] = G.arcs[v0][v];//将v0到各个终点的最短路径长度初始化为弧上的权值
		if (D[v] < MaxInt)
			Path[v] = 0;//如果v0和v之间有弧，则将v的前驱为v0
		else
			Path[v] = -1;//如果v0和v之间无弧，则将v的前驱为-1
	}
	S[v0] = true;//将v0加入S  
	D[v0] = 0;//源点到源点的距离为0 

	/* 初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集 */
	for (i = 1; i < n; ++i)//对其余n-1个顶点，依次进行计算
	{
		min = MaxInt;
		for (w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{
				v = w;//选择一条当前的最短路径，终点为v
				min = D[w];
			}
		S[v] = true;//将v加入S
		for (w = 0; w < n; ++w)//更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//更新D[w]
				Path[w] = v;//更改w的前驱为v
			}
	}
	
	/* 输出最短路径以及距离，并按照距离从大到小的顺序排序 */
	for (i = 0; i < n; i++)
		if (v0 != i && D[i] != MaxInt)//排除它本身
				a[j++] = i;//将具有权值的下标存在数组a	
	for (i = 0; i < j; i++)
		for (int u = i; u < j; u++)
			if (D[a[i]] < D[a[u]])//将权值大的下标放在前面
			{
				t = a[i];
				a[i] = a[u];
				a[u] = t;
			}
	cout << endl << endl << "按照距离从大到小输出如下：" << endl << endl;
	cout << "路径长度\t路径" << endl;
	for (i = 0; i < j; ++i)
	{
		printf(" %5d", D[a[i]]);
		printf("     %5c", G.vexs[a[i]]);
		v = Path[a[i]];//将Path所对应的位置赋给v
		while (v != 0)//判断是否有中继点
		{
			if (v >= 0 && v < MVNum)
			{
				cout << "<-" << G.vexs[v];
				v = Path[v];//更新v
			}
			else
			{
				system("cls");
				cout << "\a系统发生异常，请按任意键退出。" << endl;
				system("pause>nul&cls");
				exit(-1);
			}
		}
		cout << "<-" << G.vexs[v0] << endl;
	}
}

void ShortestPath_Floyd(AMGraph G, int v0, int v1)//用弗洛伊德算法求有向网G中的各顶点i和j之间的最短路径
{
	int i, j, k, v, D[7][7] = { 0 }, Path[7][7] = { 0 };
	for (i = 0; i < G.vexnum; ++i)//各对结点之间初始已知路径及距离
		for (j = 0; j < G.vexnum; ++j)
		{
			D[i][j] = G.arcs[i][j];
			if (D[i][j] < MaxInt && i != j)//如果i和j之间有弧，则将j的前驱置为1
				Path[i][j] = i;
			else//如果i和j之间无弧，则将j的前驱置为-1
				Path[i][j] = -1;
		}
	for (k = 0; k < G.vexnum; ++k)
		for (i = 0; i < G.vexnum; ++i)
			for (j = 0; j < G.vexnum; ++j)
				if (D[i][k] + D[k][j] < D[i][j])//从i经k到j的一条路径更短
				{
					D[i][j] = D[i][k] + D[k][j];//更新D[i][j]
					Path[i][j] = Path[k][j];//更改j的前驱为k
				}
	cout << endl << "起点城市：" << G.vexs[v0] << "\t终点城市：" << G.vexs[v1] << endl;
	if (Path[v0][v1] == -1)
		cout << "\a错误：无法到达该城市。" << endl;
	else
	{
		cout << "两地的距离为：" << D[v0][v1] << endl;
		cout << "路线：" << G.vexs[v1];
		v = Path[v0][v1];//将Path的位置赋给v
		while (v != v0)//判断是否有中继点
		{
			cout << "<-" << G.vexs[v];
			v = Path[v0][v];//更新v
		}
		cout << "<-" << G.vexs[v0] << endl;
	}
	if (v0 == v1)
		cout << "注意：出发地与目的地相同" << endl;
}

Status menu()//菜单实现
{
	int n;
	system("cls");
	cout << "/*************** 欢迎使用交通咨询系统 ***************/" << endl;
	cout << "\t1 = 某地到其他地方的最短路径和距离" << endl;
	cout << "\t2 = 两地之间的最短路径和距离" << endl;
	cout << "\t3 = 重新随机路径数据" << endl;
	cout << "\t0 = 退出交通咨询系统" << endl << endl;
	cout << "请选择功能：";
	rewind(stdin);
	if (scanf_s("%d", &n) != 1 || n < 0 || n > 3)
	{
		cout << '\a';
		return menu();
	}
	cout << endl;
	rewind(stdin);
	return n;
}

bool checkch(char& ch)//判断字符是否有效
{
	bool legal = false;
	char alphas1[8] = "ABCDEFG", alphas2[8] = "abcdefg";//存储有效字母
	for (unsigned int i = 0; i < strlen(alphas1); i++)
		if (ch == alphas1[i])
		{
			legal = true;
			break;
		}
	for (unsigned int i = 0; i < strlen(alphas2); i++)
		if (ch == alphas2[i])
		{
			ch -= 32;
			legal = true;
			break;
		}
	if (!legal)
		cout << "\a无效的城市—“" << ch << "”。" << endl;
	return legal;
}

int main()
{
	system("chcp 936&title 交通咨询系统&color e&cls");
	AMGraph G;
	int v0, v1;
	char ch;
	bool flag = true;
	CreateUDN(G);//构建邻接矩阵
	cout << endl << endl << "随机数据生成如上，请按任意键进入程序。" << endl;
	system("pause>nul");
	while (flag)
	{
		rewind(stdin);
		switch (menu())
		{
		case 1:
			cout << "请输入需要查找的城市（ABCDEFG）：";
			cin >> ch;//输入地点，将位置存放在V0中
			if (!checkch(ch))
				continue;
			v0 = ch - 65;
			ShortestPath_DIJ(G, v0);//迪杰斯特拉算法
			break;
		case 2:
			cout << "请输入从哪个城市出发（ABCDEFG）：";
			cin >> ch;
			if (!checkch(ch))
				continue;
			v0 = ch - 65;
			cout << "请输入到哪个城市(ABCDEFG)：";//输入终点城市，将位置存放在v1
			rewind(stdin);
			cin >> ch;
			if (!checkch(ch))
				continue;
			v1 = ch - 65;
			ShortestPath_Floyd(G, v0, v1);//弗洛伊德算法
			break;
		case 3:
			CreateUDN(G);
			cout << endl << "随机生成完毕！" << endl;
			break;
		case 0:
			flag = false;
		default:
			continue;
		}
		cout << endl << endl;
		system("pause");
	}
	system("cls");
	cout << "欢迎再次使用，请按任意键退出。" << endl;
	system("pause>nul&cls");
	return 0;
}