#include"Graph.h"
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#define INF 1<<30
int con_num[MAX_VERTEX_NUM] = { 0 };//存编号为i的点在G.vertices中对应的下标
int Locate(ALGraph G_,int u_)
{
	return con_num[u_];
}

void  Add_edge(ALGraph& G_, int u_, int v_, int w_)//从u到v新建一条权值为w的边
{//这里可以考虑先把G.vexnum存下来
	int num_u = Locate(G_,u_),num_v = Locate(G_,v_);
	ArcNode* new_arc = (ArcNode*)malloc(sizeof(ArcNode));
	if (!new_arc)
	{
		printf("Memory exceeded.\n");
		exit(0);
	}
	if (!num_u )
	{
		G_.vertices[++G_.vexnum].firstarc = NULL;
		G_.vertices[G_.vexnum].num = u_;
		num_u = G_.vexnum;
		con_num[u_] = num_u;
	}
	if (!num_v )
	{
		G_.vertices[++G_.vexnum].firstarc = NULL;
		G_.vertices[G_.vexnum].num = v_;
		num_v = G_.vexnum;
		con_num[v_] = num_v;
	}
	//printf("%d %d\n", num_u, num_v);
	new_arc->weight = w_;
	new_arc->adjvex = num_v;
	new_arc->nextarc = G_.vertices[num_u].firstarc;
	G_.vertices[num_u].firstarc = new_arc;
}
void Dijkstra(ALGraph G_, int s_, int t_, int& ans_, int path_[])//后续可用堆优化
{
	s_ = Locate(G_, s_);
	t_ = Locate(G_, t_);
	int d[MAX_VERTEX_NUM], vis[MAX_VERTEX_NUM];
	for (int i = 1; i <= G_.vexnum; i++)
	{
		d[i] = INF;
		vis[i] = 0;
	}
	ArcNode* p;
	for (p = G_.vertices[s_].firstarc; p; p = p->nextarc)
	{
		int v = p->adjvex;
		d[v] = p->weight;
		path_[v] = s_;
	}
	d[s_] = 0;
	vis[s_] = 1;
	for (int i = 1; i < G_.vexnum; i++)
	{
		int Min = INF, k = -1;
		for (int j = 1; j <= G_.vexnum; j++)
		{
			if (Min > d[j] && !vis[j])
			{
				Min = d[j];
				k = j;
			}
		}
		//printf("%d\n", k);
		if (k == -1)
		{
			break;
		}

		for (p = G_.vertices[k].firstarc; p; p = p->nextarc)
		{
			int v = p->adjvex;
			if (d[k] + p->weight < d[v])
			{
				d[v] = d[k] + p->weight;//更新最短路
				path_[v] = k;//存下k的前驱
			}
		}
		vis[k] = 1;
	}
	ans_ = d[t_];

}