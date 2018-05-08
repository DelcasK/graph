#include<iostream>
#define MAXSIZE 100
#define INF 100

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

//��С�����ۣ�������������ͼ��
//1����ķ�㷨
void Prim(MGraph mg,int v0,int&sum)
{
	int lowcost[MAXSIZE], vset[MAXSIZE];                           //lowcost��Ž�����̱ߣ�vset��ʾ����Ƿ��ѱ�����
	int sum,min,v;                                                                 //sum��¼��Ȩֵ��min��¼ÿ��ѭ����ʣ��ڵ��е���̱ߵ�ֵ��v���ڱ�ʾ����Ľ���λ��
	for (int i = 0; i < mg.n; ++i)                                            //��ʼ��lowcost��vset������lowcost��ԭ��Ϊ0��ֵӦ��ΪINF������0Ϊ��Сֵ��Ӱ���������ѭ��
	{
		if (mg.edges[v0][i]==0)
		{
			mg.edges[v0][i] = INF;
		}
		lowcost[i] = mg.edges[v0][i];
		vset[i] = 0;
	}
	vset[v0] = 1;                                                                  //����v0
	sum = 0;                                                                        //��ʼ��sum
	for (int i=0;i<mg.n-1;++i)                                             //��ѭ������ÿһ��ѭ������һ����㣬��ѭ��n-1��
	{
		min = INF;                                                                 //ÿ�δ�ѭ���£���Ӧ�ó�ʼ��minֵ
		for (int j = 0; j < mg.n; ++j)                                      //�ҳ�ʣ��ڵ��е���̱ߣ���ֵ��min��v
		{
			if (vset[j] == 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				v = j;
			}
		}
		vset[v] = 1;                                                                //����Ӧ�Ľ�����룬����vset��Ӧ��λ�õ�ֵ��Ϊ1
		sum += min;                                                             //ͳ��sum
		for (int j = 0; j < mg.n; ++j)                                      //����lowcost�����¼���Ľ��ı߱�������lowcost��Ӧ��ֵ�Ƚϣ���С��lowcost���滻
		{
			if (vset[j]==0&&mg.edges[v][j]<lowcost[j])
			{
				lowcost[j] = mg.edges[v][j];
			}
		}
	}
}

//2��³˹�����㷨
typedef struct
{
	int a, b;                                                                          //���ߵĽ���ֵ
	int w;                                                                             //�ߵ�Ȩֵ
}Road;
Road road[MAXSIZE];                                                       //ǰ��������road�Ѿ����ú�
int v[MAXSIZE];                                                                 //���岢�鼯����
int getRoot(int a)                                                              //whileѭ��ֱ���������㣨������a=v[a]��
{
	while (a!=v[a])
	{
		a = v[a];
	}
	return a;
}
void sort(Road road[], int e)
{
	//��road���д�С���������
}
void Kruskal(MGraph mg, int&sum, Road road[])
{
	int a, b;                                                                           //�ֱ����ڴ�űߵ����˵Ľ��
	sum = 0;
	for (int i = 0; i < mg.n; ++i)                                           //�����еĽ�����������ÿ�����ĸ���㶼���Լ�����
	{
		v[i] = i;
	}
	sort(road, mg.e);                                                            //��road����������
	for (int i = 0; i < mg.e; ++i)                                           //��ÿ���߽���ѭ��
	{
		a = getRoot(road[i].a);
		b = getRoot(road[i].b);
		if (a!=b)                                                                      //�����ߵĽ��ĸ���㲻ͬ����������Բ��루��ͬʱ���ܲ��룬�ṹ�ɻ���
		{
			v[a] = b;
			sum += road[i].w;
		}
	}
}


//���·��
//�Ͻ�˹�����㷨
void 