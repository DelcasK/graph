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
	ArcNode*firstarc;                               //指向第一个边结点
	int count;                                           //此为新增的结构体变量，用于拓扑排序，表示入度
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
	for (int i = 0; i < mg.n; ++i)
	{
		for (int j = 0; j < mg.n; ++j)
		{
			if (mg.edges[i][j] == 0)
			{
				mg.edges[i][j] = INF;
			}
		}
	}
	for (int i = 0; i < mg.n; ++i)                                            //初始化lowcost和vset，其中lowcost中原本为0的值应该为INF，否则0为最小值，影响接下来的循环
	{
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
//1迪杰斯特拉算法
void Dijkstra(MGraph mg, int v0, int dist[], int path[])
{
	int set[MAXSIZE];                                                          //记录结点是否纳入
	int min,v;
	for (int i = 0; i < mg.n; ++i)
	{
		for (int j = 0; j < mg.n; ++j)
		{
			if (mg.edges[i][j]==0)
			{
				mg.edges[i][j]=INF;
			}
		}
	}
	for (int i = 0; i < mg.n; ++i)                                          //初始化dist，path数组（dist记录v0所连接的边的结点位置，path记录最短路径下的前一个结点的位置）
	{
		dist[i] = mg.edges[v0][i];
		set[i] = 0;
		if (mg.edges[v0][i]<INF)
		{
			path[i] = mg.edges[v0][i];
		}
		else
		{
			path[i] = -1;                                                         //若不存在前一结点，则赋值为-1
		}
	}
	set[v0] = 1;                                                                  //将v0纳入
	path[v0] = -1;                                                              //v0的前一结点设为-1
	for (int i = 0; i < mg.n-1; ++i)                                     //进行n-1次操作，将所有结点纳入
	{
		min = INF;                                                               //每次循环时初始化min
		for (int j = 0; j < mg.n; ++j)                                    //找出剩余结点的最小路径
		{
			if (set[j]==0&&dist[j]<INF)
			{
				min = dist[j];
				v = j;
			}
		}
		set[v] = 1;
		for (int k = 0; k < mg.n; ++k)                                 //将剩余结点中的最短路径更新
		{
			if (set[k]==0&&(dist[v]+mg.edges[v][k])<dist[k])
			{
				dist[k] = dist[v] + mg.edges[v][k];
				path[k] = v;
			}
		}
	}
}
//由于path数组记录的是当前结点的前一结点的位置，若需要打印从源结点出发到当前结点的路径，需要逆输出（用栈实现）
void printPath(int path[], int a)
{
	int stack[MAXSIZE];
	int top = -1;
	while (a!=-1)
	{
		stack[++top] = a;
		a = path[a];
	}
	while (top!=-1)
	{
		std::cout << stack[top--] << "  ";
	}
}

//2弗洛伊德算法
void Floyd(MGraph mg, int path[][MAXSIZE])
{
	int A[MAXSIZE][MAXSIZE];
	for (int i = 0; i < mg.n; ++i)
	{
		for (int j = 0; j < mg.n; ++j)                                         //对原数组进行处理，将非对角线上的0值改为INF
		{
			if (mg.edges[i][j] == 0&&i!=j)
			{
				mg.edges[i][j] = INF;
			}
		}
	}
	for (int i = 0; i < mg.n; ++i)                                             //初始化数组
	{
		for (int j = 0; j < mg.n; ++j)
		{
			A[i][j] = mg.edges[i][j];
			path[i][j] = -1;
		}
	}
	for (int i = 0; i < mg.n; i++)                                             //套三层循环，第一层用于遍历所有的结点，第二第三层用于遍历数组
	{
		for (int j = 0; j < mg.n; j++)
		{
			for (int k = 0; k < mg.n; k++)
			{
				if (A[j][k]>A[j][i]+A[i][k])
				{
					A[j][k]=A[j][i] + A[i][k];
					path[j][k] = i;
				}
			}
		}
	}
}
//path数组打印成路径的实现
void printPath(int u, int v, int path[][MAXSIZE])
{
	if (path[u][v]==-1)
	{
		std::cout << path[u][v] << " ";
	}
	else
	{
		printPath(u, path[u][v],path);
		printPath( path[u][v],v,path);
	}
}


//拓扑排序
//AOV网（单向无环）
//VNode结点中新增的count表示入度用于拓扑排序，拓扑排序是将count为0的结点先选出，再将
//剩余结点的count-1，直至所有的结点均被选出为止
//拓扑排序的特点：若存在u到v的路径，则在拓扑排序中，u必定在v之前
//拓扑排序
int topSort(AGraph*ag)
{
	int stack[MAXSIZE];                                                 //用栈记录，过程中只将入度为0的结点推入栈中
	int top = -1;
	int sum,a;                                                                
	ArcNode*p;
	for (int i = 0; i < ag->n; i++)                                  //进行第一次循环，将count为0的结点推入栈中
	{
		if (ag->adjlist[i].count==0)
		{
			stack[++top] = i;
		}
	}
	while (top!=-1)
	{
		a = stack[top--];
		std::cout << a << " ";
		++sum;
		p = ag->adjlist[a].firstarc;
		while (p)                                                                                 //将出栈的结点所对应的边结点的count值均减1，
		{                                                                                              //减一的过程中将count变为0的结点推入栈中
			if (--ag->adjlist[p->adjvex].count==0)
			{
				stack[++top] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	if (sum==ag->n)                                                                         //若循环结束后统计总数不为结点数，则报错
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//DFS非递归算法
void DFS1(AGraph*ag, int v)                             //自制  
{
	int stack1[MAXSIZE],stack2[MAXSIZE];         //stack1用于代替系统栈，stack2用于将边结点入栈时恢复顺序
	int visit[MAXSIZE] = {0};
	int top1 = -1,top2=-1;
	int a;
	ArcNode*p = NULL;
	VNode q;
	stack1[++top1] = v;
	visit[v] = 1;
	while (top1!=-1)
	{
		a = stack1[top1--];
		std::cout << a << " ";
		q = ag->adjlist[a];
		p = ag->adjlist[a].firstarc;
		while (p)
		{
			if (visit[p->adjvex]==0)
			{
				stack2[++top2] = p->adjvex;
			}
		}
		stack1[++top1] == stack2[top2--];
	}
}

void DFS2(AGraph*ag, int v)
{
	int stack[MAXSIZE];
	int top = -1;
	int a;
	ArcNode*p = NULL;
	int visit[MAXSIZE] = { 0 };
	Visit(v);
	visit[v] = 1;
	stack[top++] = v;
	while (top!=-1)
	{
		a = stack[top];
		p = ag->adjlist[a].firstarc;
		while (p&&visit[p->adjvex]==1)                                      //找出第一个未被访问的结点
		{
			p->nextarc;
		}
		if (p==NULL)                                                                     //若是由于p为空而退出循环，则栈顶元素出栈
		{
			--top;
		}
		else                                                                                    //否则入栈p对应的元素并对其进行访问
		{
			Visit(p->adjvex);
			visit[p->adjvex] = 1;
			stack[++top] = p->adjvex;
		}
	}
}