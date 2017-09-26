/*************************************************************************
	> File Name: maximum_subarray.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Sep 2017 11:16:36 AM EDT
    > CLRS 4.1
    > Maximum Subarray: Brute_Force, Divide, Linear
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


// record the begin, end and the sum of a subarray
// used as the return sum of the maximum-subarray algorithm
struct Subarray {
    // sum = arr[end] - arr[begin];
    int begin;
    int end;
    int sum;
    bool operator==(const Subarray& val) const {
        return sum == val.sum;
    }
};

ostream& operator<< (ostream& out, const Subarray& arr) {
    out << arr.begin << ' ' << arr.end << ' ' << arr.sum << endl;
    return out;
}

// Brute Force
// O(n^2)
Subarray maximum_subarray_brute_force(int* arr, int num) {
    Subarray subarr = {0, 0, 0};
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            int sum = arr[j] - arr[i];
            if (sum > subarr.sum) {
                subarr.begin = i;
                subarr.end = j;
                subarr.sum = sum;
            }
        }
    }

    return subarr;
}

// Divide and Conquer
// O(nlogn)
Subarray maximum_subarray_divide(int* arr, int begin, int end) {
    // [begin, end)

    if (end - begin == 1) {
        Subarray subarr = {begin, end, 0};
        return subarr;
    }

    // divide
    // T(n / 2) * 2
    int mid = (begin + end) / 2;
    Subarray arr_left = maximum_subarray_divide(arr, begin, mid);
    Subarray arr_right = maximum_subarray_divide(arr, mid, end);

    // find max_subarray cross both part
    // O(n)
    int max_mid_begin = mid, max_mid_end = mid;
    int max_sum = 0;
    for (int j = mid + 1; j < end; j++) {
        int sum = arr[j] - arr[max_mid_begin];
        if (max_sum < sum) {
            max_mid_end = j;
            max_sum = sum;
        }
    }
    for (int i = mid - 1; i >= begin; i--) {
        int sum = arr[max_mid_end] - arr[i];
        if (max_sum < sum) {
            max_mid_begin = i;
            max_sum = sum;
        }
    }

    // compare
    Subarray arr_mid = {max_mid_begin, max_mid_end, max_sum};
    if (arr_left.sum > arr_right.sum && arr_left.sum > arr_mid.sum) {
        return arr_left;
    } else if (arr_right.sum > arr_left.sum && arr_right.sum > arr_mid.sum){
        return arr_right;
    } else {
        return arr_mid;
    }
}

Subarray maximum_subarray_divide(int* arr, int num) {
    return maximum_subarray_divide(arr, 0, num);
}

// Linear
// O(n)
Subarray maximum_subarray_linear(int* arr, int num) {
    int max_begin = 0, max_end = 0, min_index = 0;
    int max_sum = 0;
    int min_value = arr[min_index];

    for (int i = 1; i < num; i++) {
        int sum = arr[i] - arr[min_index];
        if (max_sum < sum) {
            max_begin = min_index;
            max_end = i;
            max_sum = sum;
        }
        if (arr[i] < min_value) {
            min_index = i;
            min_value = arr[i];
        }
    }

    Subarray subarr = {max_begin, max_end, max_sum};
    return subarr;
}


int main() {
    // simple
    int arr[] = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 90, 97};
    int num = sizeof(arr) / sizeof(int);
    Subarray max_arr_brute_force = maximum_subarray_brute_force(arr, num);
    Subarray max_arr_divide = maximum_subarray_divide(arr, num);
    Subarray max_arr_linear = maximum_subarray_linear(arr, num);
    cout << "brute force:" << max_arr_brute_force;
    cout << "divide and conquer:" << max_arr_divide;
    cout << "linear:" << max_arr_linear;

    // large problem set
    // result: 
    // len = 100000, brute_force - 14s, divide - 0s, linear - 0s
    // len = 100000000, brute_force - (who knows...), divide - 11s, linear - 1s
    srand(time(NULL));
    const int len = 100000;
    int* arr_large = new int[len];
    //int arr_large[len];
    for (int i = 0; i < len; i++) {
        arr_large[i] = rand();
    }

    time_t start, end;
    double cost_brute_force, cost_divide, cost_linear;
    time(&start);
    max_arr_brute_force = maximum_subarray_brute_force(arr_large, len);
    time(&end);
    cost_brute_force = difftime(end, start);

    time(&start);
    max_arr_divide = maximum_subarray_divide(arr_large, len);
    time(&end);
    cost_divide = difftime(end, start);

    time(&start);
    max_arr_linear = maximum_subarray_linear(arr_large, len);
    time(&end);
    cost_linear = difftime(end, start);

    if (!(max_arr_brute_force == max_arr_divide && max_arr_brute_force == max_arr_linear)) {
        cout << "error!" << endl;
    }

    cout << "brute force - " << cost_brute_force << "s: " << max_arr_brute_force;
    cout << "divide and conquer - " << cost_divide << "s: " << max_arr_divide;
    cout << "linear - " << cost_linear << "s: " << max_arr_linear;

    delete[] arr_large;

    return 0;
}
