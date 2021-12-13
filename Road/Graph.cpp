#include"Graph.h"
#include<cstdlib>
#include<cstdio>
#include<algorithm>
void  Add_edge(ALGraph& G_, int u_, int v_, int w_)//从u到v新建一条权值为w的边
{
	int i;
	for (i = 1; i <= G_.vexnum; i++)
	{
		if (G_.vertices[i].num == u_)
			break;
	}
	ArcNode* new_arc = (ArcNode*)malloc(sizeof(ArcNode));
	if (!new_arc)
	{
		printf("Memory exceeded.\n");
		exit(0);
	}
	if (i > G_.vexnum)
	{
		G_.vertices[++G_.vexnum].firstarc = NULL;
		G_.vertices[G_.vexnum].num = u_;
	}
	i = G_.vexnum;	//这条可以省略
	new_arc->weight = w_;
	new_arc->adjvex = v_;
	new_arc->nextarc = G_.vertices[i].firstarc;
	G_.vertices[i].firstarc = new_arc;
}
void Dijkstra(ALGraph G_, int s, int t, int& ans_, int path_[])
{

}