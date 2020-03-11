#pragma once
#include <iostream>
#include "vector.h"
#include "list.h"
#include "queue.h"
using namespace std;

#define INF 999999
#define MAX_VERTEX_NUM 100

//邻接矩阵表示法
class Graph_Matrix {
private:
	int *visit;

public:
	int vertexNum, edgeNum;
	int adjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	void dfs(int);
	void bfs();
};

void Graph_Matrix::dfs(int id) {
	if (!visit[id]) {
		visit[id] = 1;
		cout << id << " ";
		for (int i = 0; i < (*this).vertexNum; i++)
			if ((*this).adjMatrix[id][i] < INF)
				dfs(i);
	}
}

void Graph_Matrix::bfs() {
	Queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int id = q.front();
		q.pop();
		if (!visit[id]) {
			visit[id] = 1;
			cout << id << " ";
			for (int i = 0; i < (*this).vertexNum; i++)
				if ((*this).adjMatrix[id][i] < INF)
					q.push(i);
		}
	}
	cout << endl;
}



//邻接表表示法
class Graph_List {
private:
	int *visit;

public:
	struct Edge {
		int adjVertex;
		int weight;
	};
	struct Vertex {
		int id;
		int inNum;//入度数
		List<Edge> adjList;
	};

	int vertexNum, edgeNum;
	Vector<Vertex> vertices;

	void dfs(int);
	void bfs();
};

void Graph_List::dfs(int id) {
	if (!visit[id]) {
		visit[id] = 1;
		cout << id << " ";
		for (Edge edge : (*this).vertices[id].adjList)
			dfs(edge.adjVertex);
	}
}

void Graph_List::bfs() {
	Queue<int> q;
	q.push((*this).vertices[0].id);
	while (!q.empty()) {
		int id = q.front();
		q.pop();
		if (!visit[id]) {
			visit[id] = 1;
			cout << id << " ";
			for (Edge edge : (*this).vertices[id].adjList)
				q.push(edge.adjVertex);
		}
	}
	cout << endl;
}