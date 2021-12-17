#pragma once
#define MAX_VERTEX_NUM 300000 //上限3000000个点
//图的邻接表表示
typedef struct ArcNode//一个ArcNode结构体占用12个字节
{
    int adjvex;
    struct ArcNode* nextarc;
    int weight;//边的权重
}ArcNode;
typedef struct VNode 
{
    int num;//点的编号
    ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;
void Add_edge(ALGraph &G_,int u_,int v_,int w_);//从u到v新建一条权值为w的边
void Dijkstra(ALGraph G_, int s,int t,int& ans_, int path_[]);

//int Locate(ALGraph G_, int u_);
//s_是出发点，t_是目的地的，ans_是最短路的值，path是最短路的路径
