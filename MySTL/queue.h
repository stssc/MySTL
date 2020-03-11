#pragma once
#include "vector.h"

template <class T> class Queue
{
public:
	typedef size_t size_type;

	size_type size() { return que.size(); }

	Queue() {}//���캯��
	~Queue() {}//��������

	T front() { return *(que.begin()); }//ȡ��ͷԪ��
	T back() { return *(que.end() - 1); }//ȡ��βԪ��
	bool empty() { return que.empty(); }//�ж϶����Ƿ�Ϊ��
	void push(const T& t) { que.push_back(t); }//��β���
	void pop() { que.erase(que.begin()); }//��ͷ����

private:
	Vector<T> que;
};