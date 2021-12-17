#pragma once
#define HEAP_SIZE 800000
struct Node
{
	int m_u, m_dist;//以m_开头表示成员
	bool operator < (const Node& a) const //重载小于号
	{
		return m_dist < a.m_dist;
	}
	bool operator == (const Node& a) const //重载等号
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
			next = now >> 1;//next是now的父亲结点，应当小于等与now
			if (heap[next] < heap[now] || heap[next] == heap[now])//符合要求
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
		while ((now << 1) <= heap_size)//判断now是否还有子树
		{
			next = now << 1;
			if (next < heap_size && heap[next + 1] < heap[next])
				next++;
			//找出now的两棵子树里更小的一棵
			if (heap[now] < heap[next] || heap[now] == heap[next])//符合要求
				return;
			swap(heap[now], heap[next]);//否则将二者交换
			now = next;
		}
		
	}
	bool empty()
	{
		return heap_size == 0;//若为0，则返回真
	}
};