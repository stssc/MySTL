#pragma once
#include <iostream>
#include "graph.h"
using namespace std;

void topo(Graph_List graph){
	Queue<Graph_List::Vertex> s;//�趨һ��ջ�����ݴ����Ϊ0�Ķ��㣬O(n)��ʼ����ÿ���һ����������ڽӵ�����-1��ʱ��˳��O(1)�ж��Ƿ����Ϊ0���ǵĻ�����ջ�������Ͳ���Ҫn������O(n*nlogn)��ô���ӣ����Ҿ������Ҫ����Сֵ����Ҳ�����������а���ֱ�Ӷ���O(logn)���ͺ���
	int cnt = 0;//����һ���������ڼ���������Ķ����������O(1)�ж�һ����ͼ�еĶ��������Ƿ���Ⱦ�֪��������û���ˣ���������Ҫ����visit[]�������ҪO(n)�ж���û��Ϊ0����ô���ӣ�
	for (Graph_List::Vertex v : graph.vertices) {
		if (v.inNum == 0) 
			s.push(v);
	}
	while (!s.empty()) {
		Graph_List::Vertex v = s.front(); s.pop();
		cout << v.id << " ";
		cnt++;
		for (Graph_List::Edge e : v.adjList) {
			Graph_List::Vertex* adjv = &graph.vertices[e.adjVertex];
			(*adjv).inNum--;
			if ((*adjv).inNum == 0) 
				s.push(*adjv);
		}
	}
	cout << endl;
	if (cnt == graph.vertexNum)
		cout << "�����������" << endl;
	else
		cout << "�޷������������ԭ����ͼ���л�" << endl;
}