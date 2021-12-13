#pragma once
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode,*HuffmanTree;

int Build(HuffmanTree &HT,int * w,int n);
//w表示每个字符出现次数的数组，n表示字符总数，返回root的下标
void Coding(HuffmanTree HT,char codes[][20], int num, char* s,int cnt);
//编码
