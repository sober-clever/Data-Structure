#pragma once
#define MAX_VERTEX_NUM 800000 //����800000����
//ͼ���ڽӱ��ʾ
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode* nextarc;
    int weight;//�ߵ�Ȩ��
}ArcNode;
typedef struct VNode 
{
    int num;//��ı��
    ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;
void  Add_edge(ALGraph &G_,int u_,int v_,int w_);//��u��v�½�һ��ȨֵΪw�ı�
void Dijktra(ALGraph G_, int s,int t,int& ans_, int path_[]);
//s_�ǳ����㣬t_��Ŀ�ĵصģ�ans_�����·��ֵ��path�����·��·��
