#pragma once

using namespace std;
#define QueueLength 10

template <class T> class CircularQueue{

public:
	CircularQueue() :head(0), tail(0) {}//构造函数
	~CircularQueue() {}//析构函数

	bool empty() { return head == tail; }//判断队列是否为空
	bool full() { return (tail + 1) % QueueLength == head; }//判断队列是否已满（为防和empty的判据混淆，规定队尾后一个位置（队头前一个位置）不放元素
	T front() { return q[head]; }//取队头元素
	T back() { return q[tail - 1]; }//取队尾元素
	void push(const T& t) {//队尾入队
		if (full()) {
			throw runtime_error("out of range");
		}
		else {
			q[tail] = t;
			tail = (tail + 1) % QueueLength;
		}
		return;
	}
	void pop() {//队头出队
		if (empty()) {
			throw runtime_error("out of range");
		}
		else {
			head = (head + 1) % QueueLength;
		}
		return;
	}
	void print() {//从队头到队尾输出整个队列（此接口仅供测试用）
		if (tail > head) {
			for (int i = head; i < tail; i++)
				cout << q[i] << " ";
		}
		else if (tail < head) {
			for (int i = head; i < QueueLength; i++)
				cout << q[i] << " ";
			for (int i = 0; i < tail; i++)
				cout << q[i] << " ";
		}
		cout << endl;
		return;
	}

private:
	T q[QueueLength];
	T head, tail;//队头及队尾后面一个位置的下标

};

