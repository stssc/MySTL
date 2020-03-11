#pragma once
#include <iostream>
#include "vector.h"
#include "queue.h"
using namespace std;

class TreeNode {
public:
	int weight;
	char word;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int weight) : weight(weight), left(nullptr), right(nullptr) {}
	TreeNode(char word, int weight) :word(word), weight(weight), left(nullptr), right(nullptr) {}
	TreeNode(int weight, TreeNode* left, TreeNode* right) :weight(weight), left(left), right(right) {}

	TreeNode* constructTree(Vector<int> pre, Vector<int> vin);
	void preOrderTraversal();
	void inOrderTraversal();
	void postOrderTraversal();
	void levelOrderTraversal();
	void printTree();
};

TreeNode* TreeNode::constructTree(Vector<int> pre, Vector<int> vin) {
	if (pre.size() == 0 || vin.size() == 0)//异常检测兼递归结束条件（左右子树都为空，叶子结点） 
		return nullptr;
	TreeNode *root = new TreeNode(pre[0]);
	int i;
	Vector<int> vinLeft;
	for (i = 0; i < vin.size(); i++) {
		if (vin[i] == pre[0])
			break;
		else
			vinLeft.push_back(vin[i]);
	}
	if (i == vin.size())//中序遍历中找不到前序遍历的根结点，说明输入错误，二叉树无解
		return nullptr;
	Vector<int> vinRight;
	while (i < vin.size() - 1)
		vinRight.push_back(vin[++i]);//注意是++i不是i++，不要把根结点也放进去
	Vector<int> preLeft, preRight;
	for (i = 1; i < pre.size(); i++) {
		if (find(vinLeft.begin(), vinLeft.end(), pre[i]) != vinLeft.end())
			preLeft.push_back(pre[i]);
		else
			break;
	}
	if (i != 1 + vinLeft.size())//二叉树无解
		return nullptr;
	while (i < pre.size()) {
		if (find(vinRight.begin(), vinRight.end(), pre[i]) != vinRight.end())
			preRight.push_back(pre[i++]);
		else
			break;
	}
	if (i < pre.size())//二叉树无解
		return nullptr;
	root->left = constructTree(preLeft, vinLeft);
	root->right = constructTree(preRight, vinRight);
	return root;
}

void TreeNode::preOrderTraversal() {
	if (this == nullptr)
		return;
	cout << this->weight << " ";
	this->left->preOrderTraversal();
	this->right->preOrderTraversal();
}

void TreeNode::inOrderTraversal() {
	if (this == nullptr)
		return;
	this->left->inOrderTraversal();
	cout << this->weight << " ";
	this->right->inOrderTraversal();
}

void TreeNode::postOrderTraversal() {
	if (this == nullptr)
		return;
	this->left->postOrderTraversal();
	this->right->postOrderTraversal();
	cout << this->weight << " ";
}

void TreeNode::levelOrderTraversal() {
	if (this == nullptr)
		return;
	Queue<TreeNode*> q;
	q.push(this);
	while (!q.empty()) {
		TreeNode *node = q.front();
		q.pop();
		cout << node->weight << " ";
		if (node->left != nullptr)
			q.push(node->left);
		if (node->right != nullptr)
			q.push(node->right);
	}
	cout << endl;
}

void TreeNode::printTree() {
	preOrderTraversal();
	cout << endl;
	inOrderTraversal();
	cout << endl;
	postOrderTraversal();
	cout << endl;
	levelOrderTraversal();
}