#pragma once
using namespace std;

template <class T> struct Node//�����
{
	T data;//������
	Node<T> *prior, *next;//ǰ��ָ�룬���ָ��
};

template <class T> class List//������
{//���������ص��ǣ�����β��������β���������Ϊ�գ���β��������һ�������ݵĽ��ĺ���һ����㣬Ҳ����˵��������ͷβ����һ���ս�㣬�ֱ���end()��rend()ָ��Ľ�㣬��begin()��end()ָ����ǵ�һ����������Ľ�㣬
public:
	class next_iterator//�����������
	{
	public:
		next_iterator(Node<T> *p) { node = p; }//�������Ĺ��캯��������һ����㣬����һ��������

		next_iterator& operator++()//����ǰ��++�����
		{
			node = node->next;
			return *this;//���ص�����
		}
		next_iterator& operator--()//����ǰ��--�����
		{
			node = node->prior;
			return *this;//���ص�����
		}
		next_iterator operator++(int)//���غ���++�����
		{
			next_iterator temp(node);
			node = node->next;
			return temp;
		}
		next_iterator operator--(int)//���غ���--�����
		{
			next_iterator temp(node);
			node = node->prior;
			return temp;
		}
		next_iterator& operator+(int n)//���ö�Ԫ�����next_iterator+n
		{
			for (int i = 0; i < n; i++)
				node = node->next;
			return *this;
		}
		next_iterator& operator-(int n)//���ö�Ԫ�����next_iterator-n
		{
			for (int i = 0; i < n; i++)
				node = node->prior;
			return *this;
		}
		T operator*()//����ǰ��*�����
		{
			return node->data;//���ص�����ָ��Ľ���������
		}
		Node<T>* operator&()//����ǰ��&�����
		{
			return node;//���ص�����ָ��Ľ�㣬ע�ⷵ��ֵ���ͣ�(�ǵü�*)
		}
		bool operator==(const next_iterator& ni)//���ض�Ԫ�����==
		{
			return node == ni.node;
		}
		bool operator!=(const next_iterator& ni)//���ض�Ԫ�����!=
		{
			return node != ni.node;
		}

	private:
		Node<T> *node;//ÿһ��������ָ��һ�����
	};
	class prior_iterator//�����������
	{
	public:
		prior_iterator(Node<T> *p) { node = p; }//�������Ĺ��캯��������һ����㣬����һ��������

		prior_iterator& operator++()//����ǰ��++�����
		{
			node = node->prior;
			return *this;//���ص�����
		}
		prior_iterator& operator--()//����ǰ��--�����
		{
			node = node->next;
			return *this;//���ص�����
		}
		prior_iterator operator++(int)//���غ���++�����
		{
			prior_iterator temp(node);
			node = node->prior;
			return temp;
		}
		prior_iterator operator--(int)//���غ���--�����
		{
			prior_iterator temp(node);
			node = node->next;
			return temp;
		}
		prior_iterator& operator+(int n)//���ö�Ԫ�����prior_iterator+n
		{
			for (int i = 0; i < n; i++)
				node = node->prior;
			return *this;
		}
		prior_iterator& operator-(int n)//���ö�Ԫ�����prior_iterator-n
		{
			for (int i = 0; i < n; i++)
				node = node->next;
			return *this;
		}
		T operator*()//����ǰ��*�����
		{
			return node->data;//���ص�����ָ��Ľ���������
		}
		Node<T>* operator&()//����ǰ��&�����
		{
			return node;//���ص�����ָ��Ľ�㣬ע�ⷵ��ֵ���ͣ�(�ǵü�*)
		}
		bool operator==(const prior_iterator& ni)//���ض�Ԫ�����==
		{
			return node == ni.node;
		}
		bool operator!=(const prior_iterator& ni)//���ض�Ԫ�����!=
		{
			return node != ni.node;
		}

	private:
		Node<T> *node;//ÿһ��������ָ��һ�����
	};

	typedef size_t size_type;//���������ȵ���������

	next_iterator begin() { return next_iterator(first); }//��������ͷ���
	next_iterator end() { return next_iterator(last_next); }//��������β���
	prior_iterator rbegin() { return prior_iterator(last); }//��������ͷ���
	prior_iterator rend() { return prior_iterator(first_prior); }//��������β���
	const next_iterator begin() const { return next_iterator(first); }//����������ͷ���
	const next_iterator end() const { return next_iterator(last_next); }//����������β���
	const prior_iterator rbegin() const { return prior_iterator(last); }//����������ͷ���
	const prior_iterator rend() const { return prior_iterator(first_prior); }//����������β���
	bool empty() { return first == nullptr&&last == nullptr; }//�ж������Ƿ�Ϊ��
	void clear() //�������
	{
		Node<T> *t = first_prior->next;
		while (t != last_next)//ɾ��������������н�㲢�ͷ��ڴ�
		{
			first_prior->next = t->next;
			t->next->prior = first_prior;
			delete t;//�ͷ�ָ��t��ָ����ڴ棬����ɾ��ָ��t��
			t = first_prior->next;
		}
		first = last = nullptr;//����ͷβ��㣡
		return;
	}
	size_type size()//����������
	{
		if (empty())
			return 0;
		size_type n = 0;
		Node<T> *p = first;
		while (p != last_next)
		{
			n++;
			p = p->next;
		}
		return n;
	}

	List() { create(); }//���캯��
	List(const List& l) { create(l.begin(), l.end()); }//���ƹ��캯��
	List& operator=(const List& l)//��ֵ���������
	{
		if (this != &l)//�ж��Ƿ�������Ҹ�ֵ
		{
			clear();//ɾ����������Ķ���
			create(l.begin(), l.end());//���Ҳิ��Ԫ�ص����
		}
		return *this;//���ظ�ֵ������������δ�������Ҹ�ֵ��ԭ�������
	}
	~List() {}//��������

	void push_back(const T&);//������β��ӽ��
	void push_front(const T&);//������ͷ��ӽ��
	void pop_back();//ɾ��β���
	void pop_front();//ɾ��ͷ���
	T back() { return last->data; }//��ȡ����β���������
	T front() { return first->data; }//��ȡ����ͷ�������
	next_iterator find(const T&);//����ָ����㣬�����ؽ�����ڵ�λ��
	void insert(next_iterator, const T&);//��ָ��λ�ú������ӽ��
	void erase(next_iterator);//ɾ��ָ�����

private:
	Node<T> *first_prior, *first, *last, *last_next;//��һ����㣬��һ����������Ľ�㣬���һ����������Ľ�㣬���һ�����

	void create();//����һ��������
	void create(const next_iterator&, const next_iterator&);//���ӵ�һ�����������ڶ���������֮���Ԫ�ظ��Ƶ�һ���������У����ڸ��ƹ��캯������Ĳ�����const������create��������Ĳ���ҲӦ��const
};

template <class T> void List<T>::create()
{
	first_prior = new Node<T>;//������һ�����
	last_next = new Node<T>;//�������һ�����
	first_prior->prior = last_next->next = nullptr;
	//���Ҫ��ѭ������
	//first_prior->prior = last_next;
	//last_next->next = first_prior;
	first_prior->next = last_next;
	last_next->prior = first_prior;
	first = last = nullptr;//ͷ����β����ʼ��Ϊ��
	return;
}

template <class T> void List<T>::create(const next_iterator& i, const next_iterator& j)
{
	//�ȳ�ʼ��һ��������
	first_prior = new Node<T>;
	last_next = new Node<T>;
	first_prior->prior = last_next->next = nullptr;
	//���Ҫ��ѭ������
	//first_prior->prior = last_next;
	//last_next->next = first_prior;
	first_prior->next = last_next;
	last_next->prior = first_prior;
	//���Ƶ�����i��j�����н��
	for (next_iterator it = i; it != j; ++it)
	{
		Node<T> *n = new Node<T>;
		n->data = *it;
		n->prior = last_next->prior;
		n->next = last_next;
		last_next->prior->next = n;
		last_next->prior = n;
	}
	first = first_prior->next;//����ͷ��㣡
	last = last_next->prior;//����β��㣡
	return;
}

template <class T> void List<T>::push_back(const T& t)
{
	last_next->data = t;//�ȸ��յ�ĩ����������ֵ
	last = last_next;//����β��㣡
	Node<T> *n = new Node<T>;//�����µ�ĩ��㣬������Ϊ��
	n->next = nullptr;
	n->prior = last_next;
	last_next->next = n;
	last_next = n;//����ĩ��㣡
	first = first_prior->next;//����ͷ��㣡����Ϊ����push_back����һ��������
	return;
}

template <class T> void List<T>::push_front(const T& t)
{
	first_prior->data = t;//�ȸ��յ��׽���������ֵ
	first = first_prior;//����ͷ��㣡
	Node<T> *n = new Node<T>;//�����µ��׽�㣬������Ϊ��
	n->prior = nullptr;
	n->next = first_prior;
	first_prior->prior = n;
	first_prior = n;//�����׽�㣡
	last = last_next->prior;//����β��㣡����Ϊ����push_front����һ��������
	return;
}

template <class T> void List<T>::pop_back()
{
	Node<T> *t = last;
	t->prior->next = t->next;
	t->next->prior = t->prior;
	delete t;//ɾ��β���
	last = last_next->prior;//����β���
	return;
}

template <class T> void List<T>::pop_front()
{
	Node<T> *t = first;
	t->prior->next = t->next;
	t->next->prior = t->prior;
	delete t;//ɾ��ͷ���
	first = first_prior->next;//����ͷ���
	return;
}

template <class T> typename List<T>::next_iterator typename List<T>::find(const T& t)//����typename�ᱨ���������Ʋ�������
{
	next_iterator it = (*this).begin();
	while (it != (*this).end())
	{
		if (*it == t)
			break;//�����ҵ���һ��ƥ���λ��ʱ���ص�����
		it++;
	}
	return it;//����������û�в��ҵ�ƥ��Ԫ�أ��򷵻�β������
}

template <class T> void List<T>::insert(next_iterator i, const T& t)//�������i���������
{
	if (i == (*this).end() - 1)
		push_back(t);
	else
	{
		Node<T> *n = new Node<T>;
		n->data = t;
		n->next = (&i)->next;
		n->prior = &i;
		(&i)->next->prior = n;
		(&i)->next = n;
	}
	return;
}

template <class T> void List<T>::erase(next_iterator i)//ɾ��������iָ��Ľ��
{
	if (i == (*this).begin())
		pop_front();
	else if (i == (*this).end() - 1)
		pop_back();
	else
	{
		Node<T> *t = &i;
		t->prior->next = t->next;
		t->next->prior = t->prior;
		delete t;
	}
	return;
}