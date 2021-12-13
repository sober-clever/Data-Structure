#include"Huffman.h"
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int Build(HuffmanTree & HT, int* w, int n)
{
	int m = 2 * n - 1;//m存Huffman树总的顶点数
	HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));//HT存下每个顶点的信息(HT下标从1开始)
	for (int i = 1; i <=n; i++) HT[i] = { w[i-1],0,0,0 };
	for (int i = n+1; i <=m; i++) HT[i] = { 0,0,0,0 };//赋初值
	int first_min, second_min;//找出权值最小且未被合并的两个字符的下标
	for (int j = n+1; j <=m; j++)
	{//一共合并n-1次
		first_min = second_min = 0;
		for (int i = 1; i <=j-1; i++)
		{
			if (HT[i].parent) continue;
			if (first_min == 0)
			{
				first_min = i;
				continue;
			}
			if (HT[i].weight < HT[first_min].weight)
			{
				second_min = first_min;
				first_min = i;
			}
			else
			{
				if (second_min == 0 || HT[second_min].weight > HT[i].weight)
					second_min = i;
			}

		}
		HT[j].weight = HT[first_min].weight + HT[second_min].weight;
		HT[first_min].parent = HT[second_min].parent = j;
		HT[j].lchild = first_min;
		HT[j].rchild = second_min;
	}
	for (int i = 1; i <= m; i++) if (HT[i].parent == 0) return i;
}
void Coding(HuffmanTree HT, char codes[][20], int num, char* s,int cnt)
{
	if (HT[num].lchild == 0 && HT[num].rchild == 0)
	{
		s[cnt] = '\0';
		strcpy_s(codes[num-1],s);
		return;
	}
	if (HT[num].lchild)
	{
		s[cnt] = '0';//向左为0
		Coding(HT, codes, HT[num].lchild, s, cnt + 1);
	}
	if (HT[num].rchild)
	{
		s[cnt] = '1';//向右为1
		Coding(HT, codes, HT[num].rchild, s, cnt + 1);
	}
}