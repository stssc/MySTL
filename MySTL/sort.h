#pragma once
#include <algorithm>

//��������
int partition(int a[], int left, int right) {
	int t = a[left];//�������Ԫ��Ϊ��׼��һ�˻��֣�ʹ�ñ���С��Ԫ�ض��ܵ�����ߣ�����С��Ԫ�ض��ܵ����ұ�
	int i = left, j = right;//i���������ܣ����Ȼ�׼���Ԫ�ظϵ���׼�ұ�ȥ��j���������ܣ����Ȼ�׼С��Ԫ�ظϵ���׼���ȥ
	while (i < j) {
		while (i < j && a[j] >= t)
			j--;
		a[i] = a[j];//ֱ�Ӹ���a[i]���ɣ���Ϊa[i]���б��ݣ�Ҫô��t����Ҫô����һ�ε�a[j]�Ƕ�
		while (i < j && a[i] <= t)
			i++;
		a[j] = a[i];//ֱ�Ӹ���a[j]���ɣ���Ϊa[j]���б��ݣ����ϴε�a[i]��
	}
	a[i] = t;
	return i;
}

void quickSort(int a[], int left, int right) {
	if (left >= right)
		return;
	int mid = partition(a, left, right);
	quickSort(a, left, mid - 1);
	quickSort(a, mid + 1, right);
}



//�鲢����
void merge(int a[], int left, int mid, int right) {
	int *b = new int[right - left + 1];
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right) {
		if (a[i] < a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	//ʣ���ӱ��е�Ԫ��˳λ����b
	while (i <= mid)
		b[k++] = a[i++];
	while (j <= right)
		b[k++] = a[j++];
	for (int k = 0; k < right - left + 1; k++)
		a[k + left] = b[k];
	delete b;
}

void mergeSort(int a[], int left, int right) {
	if (left == right)
		return;
	int mid = (left + right) / 2;
	mergeSort(a, left, mid);
	mergeSort(a, mid + 1, right);
	merge(a, left, mid, right);
}



//�۰��������
int binaryInsert(int a[], int left, int right, int x) {//����aΪ��������
	while (left < right) {
		int mid = (left + right) / 2;
		if (x == a[mid])
			return mid;
		else if (x < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	int mid = left = right;
	if (x > a[mid])
		return mid + 1;
	else
		return mid;
}

void binaryInsertSort(int a[], int n) {//����ɵ�������
	for (int i = 1; i < n; i++) {//O(n)
		int d = binaryInsert(a, 0, i - 1, a[i]);//����Ҫ��a[i]����a[0...i-1]����ĸ�λ��	//O(logn)
		int t = a[i];//�ݴ�a[i]
		for (int j = i; j >= d; j--)//O(n) 
			a[j] = a[j - 1];//a[d...i-1]˳λ���Ƶ�a[d+1...i]
		a[d] = t;//ԭ�ȵ�a[i]����d
	}
}



//ϣ����������
void shellInsert(int a[], int d, int n) {
	for (int i = 0; i < d; i++) {//��������{a[0],a[0+d],a[0+2*d],...}��{a[1],a[1+d],a[1+2*d],...}��...��{a[d-1],a[d-1+d],a[d-1+2*d],...}�ֱ���ֱ�Ӳ�������
		for (int j = i; j < n; j += d) {//�����������е�ÿ��Ԫ��
			int t = a[j];//���ڲ��������a[j]��䣬�����ݴ��ʼ��a[j]
			for (int k = j - d; k >= i; k -= d) {//��a[j]˳����Ҳ��뵽������������{a[i],a[i+d],...a[j-d]}��
				if (t < a[k]) {
					a[k + d] = a[k];//a[k]����
					a[k] = t;//a[j]����
				}
				else
					break;
			}
		}
	}
}

void shellInsertSort(int a[], int d[], int n, int m) {
	for (int i = 0; i < m; i++)//m��ϣ����������ÿ��
		shellInsert(a, d[i], n);
}



//������
void heapSort(int a[], int n) {
	int *b = new int[n + 1];
	for (int i = 0; i < n; i++)
		b[i + 1] = a[i];
	int j = 0;
	while (n) {
		int i = n;
		if (n % 2 == 0) {//nΪż����˵�����һ��������丸�������ӽ�㣨������±��1��ʼ��
			if (b[i] < b[i / 2]) {
				int t = b[i / 2];
				b[i / 2] = b[i];
				b[i] = t;
			}
			i--;
		}
		//����i�����������丸�������ӽ��
		while (i >= 3) {
			if (min(b[i], b[i - 1]) < b[i / 2]) {
				if (b[i] < b[i - 1]) {
					int t = b[i / 2];
					b[i / 2] = b[i];
					b[i] = t;
				}
				else {
					int t = b[i / 2];
					b[i / 2] = b[i - 1];
					b[i - 1] = t;
				}
			}
			i -= 2;
		}
		a[j++] = b[1];
		b[1] = b[n];
		n--;
	}
}



//ð������
void bubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}



//ѡ������
void selectSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[minIndex])
				minIndex = j;
		int t = a[i];
		a[i] = a[minIndex];
		a[minIndex] = t;
	}
}