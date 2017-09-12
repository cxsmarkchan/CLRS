// CLRS 2.3 Exercise 2
// merge sort

#include <iostream>
using namespace std;

// merge [begin, mid) and [mid, end)
void merge(int* arr, int begin, int mid, int end) {
	int* tmp_arr = new int[end - begin];

	int p1 = begin, p2 = mid;
	int p = 0;

	while (p1 < mid && p2 < end) {
		if (arr[p1] <= arr[p2]) {
			tmp_arr[p++] = arr[p1++];
		} else {
			tmp_arr[p++] = arr[p2++];
		}
	}

	if (p2 == end) {
		p2 = end - (mid - p1);
		while (p2 < end) {
			arr[p2++] = arr[p1++];
		}
	}

	for (int i = 0; i < p; i++) {
		arr[i + begin] = tmp_arr[i];
	}

	delete[] tmp_arr;
}

void merge_sort(int* arr, int begin, int end) {
	if (end - begin <= 1)
		return;
	int mid = (begin + end) / 2;
	merge_sort(arr, begin, mid);
	merge_sort(arr, mid, end);
	merge(arr, begin, mid, end);
}

void merge_sort(int* arr, int num) {
	merge_sort(arr, 0, num);
}

int main() {
	int arr[] = {2, 1, 4, 2, 3, 5, 1, 8, 4, 2};
	int num = sizeof(arr) / sizeof(int);
	merge_sort(arr, num);
	for (int i = 0; i < num; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}