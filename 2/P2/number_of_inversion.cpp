// CLRS Problem 2.4
// get the number of inversions

#include <iostream>
using namespace std;

// merge and return the number of inversions
int merge(int* arr, int begin, int mid, int end) {
	int* tmp_arr = new int[end - begin];

	int p1 = begin, p2 = mid;
	int p = 0;
	int num = 0;

	while (p1 < mid && p2 < end) {
		if (arr[p1] <= arr[p2])
			tmp_arr[p++] = arr[p1++];
		else {
			num += (mid - p1);
			tmp_arr[p++] = arr[p2++];
		}
	}

	if (p2 == end) {
		p2 = end - (mid - p1);
		while (p2 < end)
			arr[p2++] = arr[p1++];
	}

	for (int i = 0; i < p; i++)
		arr[i + begin] = tmp_arr[i];

	delete[] tmp_arr;

	return num;
}

// merge sort and return the number of inversions
int merge_sort(int* arr, int begin, int end) {
	if (end - begin <= 1)
		return 0;

	int num = 0;
	int mid = (begin + end) / 2;
	num += merge_sort(arr, begin, mid);
	num += merge_sort(arr, mid, end);
	num += merge(arr, begin, mid, end);
	return num;
}

int main() {
	int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int num = sizeof(arr) / sizeof(int);
	cout << merge_sort(arr, 0, num) << endl;
	return 0;
}