#pragma once
#include <memory>//内存头文件，包含allocate<T>类，可用于内存分配管理
#include "algorithm.h"
using namespace std;

template <class T> class Vector
{
public:
	typedef T* iterator;//T类型的迭代器
	typedef const T* const_iterator;//T类型的常量迭代器
	typedef size_t size_type;//描述容器长度的数据类型
	typedef T value_type;//容器的元素值类型T
	typedef T& reference;//T类型的引用
	typedef const T& const_reference;//T类型的常量引用

	size_type size() const { return avail - data; }//返回容器长度
	iterator begin() { return data; }//返回容器的首迭代器
	const_iterator begin() const { return data; }//返回容器的首常量迭代器
	iterator end() { return avail; }//返回容器的尾迭代器
	const_iterator end() const { return avail; }//返回容器的尾常量迭代器
	bool empty() { return data == avail; }//判断容器是否为空
	void clear() { uncreate(); }//清空容器

	Vector() { create(); }//构造函数，构造一个空的Vector类对象
	explicit Vector(size_type n, const T& t = T()) { create(n, t); }//构造函数，构造一个长度为n，各元素初始化值为T类型的空(t=T())的Vector类对象
	Vector(const Vector& v) { create(v.begin(), v.end()); }//复制构造函数
	Vector& operator=(const Vector& rhs)//赋值运算符函数
	{
		if (&rhs != this)//判断是否进行自我赋值
		{
			uncreate();//删除运算符左侧的对象
			create(rhs.begin(), rhs.end());//从右侧复制元素到左侧
		}
		return *this;//返回赋值后的左操作数或未进行自我赋值的原左操作数
	}
	~Vector() { uncreate(); }//析构函数

	T& operator[] (size_type i) { return data[i]; }//[]运算符函数
	const T& operator[] (size_type i) const { return data[i]; }//常量[]运算符函数

	void push_back(const T&);//向容器末端添加一个T类型值为t的元素
	void pop_back();//删除容器末端元素
	template <class Iter> void insert(Iter, const T&);//在指定位置之后插入元素
	template <class Iter> iterator insert(Iter, Iter, iterator);//将从迭代器i到迭代器j中的元素插入到Vector类迭代器指向的位置后面，返回插入的这段元素的最后一个元素的后面一个位置
	iterator erase(iterator);//删除指定元素
	iterator erase(iterator, iterator);//删除容器中迭代器i到j的所有元素，并返回被删除的最后一个元素后面一个元素的迭代器
	iterator find(const T&);//查找指定值，返回找到的第一个迭代器，若找不到，则返回末迭代器
	void assign(T*, T*);//将一个数组的值赋给一个Vector类型的对象

private:
	iterator data;//容器首元素地址
	iterator avail;//容器（已初始化）末元素的后面一个元素的地址
	iterator limit;//分配的内存（未初始化）中末元素的后面一个元素的地址

	std::allocator<T> alloc;//控制内存分配的对象

	void create();//创建一个空对象
	void create(size_type, const T&);//创建一个长度为n，各元素初始化值为T类型的val的对象
	void create(const_iterator, const_iterator);//创建一个长度为第二个迭代器减去第一个迭代器的对象，并将第一个迭代器到第二个迭代器之间的元素复制给这个对象
	void uncreate();//删除数组中的元素并释放其占用的内存
	void grow();//重新分配原来两倍大小的内存空间
	void unchecked_append(const T&);//在已初始化的末元素之后再初始化一个元素
};

template <class T>
void Vector<T>::create()
{
	data = avail = limit = 0;
	return;
}

template <class T>
void Vector<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);//分配能储存n个T类型对象的内存，data为其首地址
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);//将迭代器data到limit之间的所有元素初始化为val
	return;
}

template <class T>
void Vector<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i);//分配能储存j-i个T类型对象的内存，data为其首地址
	limit = avail = uninitialized_copy(i, j, data);//将迭代器i到j之间的所有元素复制到data指向的内存后面，limit和avail为这段内存最后一个元素后面一个元素的地址
	return;
}

template <class T>
void Vector<T>::uncreate()
{
	if (data)
	{
		iterator it = avail;//以相反的顺序删除构造函数生成的元素
		while (it != data)
			alloc.destroy(--it);//删除迭代器it指向的元素
		alloc.deallocate(data, limit - data);//释放以data为首地址，limit-data为长度的内存空间
	}
	data = limit = avail = 0;//重置迭代器以表明Vector类对象为空
	return;
}

template <class T>
void Vector<T>::grow()
{
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));//new_size的长度取2*(limit-data)和与limit-data同类型的1的最大值
	iterator new_data = alloc.allocate(new_size);//分配能储存new_size个T类型对象的内存，new_data为其首地址
	iterator new_avail = uninitialized_copy(data, avail, new_data);//将迭代器data到avail之间的所有元素复制到new_data指向的内存后面，new_avail为这段内存最后一个元素后面一个元素的地址
	uncreate();//删除并释放原来的内存空间
	data = new_data;//新首地址
	avail = new_avail;//新末元素（已初始化）的地址
	limit = data + new_size;//新分配的内存（未初始化）中末元素的后面一个元素的地址
	return;
}

template <class T>
void Vector<T>::unchecked_append(const T& val)
{
	alloc.construct(avail++, val);//将迭代器avail指向的元素（即原来的末元素后面一个元素）初始化为val，并将avail后移一个位置
	return;
}

template <class T>
void Vector<T>::push_back(const T& t)
{
	if (avail == limit)//容量已满
		grow();//分配更多未初始化的内存空间
	unchecked_append(t);//将第一个未初始化的内存空间初始化
	return;
}

template <class T>
void Vector<T>::pop_back()
{
	alloc.destroy(avail);
	avail--;
	return;
}

template <class T> template <class Iter>
void typename Vector<T>::insert(Iter i, const T& t)
{
	if (i == avail)
		push_back(t);
	else
	{
		size_type new_size = (avail - data) + 1;//重新定义长度比原来多1的内存空间
		iterator new_data = alloc.allocate(new_size);//分配新内存
		iterator d = uninitialized_copy(data, i + 1, new_data);//复制插入位置之前的元素
		alloc.construct(d++, t);//插入指定元素
		iterator new_avail = uninitialized_copy(i + 1, avail, d);//复制插入位置之后的元素
		uncreate();//删除并释放原来的内存
		data = new_data;//重置首地址！
		limit = avail = new_avail;//重置尾地址！
	}
	return;
}

template <class T> template <class Iter>//注意这里不能写成template <class T, class Iter>！！
typename Vector<T>::iterator typename Vector<T>::insert(Iter i, Iter j, iterator c)
{
	if (c == avail)
	{
		for (Iter it = i; it != j; it++)
			push_back(*it);
		return avail;
	}
	size_type new_size = (avail - data) + (j - i);//注意！j-i要加（）！不能添加两个指针！
	iterator new_data = alloc.allocate(new_size);//分配新内存
	iterator d = uninitialized_copy(data, c + 1, new_data);//复制插入位置之前的元素
	iterator e = uninitialized_copy(i, j, d);//复制插入的元素
	iterator new_avail = uninitialized_copy(c + 1, avail, e);//复制插入位置之后的元素
	uncreate();//删除并释放原来的内存
	data = new_data;//重置首地址！
	limit = avail = new_avail;//重置尾地址！
	return e;
}

template <class T>
typename Vector<T>::iterator typename Vector<T>::erase(iterator i)
{
	if (i == data)
	{
		alloc.destroy(i);
		avail = uninitialized_copy(i + 1, avail, i);
		data = i;
	}
	else if (i == avail)
	{
		alloc.destroy(i);
		avail--;
	}
	else
	{
		if (i)
			alloc.destroy(i);//删除迭代器i指向的元素，但不释放内存
		avail = uninitialized_copy(i + 1, avail, i);//将从迭代器i+1到j之间的元素复制到以i为首的内存中,avail指向最后一个元素后面的元素
	}
	return i;//返回被删除元素的后面一个元素的迭代器
}

template <class T>
typename Vector<T>::iterator typename Vector<T>::erase(iterator i, iterator j)
{
	if (i)
	{
		iterator it = j;
		while (it != i)
			alloc.destroy(--it);//删除迭代器i到j的所有元素，但不释放内存
	}
	iterator new_avail = uninitialized_copy(j, avail, i);//将迭代器j到avail中的所有元素复制到以i为首的内存中，new_avail指向最后一个元素后面一个元素
	if (new_avail)
	{
		iterator it = avail;
		while (it != new_avail)
			alloc.destroy(--it);//删除迭代器new_avail到avail的所有元素，但不释放内存
	}
	avail = new_avail;//重置末元素迭代器!
	return i;
}

template <class T>
typename Vector<T>::iterator typename Vector<T>::find(const T& t)
{
	iterator it = data;
	while (it != avail)
	{
		if (*it == t)
			break;
		it++;
	}
	return it;
}

template <class T>
void Vector<T>::assign(T* head, T* tail)
{
	for (iterator it = head; it != tail; it++)
		push_back(*it);
	return;
}