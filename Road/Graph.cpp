#include"Graph.h"
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>
#define INF 1<<30
using namespace std;
int con_num[MAX_VERTEX_NUM] = { 0 };//存编号为i的点在G.vertices中对应的下标

void  Add_edge(ALGraph& G_, int u_, int v_, int w_)//从u到v新建一条权值为w的边
{//这里可以考虑先把G.vexnum存下来
	int num_u = con_num[u_],num_v = con_num[v_];
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

	new_arc->weight = w_;
	new_arc->adjvex = num_v;
	new_arc->nextarc = G_.vertices[num_u].firstarc;
	G_.vertices[num_u].firstarc = new_arc;
}
void Dijkstra(ALGraph G_, int s_, int t_, int& ans_, int path_[])//后续可用堆优化
{
	priority_queue <pair<int, int> > Q;
	s_ = con_num[s_];
	t_ = con_num[t_];
	pair<int, int> temp = make_pair(0, s_);
	Q.push(temp);
	int d[MAX_VERTEX_NUM], vis[MAX_VERTEX_NUM];
	for (int i = 1; i <= G_.vexnum; i++)
	{
		d[i] = INF;
		vis[i] = 0;
	}
	d[s_] = 0;
	/*ArcNode* p;
	for (p = G_.vertices[s_].firstarc; p; p = p->nextarc)
	{
		int v = p->adjvex;
		d[v] = p->weight;
		path_[v] = s_;
	}*/
	ArcNode* p;
	while (!Q.empty())
	{
		temp = Q.top();
		Q.pop();
		int u = temp.second;
		if (vis[u])//之前出队过
			continue;
		vis[u] = 1;
		for (p = G_.vertices[u].firstarc; p; p = p->nextarc)
		{
			int v = p->adjvex, w = p->weight;
			if (d[v] > d[u] + w)
			{
				d[v] = d[u] + w;
				path_[v] = u;
				Q.push(make_pair(-d[v],v));
			}
		}
	}
	ans_ = d[t_];

}
