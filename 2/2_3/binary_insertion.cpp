// CLRS 2.3 Exercise 6
// insertion sort with binary search 
// may increase the speed slightly, but cannot reduce the order of complexity

#include <iostream>
using namespace std;

int binary_search(int* arr, int begin, int end, int elem) {
	int lo = begin, hi = end;

	while (hi - lo > 1) {
		int mid = (lo + hi) / 2;
		if (arr[mid] <= elem)
			lo = mid;
		else
			hi = mid;
	}

	return hi;
}

void insertion_sort(int* arr, int num) {
	for (int i = 1; i < num; i++) {
		int place = binary_search(arr, 0, i, arr[i]);
		int tmp = arr[i];
		for (int j = i; j > place; j--)
			arr[j] = arr[j - 1];
		arr[place] = tmp;
	}
}

int main() {
	int arr[] = {1, 3, 2, 4, 3, 5, 2, 8, 9, 6};
	int num = sizeof(arr) / sizeof(int);
	insertion_sort(arr, num);
	for (int i = 0; i < num; i++)
		cout << arr[i] << ' ';
	cout << endl;
	return 0;
}