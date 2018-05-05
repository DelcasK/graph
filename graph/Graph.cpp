#include<iostream>
#define MAXSIZE 100

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