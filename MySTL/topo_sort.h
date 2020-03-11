#pragma once
#include <iostream>
#include "graph.h"
using namespace std;

void topo(Graph_List graph){
	Queue<Graph_List::Vertex> s;//设定一个栈用于暂存入度为0的顶点，O(n)初始化，每输出一个顶点对其邻接点的入度-1的时候顺便O(1)判断是否入度为0，是的话就入栈，根本就不需要n次排序O(n*nlogn)那么复杂！况且就算真的要求最小值，那也不用整个排列啊，直接二分O(logn)不就好了
	int cnt = 0;//设置一个变量用于计数已输出的顶点数，最后O(1)判断一下与图中的顶点总数是否相等就知道排序完没有了，根本不需要设置visit[]数组最后还要O(n)判断有没有为0的这么复杂！
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
		cout << "拓扑排序完毕" << endl;
	else
		cout << "无法完成拓扑排序，原因是图中有环" << endl;
}