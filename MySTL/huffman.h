#pragma once
#include <queue>
#include "tree.h"

const int LEFT = -1, RIGHT = 1;

struct cmp {
	bool operator()(TreeNode* node1, TreeNode* node2) const {
		return node1->weight > node2->weight;//注意是">"，因为weight越大优先级越低(operator<)，也就是排在优先队列的越后面，越晚出队
	}
};

TreeNode* buildHuffmanTree(Vector<char> words, Vector<int> weights) {
	priority_queue<TreeNode*, deque<TreeNode*>, cmp> q;//权值越小越优先的优先队列
	for (int i = 0; i < words.size(); i++)
		q.push(new TreeNode(words[i], weights[i]));
	while (q.size() > 1) {
		TreeNode* left = q.top(); q.pop();
		TreeNode* right = q.top(); q.pop();
		q.push(new TreeNode(left->weight + right->weight, left, right));
	}
	if (q.size() == 1) {
		q.top()->printTree();
		return q.top();
	}
	else
		return nullptr;
}

void HuffmanEncode(TreeNode* node, vector<int> code, int dir) {
	if (node == nullptr) {
		if (!code.empty())
			code.pop_back();
		return;
	}
	if (dir == LEFT)
		code.push_back(0);
	else if (dir == RIGHT)
		code.push_back(1);
	if (node->left == nullptr && node->right == nullptr) {
		cout << node->word << "(" << node->weight << "):";
		for (int x : code)
			cout << x;
		cout << endl;
	}
	HuffmanEncode(node->left, code, LEFT);
	HuffmanEncode(node->right, code, RIGHT);
}