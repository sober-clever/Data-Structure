//#pragma GCC optimize(3)
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<ctime>
#include"Graph.h"
using namespace std;
extern int con_num[MAX_VERTEX_NUM];//存编号为i的点在G.vertices中对应的下标
int g_flag = 0;
unsigned char num[2], i = 0;
void read(FILE*fp,int& x)
{
	x = 0;
	unsigned char c;
	//if (feof(fp)) return false;
	if (!g_flag)
	{
		fread(&c, 1, 1, fp);
		g_flag = 1;
		num[0] = c >> 4;//取前四位
		num[1] = c & 15;//取后四位
	}
	else
	{
		if (i == 1)
		{
			fread(&c, sizeof(unsigned char), 1, fp);
			num[0] = c >> 4;//取前四位
			num[1] = c & 15;//取后四位
		}
		i ^= 1;
	}
	//printf("%d %d\n",num[0],num[1]);
	while(num[i]==15)//表明不是字符
	{
		if (i == 1)
		{
			fread(&c, sizeof(unsigned char), 1, fp);
			num[0] = c >> 4;
			num[1] = c & 15;
		}
		i ^= 1;
		//if (feof(fp)) return false;
	}
	while (0<=num[i]&&num[i]<=9)
	{
		//printf("%d", num[i]);
		x = (x << 3) + (x << 1) + num[i];
		if (i == 1)
		{
			fread(&c, sizeof(unsigned char), 1, fp);
			num[0] = c >> 4;
			num[1] = c & 15;
		}
		i ^= 1;
		//if (feof(fp)) return false;
	}
	//printf("\n");
	//return true;
}
ALGraph G;
int g_ans, g_path[MAX_VERTEX_NUM];
int main()
{
	double start = clock();
	//printf("%d %d\n",sizeof(int), sizeof(ArcNode));
	FILE* fp = fopen("dist2.bin","rb");
	int src, dst, w;// , cnt = 0;
	while (1)
	{
		/*if (!read(fp, src))
			break;
		if (!read(fp, dst))
			break;
		if (!read(fp, w))
			break;*/
		read(fp, src);
		read(fp, dst);
		read(fp, w);
		if (feof(fp)) break;
		//cnt++;
		//printf("\n%d %d %d\n", src, dst, w);
		Add_edge(G, src, dst, w);
	}
	fclose(fp);
	printf("1\n");
	double terminal = clock();
	printf("time = %.2lfms\n", terminal - start);
	scanf("%d%d", &src, &dst);
	start = clock();
	Dijkstra(G, src, dst, g_ans, g_path);
	//printf("%d\n", g_ans);
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