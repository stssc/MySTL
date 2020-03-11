#pragma once

//折半查找
int binarySearch(int a[], int n, int x) {//假设a为递增序列
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (x == a[mid])
			return mid;
		else if (x < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;//找不到
}

//折半查找
int binarySearch(int a[], int left, int right, int x) {
	if (left > right)
		return -1;
	else {
		int mid = (left + right) / 2;
		if (x < a[mid])//小心不要写成x<mid！
			return binarySearch(a, left, mid - 1, x);
		else if (x > a[mid])
			return binarySearch(a, mid + 1, right, x);
		else
			return mid;//小心不要写成return a[mid]!
	}
}