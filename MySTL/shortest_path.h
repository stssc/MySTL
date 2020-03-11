#pragma once
#include "graph.h"

//Dijkstra算法——求源点到所有顶点的最短路径
int *visit, *disDijkstra, *pathDijkstra;//disDijkstra[i]:源点到顶点i的最短路径长度；pathDijkstra[i]:源点到顶点i的最短路径中顶点i的上一个顶点

void Dijkstra(Graph_Matrix graph, int source) {

	disDijkstra = new int[graph.vertexNum];
	for (int i = 0; i < graph.vertexNum; i++)
		disDijkstra[i] = INF;
	disDijkstra[source] = 0;

	visit = new int[graph.vertexNum];
	memset(visit, 0, graph.vertexNum * sizeof(int));
	visit[source] = 1;

	pathDijkstra = new int[graph.vertexNum];

	int minp = source;//没有负权
	int cnt = 1;//disDijkstra[source]=0已确定

	while (cnt < graph.vertexNum) {
		int min = INF;
		int p = minp;
		for (int i = 0; i < graph.vertexNum; i++) {
			if (!visit[i]) {//1到2的最短路径要么就是现在的1->2，要么就是1->其他点->2，但是1->其他点这段的距离就比直接1->2还要长了，那1->其他点+其他点->2的总路径长肯定直接大于1->2，所以最短路径只能是当前的1->2
				//松弛
				if (disDijkstra[p] + graph.adjMatrix[p][i] < disDijkstra[i]) {
					disDijkstra[i] = disDijkstra[p] + graph.adjMatrix[p][i];
					pathDijkstra[i] = p;
				}
				//一边寻找新的min
				if (disDijkstra[i] < min) {
					min = disDijkstra[i];
					minp = i;
				}
			}
		}
		visit[minp] = 1;////1到2的最短路径要么就是现在的1->2，要么就是1->其他点->2，但是1->其他点这段的距离就比直接1->2还要长了，那1->其他点+其他点->2的总路径长肯定直接大于1->2，所以最短路径只能是当前的1->2
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



//SPFA算法——求源点到所有顶点的最短路径
int *disSPFA, *pathSPFA;//disSPFA[i]:源点到点i的最短路径长度；pathSPFA[i]:源点到点i的最短路径中点i的上一个点

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



//Floyd算法——求图中每一对顶点之间的最短路径
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