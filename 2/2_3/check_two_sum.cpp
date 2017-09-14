// CLRS 2.3 Exercise 7

#include <iostream>
using namespace std;

void merge(int* arr, int begin, int mid, int end) {
	int* tmp_arr = new int[end - begin];

	int p1 = begin, p2 = mid;
	int p = 0;

	while (p1 < mid && p2 < end) {
		if (arr[p1] <= arr[p2])
			tmp_arr[p++] = arr[p1++];
		else
			tmp_arr[p++] = arr[p2++];
	}

	if (p2 == end) {
		p2 = end - (mid - p1);
		while (p2 < end)
			arr[p2++] = arr[p1++];
	}

	for (int i = 0; i < p; i++) {
		arr[i + begin] = tmp_arr[i];
	}

	delete []tmp_arr;
}

void merge_sort(int* arr, int begin, int end) {
	if (end - begin <= 1)
		return;
	int mid = (begin + end) / 2;
	merge_sort(arr, begin, mid);
	merge_sort(arr, mid, end);
	merge(arr, begin, mid, end);
}

bool check_two_sum(int* arr, int num, int x) {
	if (num <= 1)
		return false;

	merge_sort(arr, 0, num);

	int i1 = 0, i2 = 1;
	while (i2 < num) {
		while (i1 < i2) {
			if (arr[i1] + arr[i2] == x)
				return true;
			i1++;
		}
		i2++;
	}

	return false;
}

int main() {
	int arr[] = {4, 4, 1, 2, 6, 7, 8, 1, 9};
	int num = sizeof(arr) / sizeof(int);
	int x = 4;
	cout << check_two_sum(arr, num, x);
	return 0;
}