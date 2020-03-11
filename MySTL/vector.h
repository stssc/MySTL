#pragma once
#include <memory>//�ڴ�ͷ�ļ�������allocate<T>�࣬�������ڴ�������
#include "algorithm.h"
using namespace std;

template <class T> class Vector
{
public:
	typedef T* iterator;//T���͵ĵ�����
	typedef const T* const_iterator;//T���͵ĳ���������
	typedef size_t size_type;//�����������ȵ���������
	typedef T value_type;//������Ԫ��ֵ����T
	typedef T& reference;//T���͵�����
	typedef const T& const_reference;//T���͵ĳ�������

	size_type size() const { return avail - data; }//������������
	iterator begin() { return data; }//�����������׵�����
	const_iterator begin() const { return data; }//�����������׳���������
	iterator end() { return avail; }//����������β������
	const_iterator end() const { return avail; }//����������β����������
	bool empty() { return data == avail; }//�ж������Ƿ�Ϊ��
	void clear() { uncreate(); }//�������

	Vector() { create(); }//���캯��������һ���յ�Vector�����
	explicit Vector(size_type n, const T& t = T()) { create(n, t); }//���캯��������һ������Ϊn����Ԫ�س�ʼ��ֵΪT���͵Ŀ�(t=T())��Vector�����
	Vector(const Vector& v) { create(v.begin(), v.end()); }//���ƹ��캯��
	Vector& operator=(const Vector& rhs)//��ֵ���������
	{
		if (&rhs != this)//�ж��Ƿ�������Ҹ�ֵ
		{
			uncreate();//ɾ����������Ķ���
			create(rhs.begin(), rhs.end());//���Ҳิ��Ԫ�ص����
		}
		return *this;//���ظ�ֵ������������δ�������Ҹ�ֵ��ԭ�������
	}
	~Vector() { uncreate(); }//��������

	T& operator[] (size_type i) { return data[i]; }//[]���������
	const T& operator[] (size_type i) const { return data[i]; }//����[]���������

	void push_back(const T&);//������ĩ�����һ��T����ֵΪt��Ԫ��
	void pop_back();//ɾ������ĩ��Ԫ��
	template <class Iter> void insert(Iter, const T&);//��ָ��λ��֮�����Ԫ��
	template <class Iter> iterator insert(Iter, Iter, iterator);//���ӵ�����i��������j�е�Ԫ�ز��뵽Vector�������ָ���λ�ú��棬���ز�������Ԫ�ص����һ��Ԫ�صĺ���һ��λ��
	iterator erase(iterator);//ɾ��ָ��Ԫ��
	iterator erase(iterator, iterator);//ɾ�������е�����i��j������Ԫ�أ������ر�ɾ�������һ��Ԫ�غ���һ��Ԫ�صĵ�����
	iterator find(const T&);//����ָ��ֵ�������ҵ��ĵ�һ�������������Ҳ������򷵻�ĩ������
	void assign(T*, T*);//��һ�������ֵ����һ��Vector���͵Ķ���

private:
	iterator data;//������Ԫ�ص�ַ
	iterator avail;//�������ѳ�ʼ����ĩԪ�صĺ���һ��Ԫ�صĵ�ַ
	iterator limit;//������ڴ棨δ��ʼ������ĩԪ�صĺ���һ��Ԫ�صĵ�ַ

	std::allocator<T> alloc;//�����ڴ����Ķ���

	void create();//����һ���ն���
	void create(size_type, const T&);//����һ������Ϊn����Ԫ�س�ʼ��ֵΪT���͵�val�Ķ���
	void create(const_iterator, const_iterator);//����һ������Ϊ�ڶ�����������ȥ��һ���������Ķ��󣬲�����һ�����������ڶ���������֮���Ԫ�ظ��Ƹ��������
	void uncreate();//ɾ�������е�Ԫ�ز��ͷ���ռ�õ��ڴ�
	void grow();//���·���ԭ��������С���ڴ�ռ�
	void unchecked_append(const T&);//���ѳ�ʼ����ĩԪ��֮���ٳ�ʼ��һ��Ԫ��
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
	data = alloc.allocate(n);//�����ܴ���n��T���Ͷ�����ڴ棬dataΪ���׵�ַ
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);//��������data��limit֮�������Ԫ�س�ʼ��Ϊval
	return;
}

template <class T>
void Vector<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i);//�����ܴ���j-i��T���Ͷ�����ڴ棬dataΪ���׵�ַ
	limit = avail = uninitialized_copy(i, j, data);//��������i��j֮�������Ԫ�ظ��Ƶ�dataָ����ڴ���棬limit��availΪ����ڴ����һ��Ԫ�غ���һ��Ԫ�صĵ�ַ
	return;
}

template <class T>
void Vector<T>::uncreate()
{
	if (data)
	{
		iterator it = avail;//���෴��˳��ɾ�����캯�����ɵ�Ԫ��
		while (it != data)
			alloc.destroy(--it);//ɾ��������itָ���Ԫ��
		alloc.deallocate(data, limit - data);//�ͷ���dataΪ�׵�ַ��limit-dataΪ���ȵ��ڴ�ռ�
	}
	data = limit = avail = 0;//���õ������Ա���Vector�����Ϊ��
	return;
}

template <class T>
void Vector<T>::grow()
{
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));//new_size�ĳ���ȡ2*(limit-data)����limit-dataͬ���͵�1�����ֵ
	iterator new_data = alloc.allocate(new_size);//�����ܴ���new_size��T���Ͷ�����ڴ棬new_dataΪ���׵�ַ
	iterator new_avail = uninitialized_copy(data, avail, new_data);//��������data��avail֮�������Ԫ�ظ��Ƶ�new_dataָ����ڴ���棬new_availΪ����ڴ����һ��Ԫ�غ���һ��Ԫ�صĵ�ַ
	uncreate();//ɾ�����ͷ�ԭ�����ڴ�ռ�
	data = new_data;//���׵�ַ
	avail = new_avail;//��ĩԪ�أ��ѳ�ʼ�����ĵ�ַ
	limit = data + new_size;//�·�����ڴ棨δ��ʼ������ĩԪ�صĺ���һ��Ԫ�صĵ�ַ
	return;
}

template <class T>
void Vector<T>::unchecked_append(const T& val)
{
	alloc.construct(avail++, val);//��������availָ���Ԫ�أ���ԭ����ĩԪ�غ���һ��Ԫ�أ���ʼ��Ϊval������avail����һ��λ��
	return;
}

template <class T>
void Vector<T>::push_back(const T& t)
{
	if (avail == limit)//��������
		grow();//�������δ��ʼ�����ڴ�ռ�
	unchecked_append(t);//����һ��δ��ʼ�����ڴ�ռ��ʼ��
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
		size_type new_size = (avail - data) + 1;//���¶��峤�ȱ�ԭ����1���ڴ�ռ�
		iterator new_data = alloc.allocate(new_size);//�������ڴ�
		iterator d = uninitialized_copy(data, i + 1, new_data);//���Ʋ���λ��֮ǰ��Ԫ��
		alloc.construct(d++, t);//����ָ��Ԫ��
		iterator new_avail = uninitialized_copy(i + 1, avail, d);//���Ʋ���λ��֮���Ԫ��
		uncreate();//ɾ�����ͷ�ԭ�����ڴ�
		data = new_data;//�����׵�ַ��
		limit = avail = new_avail;//����β��ַ��
	}
	return;
}

template <class T> template <class Iter>//ע�����ﲻ��д��template <class T, class Iter>����
typename Vector<T>::iterator typename Vector<T>::insert(Iter i, Iter j, iterator c)
{
	if (c == avail)
	{
		for (Iter it = i; it != j; it++)
			push_back(*it);
		return avail;
	}
	size_type new_size = (avail - data) + (j - i);//ע�⣡j-iҪ�ӣ����������������ָ�룡
	iterator new_data = alloc.allocate(new_size);//�������ڴ�
	iterator d = uninitialized_copy(data, c + 1, new_data);//���Ʋ���λ��֮ǰ��Ԫ��
	iterator e = uninitialized_copy(i, j, d);//���Ʋ����Ԫ��
	iterator new_avail = uninitialized_copy(c + 1, avail, e);//���Ʋ���λ��֮���Ԫ��
	uncreate();//ɾ�����ͷ�ԭ�����ڴ�
	data = new_data;//�����׵�ַ��
	limit = avail = new_avail;//����β��ַ��
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
			alloc.destroy(i);//ɾ��������iָ���Ԫ�أ������ͷ��ڴ�
		avail = uninitialized_copy(i + 1, avail, i);//���ӵ�����i+1��j֮���Ԫ�ظ��Ƶ���iΪ�׵��ڴ���,availָ�����һ��Ԫ�غ����Ԫ��
	}
	return i;//���ر�ɾ��Ԫ�صĺ���һ��Ԫ�صĵ�����
}

template <class T>
typename Vector<T>::iterator typename Vector<T>::erase(iterator i, iterator j)
{
	if (i)
	{
		iterator it = j;
		while (it != i)
			alloc.destroy(--it);//ɾ��������i��j������Ԫ�أ������ͷ��ڴ�
	}
	iterator new_avail = uninitialized_copy(j, avail, i);//��������j��avail�е�����Ԫ�ظ��Ƶ���iΪ�׵��ڴ��У�new_availָ�����һ��Ԫ�غ���һ��Ԫ��
	if (new_avail)
	{
		iterator it = avail;
		while (it != new_avail)
			alloc.destroy(--it);//ɾ��������new_avail��avail������Ԫ�أ������ͷ��ڴ�
	}
	avail = new_avail;//����ĩԪ�ص�����!
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