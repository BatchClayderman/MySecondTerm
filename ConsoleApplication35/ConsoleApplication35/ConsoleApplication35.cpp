#include <iostream>
#define MAXSIZE 500
typedef char elemtype;
using namespace std;

typedef struct edgenode//边结点类型定义
{
    int adjvex;//顶点下标
    int weight;//权值
    struct edgenode* next;
}edgenode;

typedef struct vexnode//顶点结点类型定义
{
    elemtype data;//存储顶点的名称或其相关信息
    edgenode* firstedge;//边表头指针
}vexnode;

typedef struct graph//图
{
    vexnode vexlist[MAXSIZE];//顶点表
    int n = 0, e = 0;
}graph;

int locatevex(graph g, elemtype v)//在图中查找顶点v，存在顶点数组中的下标，不存在返回-1
{
    for (int i = 0; i < g.n; ++i)
        if (g.vexlist[i].data == v)
            return i;
    return -1;
}

bool creategraph(graph* g)//建立有向图
{
    if (g == NULL)
        return false;
    g->n = 0;
    g->e = 0;
    int i = 0, j = 0;
    elemtype v1, v2;
    edgenode* s;
    cout << "/*************** 录入有向图的边信息 ***************/" << endl;
    cout << "输入示例（引号内）：“<a,b>”，当两个元素至少有一个为 0 时，停止录入。" << endl << endl;
    while (g->n < MAXSIZE - 1 && g->e < MAXSIZE - 1)
    {
        cout << "请输入第 " << g->e + 1 << " 条边的两个端点下标：";
        rewind(stdin);
        scanf_s("<%c,%c>", &v1, sizeof(v1), &v2, sizeof(v2));
        if (v1 == '0' || v2 == '0')
            break;
        else if (v1 == v2 || v1 < '0' || v2 < '0')
        {
            cout << "\a错误：端点元素相同，或输入有误，请检查您的上述输入。" << endl;
            continue;
        }
        else
            g->e++;
        if ((i = locatevex(*g, v1)) < 0 && (++g->n) < MAXSIZE - 2)
        {
            g->vexlist[g->n].data = v1;
            i = locatevex(*g, v1);
        }
        if ((j = locatevex(*g, v2)) < 0 && (++g->n) < MAXSIZE - 2)
        {
            g->vexlist[g->n].data = v2;
            j = locatevex(*g, v2);
        }
        if (i >= 0 && j >= 0)//建立有向图的邻接表
        {
            s = (edgenode*)malloc(sizeof(edgenode));
            if (!s)
                exit(OVERFLOW);
            s->adjvex = j;
            s->next = g->vexlist[i].firstedge;
            g->vexlist[i].firstedge = s;
        }
    }
    rewind(stdin);
    return true;
}

int main()
{
    system("chcp 936&title 建立有向图&color e&cls");
    graph* g;
    g = (graph*)malloc(sizeof(graph));
    if (creategraph(g))
        cout << endl << endl << "建图成功，请按任意键退出。" << endl;
    else
        cout << "\a错误：申请内存资源失败，请按任意键退出。" << endl;
    system("pause>nul&cls");
    return 0;
}