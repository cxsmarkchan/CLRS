// CLRS 2.3 Exercise 5
// binary search

#include <iostream>
using namespace std;

// search within [begin, end)
// return the index of the last one which equals num
// return -1 if there is no match
int binary_search(int* arr, int begin, int end, int num) {
	int lo = begin, hi = end;

	while (hi - lo > 1) {
		int mid = (lo + hi) / 2;
		if (arr[mid] <= num)
			lo = mid;
		else
			hi = mid;
	}

	if (hi - lo == 1 && arr[lo] == num)
		return lo;
	else
		return -1;
}

int main() {
	int arr[] = {1, 1, 2, 4, 5, 5, 6, 7, 9};
	cout << binary_search(arr, 0, 9, 5) << endl;
	return 0;
}