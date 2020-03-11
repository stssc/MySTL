#pragma once
#include "vector.h"

template <class T> class Queue
{
public:
	typedef size_t size_type;

	size_type size() { return que.size(); }

	Queue() {}//构造函数
	~Queue() {}//析构函数

	T front() { return *(que.begin()); }//取队头元素
	T back() { return *(que.end() - 1); }//取队尾元素
	bool empty() { return que.empty(); }//判断队列是否为空
	void push(const T& t) { que.push_back(t); }//队尾入队
	void pop() { que.erase(que.begin()); }//队头出队

private:
	Vector<T> que;
};