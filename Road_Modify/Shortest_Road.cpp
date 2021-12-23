#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#define INF 1<<30
#define MAX_VERTEX_NUM 25000000 //����2500000����
#define HEAP_SIZE 60000000
#define swap(a,b) Node temp =a;a=b;b=temp
int g_flag = 0;
unsigned char num[2], i = 0;

struct Node
{
	int m_u, m_dist;//��m_��ͷ��ʾ��Ա
};

	Node heap[HEAP_SIZE];
	int heap_size = 0;
	void push(Node elm)
	{
		heap[++heap_size] = elm;
		int now = heap_size, next;
		while (now > 1)
		{
			next = now >> 1;//next��now�ĸ��׽�㣬Ӧ��С�ڵ���now
			if (heap[next].m_dist <= heap[now].m_dist)//����Ҫ��
				return;
			swap(heap[next], heap[now]);
			now = next;
		}
	}
	Node top()
	{
		Node res = heap[1];
		heap[1] = heap[heap_size--];
		int now = 1, next;
		while ((now << 1) <= heap_size)//�ж�now�Ƿ�������
		{
			next = now << 1;
			if (next < heap_size && heap[next + 1].m_dist < heap[next].m_dist)
				next++;
			//�ҳ�now�������������С��һ��
			if (heap[now].m_dist <= heap[next].m_dist)//����Ҫ��
				return res;
			swap(heap[now], heap[next]);//���򽫶��߽���
			now = next;
		}
		return res;
	}

unsigned int src, dst, w;// , cnt = 0;
//ͼ���ڽӱ��ʾ

struct Edge
{
	int adjvex, weight, next;
};
Edge e[HEAP_SIZE];
int con_num[MAX_VERTEX_NUM] = { 0 },len=0;//����Ϊi�ĵ���G.vertices�ж�Ӧ���±�
int number[MAX_VERTEX_NUM] = { 0 };
int head[MAX_VERTEX_NUM] = { 0 },cnt=0;
void add()
{
	int num_u = con_num[src];
	int num_v = con_num[dst];
	if (!num_u)
	{
		num_u = ++len;
		number[len] = src;
		con_num[src] = len;
	}
	if (!num_v)
	{
		num_v = ++len;
		number[len] = dst;
		con_num[dst] = len;
	}
	e[++cnt].adjvex = num_v;
	e[cnt].weight = w;
	e[cnt].next = head[num_u];
	head[num_u] = cnt;
}

int g_ans, g_path[MAX_VERTEX_NUM];

void Dijkstra()
{
	int s_ = con_num[src];
	int t_ = con_num[dst];
	Node temp = { s_,0 };
	push(temp);
	int d[MAX_VERTEX_NUM], vis[MAX_VERTEX_NUM] = { 0 };
	for (register int i = 1; i <= len; i++) d[i] = INF;
	d[s_] = 0;
	while (heap_size)
	{
		temp = top();
		int u = temp.m_u;
		if (vis[u])//֮ǰ���ӹ�
			continue;
		vis[u] = 1;
		for (int p=head[u];p;p=e[p].next)
		{
			int v = e[p].adjvex, w = e[p].weight;
			if (d[v] > d[u] + w)
			{
				d[v] = d[u] + w;
				g_path[v] = u;
				push(Node{ v, d[v] });
			}
		}
	}
	g_ans = d[t_];

}
FILE* fp;
void Print(int x)//���ڿ������ĳ�����������ڱ�������Ҫ���������Ϊ�������ʲ�����0�����
{
	if (!x) return;
	char c;
	c = x % 10 + 48;//48Ϊ'0'��ASCII��ֵ������Ϊ�����������ٶȣ�ֱ��д��48
	Print(x / 10);
	fwrite(&c, sizeof(char), 1, fp);
}
int main()
{

	unsigned long long  ull, temp_ull = (1 << 25)-1;
	double start = clock();
	//printf("%d\n", 15^15);
	fp = fopen("dist_modified.bin", "rb");
	//printf("1\n");
	while (1)
	{
		fread(&ull, sizeof(unsigned char), 7, fp);
		src = ull >> 25 ;
		dst = ull & temp_ull;
		fread(&w, sizeof(unsigned char), 3, fp);
		if (feof(fp)) break;
		add();
	}
	fclose(fp);
	printf("%d\n",len);
	double terminal = clock();
	printf("time = %.2lfms\n", terminal - start);
	scanf("%d%d", &src, &dst);
	start = clock();
	Dijkstra();
	terminal = clock();
	fp = fopen("ans.txt", "w");
	char c;
	fprintf(fp, "The shortest distance is %d.\n", g_ans);
	fprintf(fp, "The path is as follows:\n");
	int node = con_num[dst];
	while (node != con_num[src])
	{
		Print(number[node]);
		c = '<';
		fwrite(&c, sizeof(char), 1, fp);
		c = '-';
		fwrite(&c, sizeof(char), 1, fp);
		node = g_path[node];
	}
	Print(src);
	fclose(fp);
	
	printf("%.2lfms\n", terminal - start);
	return 0;
}