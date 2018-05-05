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
	int adjves;                                            //指向的结点的位置（编号）
	//int weight;                                        //权重
	struct ArcNode *nextarc;                        //指向下一个边结点
}ArcNode;

typedef struct                                         //头结点
{
	char data;                                           //结点信息
	ArcNode*firstarc                               //指向第一个边结点
}VNode;
 
typedef struct                                         //邻接表定义
{
	VNode adjlist[MAXSIZE][MAXSIZE];//邻接表
	int n,e                                                 //顶点数，边数
}AGraph;

//邻接表

