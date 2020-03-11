#pragma once
using namespace std;

template <class T> struct Node//结点类
{
	T data;//数据域
	Node<T> *prior, *next;//前驱指针，后继指针
};

template <class T> class List//链表类
{//这个链表的特点是，正向尾结点和逆向尾结点数据域都为空，即尾结点是最后一个有数据的结点的后面一个结点，也就是说整个链表头尾各有一个空结点，分别是end()和rend()指向的结点，而begin()和end()指向的是第一个有数据域的结点，
public:
	class next_iterator//正向迭代器类
	{
	public:
		next_iterator(Node<T> *p) { node = p; }//带参数的构造函数，传入一个结点，构造一个迭代器

		next_iterator& operator++()//重载前置++运算符
		{
			node = node->next;
			return *this;//返回迭代器
		}
		next_iterator& operator--()//重载前置--运算符
		{
			node = node->prior;
			return *this;//返回迭代器
		}
		next_iterator operator++(int)//重载后置++运算符
		{
			next_iterator temp(node);
			node = node->next;
			return temp;
		}
		next_iterator operator--(int)//重载后置--运算符
		{
			next_iterator temp(node);
			node = node->prior;
			return temp;
		}
		next_iterator& operator+(int n)//重置二元运算符next_iterator+n
		{
			for (int i = 0; i < n; i++)
				node = node->next;
			return *this;
		}
		next_iterator& operator-(int n)//重置二元运算符next_iterator-n
		{
			for (int i = 0; i < n; i++)
				node = node->prior;
			return *this;
		}
		T operator*()//重载前置*运算符
		{
			return node->data;//返回迭代器指向的结点的数据域
		}
		Node<T>* operator&()//重载前置&运算符
		{
			return node;//返回迭代器指向的结点，注意返回值类型！(记得加*)
		}
		bool operator==(const next_iterator& ni)//重载二元运算符==
		{
			return node == ni.node;
		}
		bool operator!=(const next_iterator& ni)//重载二元运算符!=
		{
			return node != ni.node;
		}

	private:
		Node<T> *node;//每一个迭代器指向一个结点
	};
	class prior_iterator//逆向迭代器类
	{
	public:
		prior_iterator(Node<T> *p) { node = p; }//带参数的构造函数，传入一个结点，构造一个迭代器

		prior_iterator& operator++()//重载前置++运算符
		{
			node = node->prior;
			return *this;//返回迭代器
		}
		prior_iterator& operator--()//重载前置--运算符
		{
			node = node->next;
			return *this;//返回迭代器
		}
		prior_iterator operator++(int)//重载后置++运算符
		{
			prior_iterator temp(node);
			node = node->prior;
			return temp;
		}
		prior_iterator operator--(int)//重载后置--运算符
		{
			prior_iterator temp(node);
			node = node->next;
			return temp;
		}
		prior_iterator& operator+(int n)//重置二元运算符prior_iterator+n
		{
			for (int i = 0; i < n; i++)
				node = node->prior;
			return *this;
		}
		prior_iterator& operator-(int n)//重置二元运算符prior_iterator-n
		{
			for (int i = 0; i < n; i++)
				node = node->next;
			return *this;
		}
		T operator*()//重载前置*运算符
		{
			return node->data;//返回迭代器指向的结点的数据域
		}
		Node<T>* operator&()//重载前置&运算符
		{
			return node;//返回迭代器指向的结点，注意返回值类型！(记得加*)
		}
		bool operator==(const prior_iterator& ni)//重载二元运算符==
		{
			return node == ni.node;
		}
		bool operator!=(const prior_iterator& ni)//重载二元运算符!=
		{
			return node != ni.node;
		}

	private:
		Node<T> *node;//每一个迭代器指向一个结点
	};

	typedef size_t size_type;//描述链表长度的数据类型

	next_iterator begin() { return next_iterator(first); }//链表正向头结点
	next_iterator end() { return next_iterator(last_next); }//链表正向尾结点
	prior_iterator rbegin() { return prior_iterator(last); }//链表逆向头结点
	prior_iterator rend() { return prior_iterator(first_prior); }//链表逆向尾结点
	const next_iterator begin() const { return next_iterator(first); }//链表常量正向头结点
	const next_iterator end() const { return next_iterator(last_next); }//链表常量正向尾结点
	const prior_iterator rbegin() const { return prior_iterator(last); }//链表常量逆向头结点
	const prior_iterator rend() const { return prior_iterator(first_prior); }//链表常量逆向尾结点
	bool empty() { return first == nullptr&&last == nullptr; }//判断链表是否为空
	void clear() //清空链表
	{
		Node<T> *t = first_prior->next;
		while (t != last_next)//删除有数据域的所有结点并释放内存
		{
			first_prior->next = t->next;
			t->next->prior = first_prior;
			delete t;//释放指针t所指向的内存，但不删除指针t！
			t = first_prior->next;
		}
		first = last = nullptr;//重置头尾结点！
		return;
	}
	size_type size()//返回链表长度
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

	List() { create(); }//构造函数
	List(const List& l) { create(l.begin(), l.end()); }//复制构造函数
	List& operator=(const List& l)//赋值运算符函数
	{
		if (this != &l)//判断是否进行自我赋值
		{
			clear();//删除运算符左侧的对象
			create(l.begin(), l.end());//从右侧复制元素到左侧
		}
		return *this;//返回赋值后的左操作数或未进行自我赋值的原左操作数
	}
	~List() {}//析构函数

	void push_back(const T&);//向链表尾添加结点
	void push_front(const T&);//向链表头添加结点
	void pop_back();//删除尾结点
	void pop_front();//删除头结点
	T back() { return last->data; }//获取链表尾结点数据域
	T front() { return first->data; }//获取链表头结点数据
	next_iterator find(const T&);//查找指定结点，并返回结点所在的位置
	void insert(next_iterator, const T&);//在指定位置后面增加结点
	void erase(next_iterator);//删除指定结点

private:
	Node<T> *first_prior, *first, *last, *last_next;//第一个结点，第一个有数据域的结点，最后一个有数据域的结点，最后一个结点

	void create();//创建一个空链表
	void create(const next_iterator&, const next_iterator&);//将从第一个迭代器到第二个迭代器之间的元素复制到一个新链表中（由于复制构造函数传入的参数是const，所以create函数传入的参数也应是const
};

template <class T> void List<T>::create()
{
	first_prior = new Node<T>;//创建第一个结点
	last_next = new Node<T>;//创建最后一个结点
	first_prior->prior = last_next->next = nullptr;
	//如果要做循环链表
	//first_prior->prior = last_next;
	//last_next->next = first_prior;
	first_prior->next = last_next;
	last_next->prior = first_prior;
	first = last = nullptr;//头结点和尾结点初始化为空
	return;
}

template <class T> void List<T>::create(const next_iterator& i, const next_iterator& j)
{
	//先初始化一个空链表
	first_prior = new Node<T>;
	last_next = new Node<T>;
	first_prior->prior = last_next->next = nullptr;
	//如果要做循环链表
	//first_prior->prior = last_next;
	//last_next->next = first_prior;
	first_prior->next = last_next;
	last_next->prior = first_prior;
	//复制迭代器i到j的所有结点
	for (next_iterator it = i; it != j; ++it)
	{
		Node<T> *n = new Node<T>;
		n->data = *it;
		n->prior = last_next->prior;
		n->next = last_next;
		last_next->prior->next = n;
		last_next->prior = n;
	}
	first = first_prior->next;//重置头结点！
	last = last_next->prior;//重置尾结点！
	return;
}

template <class T> void List<T>::push_back(const T& t)
{
	last_next->data = t;//先给空的末结点的数据域赋值
	last = last_next;//重置尾结点！
	Node<T> *n = new Node<T>;//创建新的末结点，数据域为空
	n->next = nullptr;
	n->prior = last_next;
	last_next->next = n;
	last_next = n;//重置末结点！
	first = first_prior->next;//重置头结点！（因为可能push_back的是一个空链表）
	return;
}

template <class T> void List<T>::push_front(const T& t)
{
	first_prior->data = t;//先给空的首结点的数据域赋值
	first = first_prior;//重置头结点！
	Node<T> *n = new Node<T>;//创建新的首结点，数据域为空
	n->prior = nullptr;
	n->next = first_prior;
	first_prior->prior = n;
	first_prior = n;//重置首结点！
	last = last_next->prior;//重置尾结点！（因为可能push_front的是一个空链表）
	return;
}

template <class T> void List<T>::pop_back()
{
	Node<T> *t = last;
	t->prior->next = t->next;
	t->next->prior = t->prior;
	delete t;//删除尾结点
	last = last_next->prior;//重置尾结点
	return;
}

template <class T> void List<T>::pop_front()
{
	Node<T> *t = first;
	t->prior->next = t->next;
	t->next->prior = t->prior;
	delete t;//删除头结点
	first = first_prior->next;//重置头结点
	return;
}

template <class T> typename List<T>::next_iterator typename List<T>::find(const T& t)//不加typename会报错：依赖名称不是类型
{
	next_iterator it = (*this).begin();
	while (it != (*this).end())
	{
		if (*it == t)
			break;//当查找到第一个匹配的位置时返回迭代器
		it++;
	}
	return it;//若整个链表都没有查找到匹配元素，则返回尾迭代器
}

template <class T> void List<T>::insert(next_iterator i, const T& t)//向迭代器i后面插入结点
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

template <class T> void List<T>::erase(next_iterator i)//删除迭代器i指向的结点
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