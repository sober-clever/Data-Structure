#include<cstdio>
#include<iostream>
#include"Graph.h"
using namespace std;
ALGraph G;
int ans, path[MAX_VERTEX_NUM];
int main()
{
	FILE* fp = fopen("distance_info2.txt","r");
	int src, dst, w;
	while (fscanf(fp, "%d %d %d", &src, &dst, &w) != EOF)
		Add_edge(G, src, dst, w);
	fclose(fp);
	fp = fopen("public_test_2.txt", "r");
	fscanf(fp, "%d %d", &src, &dst);
	Dijktra(G, src, dst, ans, path);
	//Êä³öansºÍpath
	return 0;
}