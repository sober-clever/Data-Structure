#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include"Graph.h"
using namespace std;
ALGraph G;
int g_ans, g_path[MAX_VERTEX_NUM];
int main()
{
	FILE* fp = fopen("distance_info_2.txt","r");
	int src, dst, w;// , cnt = 0;
	while (fscanf(fp, "%d %d %d", &src, &dst, &w) != EOF)
	{
		Add_edge(G, src, dst, w);
		//cnt++;
		//printf("%d\n", cnt);
	}
	fclose(fp);
	printf("1\n");
	//fp = fopen("public_test_2.txt", "r");
	//fscanf(fp, "%d %d", &src, &dst);
	scanf("%d%d", &src, &dst);
	Dijkstra(G, src, dst, g_ans, g_path);
	fp = fopen("ans.txt", "w");
	fprintf(fp, "The shortest distance is %d.\n", g_ans);
	fprintf(fp, "The path is as follows:\n");
	int node = Locate(G,dst);
	while (node != Locate(G,src))
	{
		fprintf(fp, "%d<-", G.vertices[node].num);
		node = g_path[node];
	}
	fprintf(fp, "%d\n", src);
	return 0;
}