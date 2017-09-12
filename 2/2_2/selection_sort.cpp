// CLRS 2.2 Exercise 2
// selection sort

#include <iostream>
using namespace std;

void selection_sort(int* arr, int num) {
	for (int i = 0; i < num; i++) {
		int min_id = i;
		for (int j = i + 1; j < num; j++) {
			if (arr[j] < arr[min_id]) {
				min_id = j;
			}
		}
		// swap
		int tmp = arr[i];
		arr[i] = arr[min_id];
		arr[min_id] = tmp;
	}
}

int main() {
	int arr[] = {2, 1, 4, 2, 3, 5, 1, 8, 4, 2};
	int num = sizeof(arr) / sizeof(int);
	selection_sort(arr, num);
	for (int i = 0; i < num; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}