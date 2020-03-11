#pragma once
#include <algorithm>

//快速排序
int partition(int a[], int left, int right) {
	int t = a[left];//以最左端元素为基准做一趟划分，使得比它小的元素都跑到它左边，比它小的元素都跑到它右边
	int i = left, j = right;//i从做往右跑，将比基准大的元素赶到基准右边去；j从右往左跑，将比基准小的元素赶到基准左边去
	while (i < j) {
		while (i < j && a[j] >= t)
			j--;
		a[i] = a[j];//直接覆盖a[i]即可，因为a[i]已有备份，要么在t处，要么在上一次的a[j]那儿
		while (i < j && a[i] <= t)
			i++;
		a[j] = a[i];//直接覆盖a[j]即可，因为a[j]已有备份，在上次的a[i]那
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



//归并排序
void merge(int a[], int left, int mid, int right) {
	int *b = new int[right - left + 1];
	int i = left, j = mid + 1, k = 0;
	while (i <= mid && j <= right) {
		if (a[i] < a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	//剩余子表中的元素顺位进入b
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



//折半插入排序
int binaryInsert(int a[], int left, int right, int x) {//假设a为递增序列
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

void binaryInsertSort(int a[], int n) {//排序成递增序列
	for (int i = 1; i < n; i++) {//O(n)
		int d = binaryInsert(a, 0, i - 1, a[i]);//计算要把a[i]插入a[0...i-1]里的哪个位置	//O(logn)
		int t = a[i];//暂存a[i]
		for (int j = i; j >= d; j--)//O(n) 
			a[j] = a[j - 1];//a[d...i-1]顺位后移到a[d+1...i]
		a[d] = t;//原先的a[i]插入d
	}
}



//希尔插入排序
void shellInsert(int a[], int d, int n) {
	for (int i = 0; i < d; i++) {//对子序列{a[0],a[0+d],a[0+2*d],...}，{a[1],a[1+d],a[1+2*d],...}，...，{a[d-1],a[d-1+d],a[d-1+2*d],...}分别做直接插入排序
		for (int j = i; j < n; j += d) {//遍历子序列中的每个元素
			int t = a[j];//由于插入过程中a[j]会变，故先暂存初始的a[j]
			for (int k = j - d; k >= i; k -= d) {//将a[j]顺序查找插入到已排序子序列{a[i],a[i+d],...a[j-d]}中
				if (t < a[k]) {
					a[k + d] = a[k];//a[k]后移
					a[k] = t;//a[j]插入
				}
				else
					break;
			}
		}
	}
}

void shellInsertSort(int a[], int d[], int n, int m) {
	for (int i = 0; i < m; i++)//m趟希尔插入排序，每趟
		shellInsert(a, d[i], n);
}



//堆排序
void heapSort(int a[], int n) {
	int *b = new int[n + 1];
	for (int i = 0; i < n; i++)
		b[i + 1] = a[i];
	int j = 0;
	while (n) {
		int i = n;
		if (n % 2 == 0) {//n为偶数，说明最后一个结点是其父结点的左子结点（根结点下标从1开始）
			if (b[i] < b[i / 2]) {
				int t = b[i / 2];
				b[i / 2] = b[i];
				b[i] = t;
			}
			i--;
		}
		//现在i是奇数，是其父结点的右子结点
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



//冒泡排序
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



//选择排序
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