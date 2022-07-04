#include <iostream>
#define MaxInt 60000//表示极大值
#define Range 10000//随机数的最大路径长度
using namespace std;
typedef char VerTexType;//假设顶点的数据类型为字符型
typedef int ArcType;//假设边的权值为整型

struct AMGraph
{
	VerTexType vexs[6] = { 0 };//顶点表
	ArcType arcs[6][6] = { {0} };//邻接矩阵
	int vexnum = 6, arcnum = 9;//图的当前结点数和边数
};

int LocateVex(AMGraph G, int v)//查找顶点V在图中的位置
{
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)//图G存在，v和G中顶点有相同特征
			return i;//返回该顶点在图的位置
	return -1;
}

void InitGraph(AMGraph& G)//采用邻接矩阵创建有向图
{
	int i, j, k, w[9] = { rand() % Range };
	char v1[9] = { 'A','A','A','B','B','C','C','D','E' }, v2[9] = { 'B','C','D','C','E','D','F','F','F' };
	for (i = 0; i < 9; ++i)
	{
		w[i] = rand() % Range;
		//cout << i << '\t' << w[i] << endl;
	}
	G.vexnum = 6;//总顶点数
	G.arcnum = 9;//总边数
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
	return;
}

void ShortestPath_DIJ(AMGraph G, int v0)//用迪杰斯特拉算法求有向网G的v0顶点到其余顶点的最短路径
{
	if (v0 < 0 || v0 > G.vexnum)
		return;
	int i, t, j = 0, w, v, min, Path[6] = { 0 }, S[6] = { 0 }, D[6] = { 0 }, a[5] = { 0 };
	for (v = 0; v < G.vexnum; ++v)//顶点依次初始化
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
	for (i = 1; i < G.vexnum; ++i)//对其余n-1个顶点，依次进行计算
	{
		min = MaxInt;
		for (w = 0; w < G.vexnum; ++w)
			if (!S[w] && D[w] < min)
			{
				v = w;//选择一条当前的最短路径，终点为v
				min = D[w];
			}
		S[v] = true;//将v加入S
		for (w = 0; w < G.vexnum; ++w)//更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];//更新D[w]
				Path[w] = v;//更改w的前驱为v
			}
	}

	/* 输出最短路径以及距离，并按照距离从大到小的顺序排序 */
	for (i = 0; i < G.vexnum; i++)
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
	cout << "迪杰斯特拉算法，按照距离从大到小输出如下：" << endl << endl;
	cout << "路径长度\t路径" << endl;
	for (i = 0; i < j; ++i)
	{
		printf(" %5d", D[a[i]]);
		printf("     %5c", G.vexs[a[i]]);
		v = Path[a[i]];//将Path所对应的位置赋给v
		while (v != 0)//判断是否有中继点
		{
			if (v >= 0 && v < 6)
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
	if (v0 < 0 || v0 > G.vexnum || v1 < 0 || v1 > G.vexnum)
		return;
	int i, j, k, v, D[6][6] = { 0 }, Path[6][6] = { 0 };
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
		cout << "注意：出发地与目的地相同。" << endl;
}

int main()
{
	system("chcp 936&title 求最短路径&color e&cls");
	AMGraph G;
	InitGraph(G);//构建邻接矩阵
	ShortestPath_DIJ(G, 0);//迪杰斯特拉算法
	cout << endl << endl << "弗洛伊德算法，按结点顺序输出如下：" << endl;
	for (int i = 1; i < 6; ++i)
		ShortestPath_Floyd(G, 0, i);//弗洛伊德算法
	cout << endl << endl << "演示完毕，请按任意键退出本程序。" << endl;
	system("pause>nul&cls");
	return 0;
}