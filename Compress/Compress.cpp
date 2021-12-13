#define _CRT_SECURE_NO_WARNINGS
#include"Huffman.h"
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN = 20;
void Str2Bin(char s[], unsigned char &c)
{
	c = 0;
	for (int i = 0; i < 8; i++)
		c = (c << 1) + s[i] - '0';
}
void Bin2Str(char s[],unsigned char c)
{
	for (int i = 0; i < 8; i++)
	{
		s[i] = c%2+'0';
		c >>= 1;
	}
	for (int i = 0; i <= 3; i++)
	{
		char t = s[i];
		s[i] = s[7 - i];
		s[7 - i] = t;
	}
	s[8] = '\0';
}
int main()
{
	char file_name[20];//�ļ���
	int cnt[260] = { 0 };//���ڼ�¼ÿ��ASCII���ַ����ļ��г����˶��ٴ�
	int new_cnt[260], num[260],n=0;
	unsigned char c_num[260];
	//cout << sizeof(unsigned char)<<endl;
	cout << "Please input the file you want to compress." << endl;
	cin >> file_name;
	FILE* fp = fopen(file_name,"rb");
	//FILE* fp_com = fopen("compressed.txt", "wb");//�Զ�����д�����ʽ��
	unsigned char c;//cΪ���ļ��ж������ַ�
	while (fread(&c,sizeof(unsigned char),1,fp)>0) cnt[c]++;//��ÿ���ַ������Ա��ڽ���
	for (int i = 0; i < 256; i++)//ֻ�����ļ��г��ֹ����ַ�����
	{
		if (cnt[i])
		{
			new_cnt[n] = cnt[i];
			num[i] = n;//����i�ı��
			c_num[n] = i;//���±��Ϊn���ַ����ĸ�
			n++;
		}
	}
	

	HuffmanTree HT;
	int root = Build(HT, new_cnt, n);
	cout << root << endl;
	char codes[260][20],s[20];//���ڴ�ÿ���ַ���Huffman����
	Coding(HT,codes,root,s,0);
//	for (int i = 0; i < n; i++)
//		cout << codes[i] << endl;
	FILE* fp_com = fopen("compressed.txt", "wb");
	FILE* fp_code = fopen("code.txt", "w");
//	FILE* fp1 = fopen("codefile.txt", "w");
	for (int i = 0; i < n; i++)
		fprintf(fp_code, "%c:%s\n", c_num[i], codes[i]);
	fclose(fp_code);
	unsigned char zero = 0,temp_c;
	fwrite(&zero, sizeof(unsigned char), 1, fp_com);
	fwrite(&zero, sizeof(unsigned char), 1, fp_com);//д����0��ȥռλ
	rewind(fp);
	char temp_s[10];//���ڴ�ÿһ��д��İ�λ
	int temp_len = 0;
	while(fread(&c, sizeof(unsigned char), 1, fp) > 0)
	{
//		fprintf(fp1, "%s", codes[num[c]]);
		for (int i = 0; codes[num[c]][i]; i++)
		{

			temp_s[temp_len++] = codes[num[c]][i];
			if (temp_len == 8)
			{
				temp_s[temp_len] = '\0';
				Str2Bin(temp_s,temp_c);
				fwrite(&temp_c, sizeof(unsigned char),1,fp_com);
				temp_len = 0;
			}
		}
	}
	for (int i = temp_len; i < 8; i++)
		temp_s[i] = '0';
	temp_s[8] = '\0';
	temp_c = 8-temp_len;//��0�ĸ���
	rewind(fp_com);
	fwrite(&temp_c, sizeof(unsigned char), 1, fp_com);
	Str2Bin(temp_s, temp_c);//��temp_sת��temp_c
	fwrite(&temp_c, sizeof(unsigned char), 1, fp_com);
	fclose(fp_com);
	fclose(fp);
	cout << "Decode or not(y/n):" << endl;
	getchar();
	char ch = getchar();
	if (ch == 'y')
	{
		int u=root;
		fp_com = fopen("compressed.txt", "rb");
		fp = fopen("decode.bin", "wb");
		fread(&zero, sizeof(unsigned char), 1, fp_com);//����zero����Ǻ��油0�ĸ���
		fread(&temp_c, sizeof(unsigned char), 1, fp_com);//�������ǲ�0������һ���ַ�
		while (fread(&c,sizeof(unsigned char),1,fp_com)>0)
		{
			Bin2Str(temp_s, c);
			for (int i = 0; i < 8; i++)
			{

				if (temp_s[i] == '0')
					u = HT[u].lchild;
				else
					u = HT[u].rchild;
				if (!HT[u].lchild)
				{
					fwrite(&c_num[u-1], sizeof(unsigned char), 1, fp);
					u = root;
				}
			}
			
		}
		Bin2Str(temp_s, temp_c);
		for (int i = 0; i < 8 - zero; i++)
		{
			if (!HT[u].lchild)
			{
				fwrite(&c_num[u-1], sizeof(unsigned char), 1, fp);
				u = root;
			}
			if (temp_s[i] == '0')
				u = HT[u].lchild;
			else
				u = HT[u].rchild;
		}
	}
	return 0;
}