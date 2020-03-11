#pragma once
#include "graph.h"

//Dijkstra�㷨������Դ�㵽���ж�������·��
int *visit, *disDijkstra, *pathDijkstra;//disDijkstra[i]:Դ�㵽����i�����·�����ȣ�pathDijkstra[i]:Դ�㵽����i�����·���ж���i����һ������

void Dijkstra(Graph_Matrix graph, int source) {

	disDijkstra = new int[graph.vertexNum];
	for (int i = 0; i < graph.vertexNum; i++)
		disDijkstra[i] = INF;
	disDijkstra[source] = 0;

	visit = new int[graph.vertexNum];
	memset(visit, 0, graph.vertexNum * sizeof(int));
	visit[source] = 1;

	pathDijkstra = new int[graph.vertexNum];

	int minp = source;//û�и�Ȩ
	int cnt = 1;//disDijkstra[source]=0��ȷ��

	while (cnt < graph.vertexNum) {
		int min = INF;
		int p = minp;
		for (int i = 0; i < graph.vertexNum; i++) {
			if (!visit[i]) {//1��2�����·��Ҫô�������ڵ�1->2��Ҫô����1->������->2������1->��������εľ���ͱ�ֱ��1->2��Ҫ���ˣ���1->������+������->2����·�����϶�ֱ�Ӵ���1->2���������·��ֻ���ǵ�ǰ��1->2
				//�ɳ�
				if (disDijkstra[p] + graph.adjMatrix[p][i] < disDijkstra[i]) {
					disDijkstra[i] = disDijkstra[p] + graph.adjMatrix[p][i];
					pathDijkstra[i] = p;
				}
				//һ��Ѱ���µ�min
				if (disDijkstra[i] < min) {
					min = disDijkstra[i];
					minp = i;
				}
			}
		}
		visit[minp] = 1;////1��2�����·��Ҫô�������ڵ�1->2��Ҫô����1->������->2������1->��������εľ���ͱ�ֱ��1->2��Ҫ���ˣ���1->������+������->2����·�����϶�ֱ�Ӵ���1->2���������·��ֻ���ǵ�ǰ��1->2
		cnt++;
		/*for (int i = 0; i < graph.vertexNum; i++)
			cout << disDijkstra[i] << " ";
		cout << endl;
		cout << "min=" << min << ",minp=" << minp << endl;*/
	}

	for (int i = 0; i < graph.vertexNum; i++)
		cout << disDijkstra[i] << " ";
	cout << endl;
	for (int i = 0; i < graph.vertexNum; i++)
		cout << pathDijkstra[i] << " ";
	cout << endl;
}



//SPFA�㷨������Դ�㵽���ж�������·��
int *disSPFA, *pathSPFA;//disSPFA[i]:Դ�㵽��i�����·�����ȣ�pathSPFA[i]:Դ�㵽��i�����·���е�i����һ����

void SPFA(Graph_List graph, int source) {
	pathSPFA = new int[graph.vertexNum];
	disSPFA = new int[graph.vertexNum];
	for (int i = 0; i < graph.vertexNum; i++)
		disSPFA[i] = INF;
	disSPFA[source] = 0;
	Queue<int> q;
	q.push(source);
	int *visit = new int[graph.vertexNum];
	memset(visit, 0, sizeof(int)*graph.vertexNum);
	visit[source] = 1;
	while (!q.empty()) {
		int i = q.front(); q.pop();
		visit[i] = 0;
		//for (Graph_List::Edge edge : graph.vertices[i].adjList) {
		for (List<Graph_List::Graph_List::Edge>::next_iterator it = graph.vertices[i].adjList.begin(); it != graph.vertices[i].adjList.end(); it++) {
			Graph_List::Edge edge = *it;
			if (disSPFA[i] + edge.weight < disSPFA[edge.adjVertex]) {
				disSPFA[edge.adjVertex] = disSPFA[i] + edge.weight;
				pathSPFA[edge.adjVertex] = i;
				if (!visit[edge.adjVertex]) {
					q.push(edge.adjVertex);
					visit[edge.adjVertex] = 1;
				}
			}
		}
	}
}



//Floyd�㷨������ͼ��ÿһ�Զ���֮������·��
int disFloyd[MAX_VERTEX_NUM][MAX_VERTEX_NUM], pathFloyd[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void Floyd(Graph_Matrix graph) {
	for (int i = 0; i < graph.vertexNum; i++) {
		for (int j = 0; j < graph.vertexNum; j++) {
			disFloyd[i][j] = graph.adjMatrix[i][j];
			if (disFloyd[i][j] < INF)
				pathFloyd[i][j] = i;
		}
	}
	for (int k = 0; k < graph.vertexNum; k++) {
		for (int i = 0; i < graph.vertexNum; i++) {
			for (int j = 0; j < graph.vertexNum; j++) {
				if (disFloyd[i][k] + disFloyd[k][j] < disFloyd[i][j]) {
					disFloyd[i][j] = disFloyd[i][k] + disFloyd[k][j];
					pathFloyd[i][j] = pathFloyd[k][j];
				}
			}
		}
	}
}