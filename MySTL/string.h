#pragma once

#include <iostream>
#include "vector.h"
using namespace std;

class String
{
	friend istream& operator>>(istream&, String&);//��������������Ԫ����
public:
	typedef Vector<char>::size_type size_type;//�����ַ������ȵ���������
	typedef Vector<char>::iterator iterator;//String�ĵ�����
	typedef Vector<char>::const_iterator const_iterator;//String�ĳ���������

	size_type size() const { return data.size(); }//�����ַ�������
	iterator begin() { return data.begin(); }//�����ַ����׵�����
	iterator end() { return data.end(); }//�����ַ���β������

	String() {}//���캯��
	String(size_type n, char c) :data(n, c) {}//������n��c�ַ���ɵ��ַ���
	String(const char* cp) { copy(cp, cp + strlen(cp), back_inserter(data)); }//���ƹ��캯����char *�Ͳ�����
	template<class Iter> String(Iter b, Iter e) { copy(b, e, back_inserter(data)); }//���ƹ��캯����String�Ͳ�����

	char& operator[](size_type i) { return data[i]; }//��������������
	const char& operator[](size_type i) const { return data[i]; }//��������������
	String& operator+=(const String& s) {//���ض�Ԫ�����+=
		copy(s.data.begin(), s.data.end(), back_inserter(data));//���������ַ���
		return *this;
	}
	bool operator<(const String& s)//���ض�Ԫ�����<
	{
		size_type i = 0;
		while (i < data.size() && i < s.size())//���������ܵ�ͷ�������Խ��
		{
			if (data[i] > s[i])//������һ��data[i]>s[i]����˵��*this > s
				return false;
			if (data[i] < s[i])//������һ��data[i]<s[i]����˵��*this < s
				return true;
			i++;//һֱ������һֱ�������ȥ
		}
		if (data.size() < s.size())//s��ǰ�벿�ֶ���*this��ȣ���s�Ƚϳ����ͱȽϴ�
			return true;
		else//*this >= s
			return false;
	}
	bool operator>(const String& s)//���ض�Ԫ�����>
	{
		size_type i = 0;
		while (i < data.size() && i < s.size())//���������ܵ�ͷ�������Խ��
		{
			if (data[i] < s[i])//������һ��data[i]<s[i]����˵��*this < s
				return false;
			if (data[i] > s[i])//������һ��data[i]>s[i]����˵��*this > s
				return true;
			i++;//һֱ������һֱ�������ȥ
		}
		if (data.size() > s.size())//*this��ǰ�벿�ֶ���s��ȣ���*this�Ƚϳ����ͱȽϴ�
			return true;
		else//*this <= s
			return false;
	}
	bool operator==(const String& s)//���ض�Ԫ�����==
	{
		if (data.size() != s.size())//��������ȶ���������������ַ����϶������
			return false;
		size_type i = 0;
		while (i < data.size())
		{
			if (data[i] != s[i])//��������һ������ȵ��ַ�ʱ˵���ַ��������
				return false;
			i++;
		}
		return true;//��ͷ��β����ȣ�����Ҳ��ȣ����ַ������
		//���ַ����������Ƚ��٣�������Ч��Ӧ�ñȽϵ�
		/*if (!((*this) > s) && !((*this) < s))
			return true;
		else
			return false;*/
	}
	bool operator!=(const String& s)//���ض�Ԫ�����!=
	{
		if (data.size() != s.size())//��������ȶ���������������ַ����϶������
			return true;
		size_type i = 0;
		while (i < data.size())
		{
			if (data[i] != s[i])//��������һ������ȵ��ַ�ʱ˵���ַ��������
				return true;
			i++;
		}
		return false;//��ͷ��β����ȣ�����Ҳ��ȣ����ַ������
		//���ַ����������Ƚ��٣�������Ч��Ӧ�ñȽϵ�
		/*if (((*this) > s) || ((*this) < s))
			return true;
		else
			return false;*/
	}

	template <class Iter> iterator insert(Iter i, Iter j, iterator c)//����һ��Ԫ�ص�ָ��λ�ú��棬�����ز�������һ��Ԫ�غ���һ��Ԫ�صĵ�����
	{
		return data.insert(i, j, c);
	}

private:
	Vector<char> data;//һ���ַ�����Ϊһ���ַ�������
};

istream& operator>>(istream& is, String& s)//istream&�Ƕ�Ԫ�����>>��������������Ըú���������ΪString��ĳ�Ա�����������ڸú�������ı����˽�г�Ա��ֵ�����Ըú�����Ӧ��String�����Ԫ����
{
	s.data.clear();//������ϴζ����ֵ���͸�����ƽ���Ĳ���һ����������s����һ�ζ�ȡ֮��ͱ���ȥ
	char c;
	while (is.get(c) && isspace(c));//�����������ж���һ���հ��ַ�ʱ��������ȡ�����ڼ�����ȡ�Ĳ����Ѿ�д��while���ж����������ˣ�����ѭ����Ϊ��
	if (is)//�����������ж���һ���ǿհ��ַ�ʱ
	{
		/*while (is.get(c) && !isspace(c))
			s.data.push_back(c);*/
			//����Ӧ���Ȱ���һ��ѭ���������get�����Ǹ�!isspace��c�������ټ����ж�is.get(c)&&!isspace(c)
		do {//��ȡ�������еķǿհ��ַ���ֱ������һ���հ��ַ�Ϊֹ
			s.data.push_back(c);
		} while (is.get(c) && !isspace(c));
		if (is)//�������Ϊ�����˿հ��ַ����˳���Ҫ������հ��ַ��Ż���������
			is.unget();
	}
	return is;//��������ȡ�����ַ�ʱ����
}

ostream& operator<<(ostream& os, const String& s)//ostream&�Ƕ�Ԫ�����>>��������������Ըú���������ΪString��ĳ�Ա����
{
	for (String::size_type i = 0; i < s.size(); i++)
		os << s[i];
	return os;
}

String operator+(const String& s, const String& t)//������ΪString��ĳ�Ա�����������ƻ������Ҳ������ĶԳ���
{
	String r = s;
	r += t;
	return r;
}