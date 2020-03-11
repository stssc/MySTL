#pragma once

#include <iostream>
#include "vector.h"
using namespace std;

class String
{
	friend istream& operator>>(istream&, String&);//重载输入流，友元函数
public:
	typedef Vector<char>::size_type size_type;//描述字符串长度的数据类型
	typedef Vector<char>::iterator iterator;//String的迭代器
	typedef Vector<char>::const_iterator const_iterator;//String的常量迭代器

	size_type size() const { return data.size(); }//返回字符串长度
	iterator begin() { return data.begin(); }//返回字符串首迭代器
	iterator end() { return data.end(); }//返回字符串尾迭代器

	String() {}//构造函数
	String(size_type n, char c) :data(n, c) {}//构造由n个c字符组成的字符串
	String(const char* cp) { copy(cp, cp + strlen(cp), back_inserter(data)); }//复制构造函数（char *型参数）
	template<class Iter> String(Iter b, Iter e) { copy(b, e, back_inserter(data)); }//复制构造函数（String型参数）

	char& operator[](size_type i) { return data[i]; }//索引操作符函数
	const char& operator[](size_type i) const { return data[i]; }//索引操作符函数
	String& operator+=(const String& s) {//重载二元运算符+=
		copy(s.data.begin(), s.data.end(), back_inserter(data));//连接两个字符串
		return *this;
	}
	bool operator<(const String& s)//重载二元运算符<
	{
		size_type i = 0;
		while (i < data.size() && i < s.size())//两个都不能到头，否则会越界
		{
			if (data[i] > s[i])//遇到第一个data[i]>s[i]的则说明*this > s
				return false;
			if (data[i] < s[i])//遇到第一个data[i]<s[i]的则说明*this < s
				return true;
			i++;//一直相等则得一直往后比下去
		}
		if (data.size() < s.size())//s的前半部分都和*this相等，但s比较长，就比较大
			return true;
		else//*this >= s
			return false;
	}
	bool operator>(const String& s)//重载二元运算符>
	{
		size_type i = 0;
		while (i < data.size() && i < s.size())//两个都不能到头，否则会越界
		{
			if (data[i] < s[i])//遇到第一个data[i]<s[i]的则说明*this < s
				return false;
			if (data[i] > s[i])//遇到第一个data[i]>s[i]的则说明*this > s
				return true;
			i++;//一直相等则得一直往后比下去
		}
		if (data.size() > s.size())//*this的前半部分都和s相等，但*this比较长，就比较大
			return true;
		else//*this <= s
			return false;
	}
	bool operator==(const String& s)//重载二元运算符==
	{
		if (data.size() != s.size())//如果连长度都不相等那这两个字符串肯定不相等
			return false;
		size_type i = 0;
		while (i < data.size())
		{
			if (data[i] != s[i])//当遇到第一个不相等的字符时说明字符串不相等
				return false;
			i++;
		}
		return true;//从头到尾都相等，长度也相等，则字符串相等
		//这种方法代码量比较少，但运行效率应该比较低
		/*if (!((*this) > s) && !((*this) < s))
			return true;
		else
			return false;*/
	}
	bool operator!=(const String& s)//重载二元运算符!=
	{
		if (data.size() != s.size())//如果连长度都不相等那这两个字符串肯定不相等
			return true;
		size_type i = 0;
		while (i < data.size())
		{
			if (data[i] != s[i])//当遇到第一个不相等的字符时说明字符串不相等
				return true;
			i++;
		}
		return false;//从头到尾都相等，长度也相等，则字符串相等
		//这种方法代码量比较少，但运行效率应该比较低
		/*if (((*this) > s) || ((*this) < s))
			return true;
		else
			return false;*/
	}

	template <class Iter> iterator insert(Iter i, Iter j, iterator c)//插入一段元素到指定位置后面，并返回插入的最后一个元素后面一个元素的迭代器
	{
		return data.insert(i, j, c);
	}

private:
	Vector<char> data;//一个字符串即为一个字符型数组
};

istream& operator>>(istream& is, String& s)//istream&是二元运算符>>的左操作数，所以该函数不能作为String类的成员函数，但由于该函数必须改变类的私有成员的值，所以该函数还应是String类的友元函数
{
	s.data.clear();//先清空上次读入的值，就跟我们平常的操作一样，读到的s在下一次读取之后就被除去
	char c;
	while (is.get(c) && isspace(c));//当从输入流中读到一个空白字符时，继续读取（由于继续读取的操作已经写在while的判断条件里面了，所以循环体为空
	if (is)//当从输入流中读到一个非空白字符时
	{
		/*while (is.get(c) && !isspace(c))
			s.data.push_back(c);*/
			//错误，应该先把上一个循环体中最后get到的那个!isspace的c读进来再继续判断is.get(c)&&!isspace(c)
		do {//读取输入流中的非空白字符，直到遇到一个空白字符为止
			s.data.push_back(c);
		} while (is.get(c) && !isspace(c));
		if (is)//如果是因为读到了空白字符而退出，要把这个空白字符放回输入流！
			is.unget();
	}
	return is;//输入流读取不到字符时返回
}

ostream& operator<<(ostream& os, const String& s)//ostream&是二元运算符>>的左操作数，所以该函数不能作为String类的成员函数
{
	for (String::size_type i = 0; i < s.size(); i++)
		os << s[i];
	return os;
}

String operator+(const String& s, const String& t)//不能作为String类的成员函数，否则破坏了左右操作数的对称性
{
	String r = s;
	r += t;
	return r;
}