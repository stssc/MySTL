#pragma once
using namespace std;

#define Status int
constexpr auto TRUE = 1;
constexpr auto FALSE = 0;

template <class T> struct Node
{
	T data;
	Node *left, *right, *parent;
};

template <class T> class SortTree
{
private:
	bool empty() { return root == nullptr; }

public:
	SortTree() {}//���캯��

	Node<T> *root;//�����

	Node<T>* find(Node<T>*, const T&);//����ָ��Ԫ��
	Status insert(Node<T>*, const T&);//����ָ��Ԫ��
	Status erase(const T&);//ɾ��ָ��Ԫ��
	void print(Node<T>*);//��������������������
};

template <class T> Node<T>* SortTree<T>::find(Node<T>* node, const T& t)
{
	if (node == nullptr)
		return nullptr;
	else {
		if (t == node->data)
			return node;
		else if (node->left != nullptr && t < node->data)
			return find(node->left, t);
		else if (node->right != nullptr && t > node->data)
			return find(node->right, t);
		else
			return nullptr;
	}
}

template <class T> Status SortTree<T>::insert(Node<T>* node, const T& t)
{
	if (empty())//����
	{
		Node<T> *root = new Node<T>;
		root->parent = root->left = root->right = nullptr;
		root->data = t;
		this->root = root;//��������㣡
		return TRUE;
	}
	else if (node->left != nullptr && node->right == nullptr)
	{
		if (t > node->data)
		{
			Node<T> *child = new Node<T>;
			child->data = t;
			child->left = child->right = nullptr;
			child->parent = node;
			node->right = child;
			return TRUE;
		}
		else if (t < node->data)
			return insert(node->left, t);
		else
			return FALSE;
	}
	else if (node->left == nullptr && node->right != nullptr)
	{
		if (t < node->data)
		{
			Node<T> *child = new Node<T>;
			child->data = t;
			child->left = child->right = nullptr;
			child->parent = node;
			node->left = child;
			return TRUE;
		}
		else if (t > node->data)
			return insert(node->right, t);
		else
			return FALSE;
	}
	else if (node->left == nullptr && node->right == nullptr)
	{
		if (t < node->data)
		{
			Node<T> *left = new Node<T>;
			left->data = t;
			left->left = left->right = nullptr;
			left->parent = node;
			node->left = left;
			return TRUE;
		}
		else if (t > node->data)
		{
			Node<T> *right = new Node<T>;
			right->data = t;
			right->left = right->right = nullptr;
			right->parent = node;
			node->right = right;
			return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
		if (t < node->data)
			return insert(node->left, t);
		else if (t > node->data)
			return insert(node->right, t);
		else
			return FALSE;
	}
}

template <class T> Status SortTree<T>::erase(const T& t)
{
	Node<T> *p = find(root, t);
	if (p == nullptr)
		return FALSE;
	else if (p->parent == nullptr)//ɾ��������Ҫ���ø����
	{
		if (p->left == nullptr && p->right == nullptr)
			root = nullptr;
		else if (p->left != nullptr && p->right == nullptr)
		{
			p->left->parent = nullptr;
			root = p->left;
		}
		else if (p->left == nullptr && p->right != nullptr)
		{
			p->right->parent = nullptr;
			root = p->right;
		}
		else
		{
			//������ʵ�������ϲ������������������ϲ��������������ԣ�������Ǽ�һ��ƽ�⻯���Ż������������񲢲鼯�����߲����߸�����ȵȣ��������
			Node<T> *r = p->right;
			while (r->left)
				r = r->left;
			p->left->parent = r;
			r->left = p->left;
			p->right->parent = nullptr;
			root = p->right;
		}
	}
	else if (p->left == nullptr && p->right == nullptr)//Ҷ���ֱ��ɾ��
	{
		if (p == p->parent->left)
			p->parent->left = nullptr;
		else
			p->parent->right = nullptr;
	}
	else if (p->left != nullptr && p->right == nullptr)//������
	{
		p->left->parent = p->parent;
		if (p == p->parent->left)
			p->parent->left = p->left;
		else
			p->parent->right = p->left;
	}
	else if (p->left == nullptr && p->right != nullptr)//���Һ���
	{
		p->right->parent = p->parent;
		if (p == p->parent->left)
			p->parent->left = p->right;
		else
			p->parent->right = p->right;
	}
	else//����������С�����ж�Ů
	{
		if (p = p->parent->left) {
			p->right->parent = p->parent;
			p->parent->left = p->right;
			Node<T> *r = p->right;
			while (r->left)
				r = r->left;
			r->left = p->left;
			p->left->parent = r;
		}
		else {
			p->left->parent = p->parent;
			p->parent->right = p->left;
			Node<T> *r = p->left;
			while (r->right)
				r = r->right;
			r->right = p->right;
			p->right->parent = r;
		}
	}
	delete p;
	return TRUE;
}

template <class T> void SortTree<T>::print(Node<T>* root)
{
	if (root == nullptr)
		return;
	print(root->left);
	cout << root->data << " ";
	print(root->right);
}