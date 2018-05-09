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
	ArcNode*firstarc;                               //ָ���һ���߽��
	int count;                                           //��Ϊ�����Ľṹ������������������򣬱�ʾ���
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
	for (int i = 0; i < mg.n; ++i)                                            //��ʼ��lowcost��vset������lowcost��ԭ��Ϊ0��ֵӦ��ΪINF������0Ϊ��Сֵ��Ӱ���������ѭ��
	{
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
//1�Ͻ�˹�����㷨
void Dijkstra(MGraph mg, int v0, int dist[], int path[])
{
	int set[MAXSIZE];                                                          //��¼����Ƿ�����
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
	for (int i = 0; i < mg.n; ++i)                                          //��ʼ��dist��path���飨dist��¼v0�����ӵıߵĽ��λ�ã�path��¼���·���µ�ǰһ������λ�ã�
	{
		dist[i] = mg.edges[v0][i];
		set[i] = 0;
		if (mg.edges[v0][i]<INF)
		{
			path[i] = mg.edges[v0][i];
		}
		else
		{
			path[i] = -1;                                                         //��������ǰһ��㣬��ֵΪ-1
		}
	}
	set[v0] = 1;                                                                  //��v0����
	path[v0] = -1;                                                              //v0��ǰһ�����Ϊ-1
	for (int i = 0; i < mg.n-1; ++i)                                     //����n-1�β����������н������
	{
		min = INF;                                                               //ÿ��ѭ��ʱ��ʼ��min
		for (int j = 0; j < mg.n; ++j)                                    //�ҳ�ʣ�������С·��
		{
			if (set[j]==0&&dist[j]<INF)
			{
				min = dist[j];
				v = j;
			}
		}
		set[v] = 1;
		for (int k = 0; k < mg.n; ++k)                                 //��ʣ�����е����·������
		{
			if (set[k]==0&&(dist[v]+mg.edges[v][k])<dist[k])
			{
				dist[k] = dist[v] + mg.edges[v][k];
				path[k] = v;
			}
		}
	}
}
//����path�����¼���ǵ�ǰ����ǰһ����λ�ã�����Ҫ��ӡ��Դ����������ǰ����·������Ҫ���������ջʵ�֣�
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

//2���������㷨
void Floyd(MGraph mg, int path[][MAXSIZE])
{
	int A[MAXSIZE][MAXSIZE];
	for (int i = 0; i < mg.n; ++i)
	{
		for (int j = 0; j < mg.n; ++j)                                         //��ԭ������д������ǶԽ����ϵ�0ֵ��ΪINF
		{
			if (mg.edges[i][j] == 0&&i!=j)
			{
				mg.edges[i][j] = INF;
			}
		}
	}
	for (int i = 0; i < mg.n; ++i)                                             //��ʼ������
	{
		for (int j = 0; j < mg.n; ++j)
		{
			A[i][j] = mg.edges[i][j];
			path[i][j] = -1;
		}
	}
	for (int i = 0; i < mg.n; i++)                                             //������ѭ������һ�����ڱ������еĽ�㣬�ڶ����������ڱ�������
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
//path�����ӡ��·����ʵ��
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


//��������
//AOV���������޻���
//VNode�����������count��ʾ������������������������ǽ�countΪ0�Ľ����ѡ�����ٽ�
//ʣ�����count-1��ֱ�����еĽ�����ѡ��Ϊֹ
//����������ص㣺������u��v��·�����������������У�u�ض���v֮ǰ
//��������
int topSort(AGraph*ag)
{
	int stack[MAXSIZE];                                                 //��ջ��¼��������ֻ�����Ϊ0�Ľ������ջ��
	int top = -1;
	int sum,a;                                                                
	ArcNode*p;
	for (int i = 0; i < ag->n; i++)                                  //���е�һ��ѭ������countΪ0�Ľ������ջ��
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
		while (p)                                                                                 //����ջ�Ľ������Ӧ�ı߽���countֵ����1��
		{                                                                                              //��һ�Ĺ����н�count��Ϊ0�Ľ������ջ��
			if (--ag->adjlist[p->adjvex].count==0)
			{
				stack[++top] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	if (sum==ag->n)                                                                         //��ѭ��������ͳ��������Ϊ��������򱨴�
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//DFS�ǵݹ��㷨
void DFS1(AGraph*ag, int v)                             //����  
{
	int stack1[MAXSIZE],stack2[MAXSIZE];         //stack1���ڴ���ϵͳջ��stack2���ڽ��߽����ջʱ�ָ�˳��
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
		while (p&&visit[p->adjvex]==1)                                      //�ҳ���һ��δ�����ʵĽ��
		{
			p->nextarc;
		}
		if (p==NULL)                                                                     //��������pΪ�ն��˳�ѭ������ջ��Ԫ�س�ջ
		{
			--top;
		}
		else                                                                                    //������ջp��Ӧ��Ԫ�ز�������з���
		{
			Visit(p->adjvex);
			visit[p->adjvex] = 1;
			stack[++top] = p->adjvex;
		}
	}
}