#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<ctime>
#include"Graph.h"
using namespace std;
extern int con_num[MAX_VERTEX_NUM];//存编号为i的点在G.vertices中对应的下标
bool read(FILE*fp,int& x)
{
	x = 0;
	char c;
	if (feof(fp)) return false;
	fread(&c, sizeof(char), 1, fp);
	while(c<'0'|| c>'9')
	{
		fread(&c, sizeof(char), 1, fp); 
		if (feof(fp)) return false;
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - 48;
		fread(&c, sizeof(char), 1, fp);
		if (feof(fp)) return false;
	}
}
ALGraph G;
int g_ans, g_path[MAX_VERTEX_NUM];
int main()
{
	double start = clock();
	FILE* fp = fopen("distance_info_2.txt","rb");
	int src, dst, w;// , cnt = 0;
	while (1)
	{
		if (!read(fp, src))
			break;
		if (!read(fp, dst))
			break;
		if (!read(fp, w))
			break;
		Add_edge(G, src, dst, w);
		
	}
	fclose(fp);
	printf("1\n");
	double terminal = clock();
	printf("time = %.2lfms\n", terminal - start);
	scanf("%d%d", &src, &dst);
	start = clock();
	Dijkstra(G, src, dst, g_ans, g_path);
	fp = fopen("ans.txt", "w");
	fprintf(fp, "The shortest distance is %d.\n", g_ans);
	fprintf(fp, "The path is as follows:\n");
	int node = con_num[dst];
	while (node != con_num[src])
	{
		fprintf(fp, "%d<-", G.vertices[node].num);
		node = g_path[node];
	}
	fprintf(fp, "%d\n", src);
	fclose(fp);
	terminal = clock();
	printf("%.2lfms\n", terminal - start);
	return 0;
}