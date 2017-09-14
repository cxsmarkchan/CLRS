// CLRS Problem 2.2
// bubble sort

#include <iostream>
using namespace std;

void bubble_sort(int* arr, int num) {
	for (int i = num; i > 0; i--) {
		for (int j = 1; j < i; j++) {
			if (arr[j] < arr[j - 1]) {
				int tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
			}
		}
	}
}

int main() {
	int arr[] = {3, 4, 1, 2, 5, 6, 3, 1, 4, 2};
	int num = sizeof(arr) / sizeof(int);

	bubble_sort(arr, num);
	for (int i = 0; i < num; i++)
		cout << arr[i] << ' ';
	cout << endl;

	return 0;
}