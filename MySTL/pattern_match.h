#pragma once
#include "String.h"

int* getNext(String s) {//求串s的next[]数组，next[i]表示子串s[0...i-1]（注意不是s[0...i]！！）前后缀相同的最大长度（注意串的前后缀均不包括串本身）
	int *next = new int[s.size()];
	int i = 0, j = 1;
	next[1] = 0;//根据定义可知，next[1]=0
	while (j < s.size() - 1 && s[i] != s[j]) {//从s[1]开始寻找第一个与s[0]相同的字符（最长后缀的第一个字符肯定和最长前缀的第一个字符即串的第一个字符相同），注意检查j越界错误！
		next[j + 1] = 0;
		j++;
	}
	//当找到串s中第一个与s[0]相同的字符时，开始往后匹配
	while (j < s.size() - 1) {//不需要构造next[s.size()-1+1]，因为计算整个串s的最长相同前后缀长度没有意义
		if (s[i] == s[j]) {//如果相同则继续匹配下去
			next[j + 1] = i + 1;//边匹配边求出子串s[0...i-1]前后缀相同的最大长度为前缀s[0...i]的长度即i+1;
			i++; j++;
		}
		else {//重新寻找下一个与s[0]相同的字符
			i = 0;
			while (j < s.size() - 1 && s[i] != s[j]) {//注意检查j越界错误！
				next[j + 1] = 0;
				j++;
			}
			//当找到串s中下一个与s[0]相同的字符时，继续往后匹配
		}
	}
	return next;
}

//更好的算法，提高例如aaaab匹配aaabaaaab的效率（其实也不痛不痒）
int* getNext_betterAlgorithm(String s) {///求串s的next[]数组，next[i]表示子串s[0...i-1]（注意不是s[0...i]！！）前后缀相同的最大长度（注意串的前后缀均不包括串本身）
	int *next = new int[s.size()];
	int i = 0, j = 1;
	next[1] = 0;///根据定义可知，next[1]=0
	while (j < s.size() - 1 && s[i] != s[j]) {///从s[1]开始寻找第一个与s[0]相同的字符（最长后缀的第一个字符肯定和最长前缀的第一个字符即串的第一个字符相同），注意检查j越界错误！
		next[j + 1] = 0;
		j++;
	}
	///当找到串s中第一个与s[0]相同的字符时，开始往后匹配
	while (j < s.size() - 1) {///不需要构造next[s.size()-1+1]，因为计算整个串s的最长相同前后缀长度没有意义
		if (s[i] == s[j]) {///如果相同则继续匹配下去
			if (s[j + 1] != s[i + 1])
				next[j + 1] = i + 1;///边匹配边求出子串s[0...i-1]前后缀相同的最大长度为前缀s[0...i]的长度即i+1;
			else//正常如果在s[j+1]处失配就应该跳到next[j+1]=i+1处继续匹配，但如果s[j+1]=s[i+1]，那么就算跳回s[next[j+1]]也还是失配，不如跳到next[next[j+1]]
				next[j + 1] = next[i + 1];
			i++; j++;
		}
		else {///重新寻找下一个与s[0]相同的字符
			i = 0;
			while (j < s.size() - 1 && s[i] != s[j]) {///注意检查j越界错误！
				next[j + 1] = 0;
				j++;
			}
			///当找到串s中下一个与s[0]相同的字符时，继续往后匹配
		}
	}
	return next;
}

int kmp(String s, String t) {//判断串s是不是串t的子串，如果是，则求出串s在串t中的位置
	//int *next = getNext(s);
	int *next = getNext_betterAlgorithm(s);
	int i = 0, j = 0;
	while (i < s.size() && j < t.size()) {
		if (s[i] == t[j]) {//如果匹配则继续往后匹配
			i++; j++;
		}
		else {//如果不匹配则用子串s[0...i-1]中与后缀相同的最长前缀的下一个字符代替串s当前字符，和串t当前字符重新开始匹配，如果串s[0...i-1]没有相同的前后缀则从s[0]开始与串t当前字符重新开始匹配（与next[]数组定义符合），如果本来就是s[0]和t[j]不匹配则从s[0]和t[j+1]开始重新匹配
			if (i == 0)
				j++;
			else
				i = next[i];
		}
	}
	if (i == s.size())//如果退出循环是因为串s遍历完，说明s[0...s.size()-1]匹配成功（如果最后一位匹配不成功的话i会变成next[i]），此时i和j都在匹配串的下一个字符
		return j - s.size();
	else
		return -1;
}