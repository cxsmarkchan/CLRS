// CLRS 2.1
// insertion sort

#include <iostream>
using namespace std;

void insertion_sort(int* arr, int num) {
	for (int i = 0; i < num; i++) {
		int tmp = arr[i];

		//find the position to insert
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] <= arr[i]) break;
		}
		j++;

		// insert
		for (int k = i; k > j; k--) {
			arr[k] = arr[k - 1];
		}
		arr[j] = tmp;
	}
}

int main() {
	int arr[] = {3, 4, 3, 2, 7, 5, 1, 3, 2, 3};
	int n = sizeof(arr) / sizeof(int);
	insertion_sort(arr, n);
	for (int i = 0; i < n; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}