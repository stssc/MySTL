#include <iostream>
#include "algorithm.h"
#include "string.h"
#include "vector.h"
using namespace std;

int main() {
	Vector<int> v;
	v.push_back(1);
	for (int x : v)
		cout << x << " ";
	cout << endl;
	cout << v[0] << endl;
	int a[] = { 2,3,5,3,1 };
	quickSort(a, 0,4);
	for (int i = 0; i < 5; i++)
		cout << a[i] << " ";
	cout << endl;
	String s = "fsda", t = "adfafsdagsd";
	cout << kmp(s, t) << endl;
	return 0;
}