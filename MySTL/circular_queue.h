#pragma once

using namespace std;
#define QueueLength 10

template <class T> class CircularQueue{

public:
	CircularQueue() :head(0), tail(0) {}//���캯��
	~CircularQueue() {}//��������

	bool empty() { return head == tail; }//�ж϶����Ƿ�Ϊ��
	bool full() { return (tail + 1) % QueueLength == head; }//�ж϶����Ƿ�������Ϊ����empty���оݻ������涨��β��һ��λ�ã���ͷǰһ��λ�ã�����Ԫ��
	T front() { return q[head]; }//ȡ��ͷԪ��
	T back() { return q[tail - 1]; }//ȡ��βԪ��
	void push(const T& t) {//��β���
		if (full()) {
			throw runtime_error("out of range");
		}
		else {
			q[tail] = t;
			tail = (tail + 1) % QueueLength;
		}
		return;
	}
	void pop() {//��ͷ����
		if (empty()) {
			throw runtime_error("out of range");
		}
		else {
			head = (head + 1) % QueueLength;
		}
		return;
	}
	void print() {//�Ӷ�ͷ����β����������У��˽ӿڽ��������ã�
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
	T head, tail;//��ͷ����β����һ��λ�õ��±�

};

