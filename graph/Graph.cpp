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
	int adjves;                                            //ָ��Ľ���λ�ã���ţ�
	//int weight;                                        //Ȩ��
	struct ArcNode *nextarc;                        //ָ����һ���߽��
}ArcNode;

typedef struct                                         //ͷ���
{
	char data;                                           //�����Ϣ
	ArcNode*firstarc                               //ָ���һ���߽��
}VNode;
 
typedef struct                                         //�ڽӱ���
{
	VNode adjlist[MAXSIZE][MAXSIZE];//�ڽӱ�
	int n,e                                                 //������������
}AGraph;

//�ڽӱ�

