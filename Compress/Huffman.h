#pragma once
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode,*HuffmanTree;

int Build(HuffmanTree &HT,int * w,int n);
//w��ʾÿ���ַ����ִ��������飬n��ʾ�ַ�����������root���±�
void Coding(HuffmanTree HT,char codes[][20], int num, char* s,int cnt);
//����
