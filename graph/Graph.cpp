#include<iostream>
#define MAXSIZE 100
#define INF 100

//邻接矩阵

typedef struct
{
	int no;                                      //顶点编号
	//char info;                              //顶点的信息，一般不会有额外信息，所以留空
}VertexType;                                //顶点类型

typedef struct
{
	int edges[MAXSIZE][MAXSIZE];      //邻接矩阵定义   
	int n, e;                                             //顶点数，边数
	VertexType vex[MAXSIZE];             //存放结点信息
}MGraph;                                             //图的定义

//邻接矩阵


//邻接表

typedef struct ArcNode                          //边结点定义
{
	int adjvex;                                            //指向的结点的位置（编号）
	//int weight;                                        //权重
	struct ArcNode *nextarc;                        //指向下一个边结点
}ArcNode;

typedef struct                                         //头结点
{
	char data;                                           //结点信息
	ArcNode*firstarc;                              //指向第一个边结点
}VNode;
 
typedef struct                                         //邻接表定义
{
	VNode adjlist[MAXSIZE];                  //邻接表
	int n, e;                                                //顶点数，边数
}AGraph;

//邻接表

//DFS(深度优先搜索遍历)
int visit[MAXSIZE];                                             //全局数组，用于标记对应编号的结点是否访问过，初值为0
void Visit(int v){}                                                //Visit函数用于访问结点
void DFS(AGraph*ag, int v)                              //v用于表示访问的第一个结点的编号
{
	ArcNode*p = ag->adjlist[v].firstarc;
	visit[v] = 1;
	Visit(v);
	while (p)                                                         //在同一深度要用循环
	{
		if (!visit[p->adjvex])
		{
			DFS(ag, p->adjvex);								//递归
		}
		p = p->nextarc;
	}
}

//BFS（广度优先搜索遍历）
void BFS(AGraph*ag, int v)
{
	int que[MAXSIZE];
	int front, rear;
	++rear;
	que[rear] =v;
	visit[v] = 1;
	ArcNode*p ;
	while (front!=rear)
	{
		++front;
		Visit(front);
		p = ag->adjlist[que[front]].firstarc;
		while (p)
		{
			if (visit[p->adjvex] == 0)
			{
				++rear;
				que[rear] = p->adjvex;
				visit[p->adjvex] = 1;
			}
			p = p->nextarc;
		}
	}
}

//对于非连通图，上面的写法应扩展为
void dfs(AGraph*ag)
{
	for (int i = 0; i < ag->n; ++i)
	{
		if (visit[i]==0)
		{
			DFS(ag, i);
		}
	}
}
void bfs(AGraph*ag)
{
	for (int i = 0; i < ag->n; ++i)
	{
		if (visit[i] == 0)
		{
			BFS(ag, i);
		}
	}
}

//最小（代价）生成树（无向图）
//1普里姆算法
void Prim(MGraph mg,int v0,int&sum)
{
	int lowcost[MAXSIZE], vset[MAXSIZE];                           //lowcost存放结点的最短边，vset表示结点是否已被纳入
	int sum,min,v;                                                                 //sum记录总权值，min记录每次循环下剩余节点中的最短边的值，v用于表示纳入的结点的位置
	for (int i = 0; i < mg.n; ++i)                                            //初始化lowcost和vset，其中lowcost中原本为0的值应该为INF，否则0为最小值，影响接下来的循环
	{
		if (mg.edges[v0][i]==0)
		{
			mg.edges[v0][i] = INF;
		}
		lowcost[i] = mg.edges[v0][i];
		vset[i] = 0;
	}
	vset[v0] = 1;                                                                  //纳入v0
	sum = 0;                                                                        //初始化sum
	for (int i=0;i<mg.n-1;++i)                                             //大循环，即每一次循环纳入一个结点，共循环n-1次
	{
		min = INF;                                                                 //每次大循环下，都应该初始化min值
		for (int j = 0; j < mg.n; ++j)                                      //找出剩余节点中的最短边，赋值给min和v
		{
			if (vset[j] == 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				v = j;
			}
		}
		vset[v] = 1;                                                                //将对应的结点纳入，即将vset对应的位置的值设为1
		sum += min;                                                             //统计sum
		for (int j = 0; j < mg.n; ++j)                                      //更新lowcost，用新加入的结点的边遍历，与lowcost对应的值比较，若小于lowcost则替换
		{
			if (vset[j]==0&&mg.edges[v][j]<lowcost[j])
			{
				lowcost[j] = mg.edges[v][j];
			}
		}
	}
}

//2克鲁斯卡尔算法
typedef struct
{
	int a, b;                                                                          //两边的结点的值
	int w;                                                                             //边的权值
}Road;
Road road[MAXSIZE];                                                       //前提条件，road已经设置好
int v[MAXSIZE];                                                                 //定义并查集数组
int getRoot(int a)                                                              //while循环直至到达根结点（根结点的a=v[a]）
{
	while (a!=v[a])
	{
		a = v[a];
	}
	return a;
}
void sort(Road road[], int e)
{
	//对road进行从小到大的排序
}
void Kruskal(MGraph mg, int&sum, Road road[])
{
	int a, b;                                                                           //分别用于存放边的两端的结点
	sum = 0;
	for (int i = 0; i < mg.n; ++i)                                           //将所有的结点独立化，即每个结点的根结点都是自己本身
	{
		v[i] = i;
	}
	sort(road, mg.e);                                                            //将road按升序排列
	for (int i = 0; i < mg.e; ++i)                                           //对每条边进行循环
	{
		a = getRoot(road[i].a);
		b = getRoot(road[i].b);
		if (a!=b)                                                                      //若两边的结点的根结点不同，则表明可以并入（相同时不能并入，会构成环）
		{
			v[a] = b;
			sum += road[i].w;
		}
	}
}


//最短路径
//迪杰斯特拉算法
void 