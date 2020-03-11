#pragma once

//�۰����
int binarySearch(int a[], int n, int x) {//����aΪ��������
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
	return -1;//�Ҳ���
}

//�۰����
int binarySearch(int a[], int left, int right, int x) {
	if (left > right)
		return -1;
	else {
		int mid = (left + right) / 2;
		if (x < a[mid])//С�Ĳ�Ҫд��x<mid��
			return binarySearch(a, left, mid - 1, x);
		else if (x > a[mid])
			return binarySearch(a, mid + 1, right, x);
		else
			return mid;//С�Ĳ�Ҫд��return a[mid]!
	}
}