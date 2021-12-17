#pragma once
#define HEAP_SIZE 800000
struct Node
{
	int m_u, m_dist;//��m_��ͷ��ʾ��Ա
	bool operator < (const Node& a) const //����С�ں�
	{
		return m_dist < a.m_dist;
	}
	bool operator == (const Node& a) const //���صȺ�
	{
		return m_dist == a.m_dist;
	}
};
void swap(Node& a, Node& b)
{
	Node temp = a;
	a = b;
	b = temp;
}
struct Heap
{
	Node heap[HEAP_SIZE];
	int heap_size = 0;
	void push(Node elm)
	{
		heap[++heap_size] = elm;
		int now = heap_size,next;
		while (now > 1)
		{
			next = now >> 1;//next��now�ĸ��׽�㣬Ӧ��С�ڵ���now
			if (heap[next] < heap[now] || heap[next] == heap[now])//����Ҫ��
				return;
			swap(heap[next],heap[now]);
			now = next;
		}
	}
	Node top()
	{
		return heap[1];
	}
	void pop()
	{
		heap[1] = heap[heap_size];
		heap_size--;
		int now = 1,next;
		while ((now << 1) <= heap_size)//�ж�now�Ƿ�������
		{
			next = now << 1;
			if (next < heap_size && heap[next + 1] < heap[next])
				next++;
			//�ҳ�now�������������С��һ��
			if (heap[now] < heap[next] || heap[now] == heap[next])//����Ҫ��
				return;
			swap(heap[now], heap[next]);//���򽫶��߽���
			now = next;
		}
		
	}
	bool empty()
	{
		return heap_size == 0;//��Ϊ0���򷵻���
	}
};