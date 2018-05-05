#include<iostream>
#define MAXSIZE 100

//�ڽӾ���

typedef struct
{
	int no;                                      //������
	//char info;                              //�������Ϣ��һ�㲻���ж�����Ϣ����������
}VertexType;                                //��������

typedef struct
{
	int edges[MAXSIZE][MAXSIZE];      //�ڽӾ�����   
	int n, e;                                             //������������
	VertexType vex[MAXSIZE];             //��Ž����Ϣ
}MGraph;                                             //ͼ�Ķ���

//�ڽӾ���


//�ڽӱ�

typedef struct ArcNode                          //�߽�㶨��
{
	int adjvex;                                            //ָ��Ľ���λ�ã���ţ�
	//int weight;                                        //Ȩ��
	struct ArcNode *nextarc;                        //ָ����һ���߽��
}ArcNode;

typedef struct                                         //ͷ���
{
	char data;                                           //�����Ϣ
	ArcNode*firstarc;                              //ָ���һ���߽��
}VNode;
 
typedef struct                                         //�ڽӱ���
{
	VNode adjlist[MAXSIZE];                  //�ڽӱ�
	int n, e;                                                //������������
}AGraph;

//�ڽӱ�

//DFS(���������������)
int visit[MAXSIZE];                                             //ȫ�����飬���ڱ�Ƕ�Ӧ��ŵĽ���Ƿ���ʹ�����ֵΪ0
void Visit(int v){}                                                //Visit�������ڷ��ʽ��
void DFS(AGraph*ag, int v)                              //v���ڱ�ʾ���ʵĵ�һ�����ı��
{
	ArcNode*p = ag->adjlist[v].firstarc;
	visit[v] = 1;
	Visit(v);
	while (p)                                                         //��ͬһ���Ҫ��ѭ��
	{
		if (!visit[p->adjvex])
		{
			DFS(ag, p->adjvex);								//�ݹ�
		}
		p = p->nextarc;
	}
}

//BFS�������������������
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

//���ڷ���ͨͼ�������д��Ӧ��չΪ
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