// CLRS 2.3 Exercise 4
// recursive version of insertion sort

#include <iostream>
using namespace std;

void insertion_sort(int* arr, int num) {
	if (num <= 1)
		return;

	insertion_sort(arr, num - 1);

	int tmp = arr[num - 1];
	int i;
	for (i = num - 2; i >= 0; i--) {
		if (arr[i] <= tmp)
			break;
	}
	i++;
	
	for (int j = num - 1; j > i; j--) {
		arr[j] = arr[j - 1];
	}
	arr[i] = tmp;
}

int main() {
	int arr[] = {2, 1, 4, 2, 3, 5, 1, 8, 4, 2};
	int num = sizeof(arr) / sizeof(int);
	insertion_sort(arr, num);
	for (int i = 0; i < num; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	return 0;
}